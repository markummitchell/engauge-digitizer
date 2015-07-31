#include "EngaugeAssert.h"
#include "FormatDateTime.h"
#include "Logger.h"

FormatDateTime::FormatDateTime()
{
  loadFormatsFormat();
  loadFormatsParseAcceptable();
  loadFormatsParseIncomplete();
}

void FormatDateTime::dateTimeLookup (const FormatsDate &formatsDateAll,
                                     const FormatsTime &formatsTimeAll,
                                     CoordUnitsDate coordUnitsDate,
                                     CoordUnitsTime coordUnitsTime,
                                     const QString &string,
                                     bool useQDateTimeElseQRegExp,
                                     unsigned long &value,
                                     bool &success) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::dateTimeLookup";

  success = false;

  ENGAUGE_ASSERT (formatsDateAll.contains (coordUnitsDate));
  ENGAUGE_ASSERT (formatsTimeAll.contains (coordUnitsTime));

  QStringList formatsDate = formatsDateAll [coordUnitsDate];
  QStringList formatsTime = formatsTimeAll [coordUnitsTime];

  // Loop through the legal date/time combinations
  QStringList::const_iterator itrDate, itrTime;
  bool iterating = true;
  for (itrDate = formatsDate.begin(); itrDate != formatsDate.end() && iterating; itrDate++) {

    QString formatDate = *itrDate;

    for (itrTime = formatsTime.begin(); itrTime != formatsTime.end() && iterating; itrTime++) {

      QString formatTime = *itrTime;

      // Insert space as separator only if needed. Do not use trim around here since formatDate may or may not end in a space
      QString separator = (!formatDate.isEmpty() && !formatTime.isEmpty() ? " " : "");

      QString formatDateTime = formatDate + separator + formatTime;

      if (!formatDateTime.isEmpty()) {

        // Try parsing according to the current format
        if (useQDateTimeElseQRegExp) {

          QDateTime dt = QDateTime::fromString (string,
                                                formatDateTime);

          LOG4CPP_DEBUG_S ((*mainCat)) << "FormatDateTime::dateTimeLookup"
                                       << " format=" << formatDateTime.toLatin1().data()
                                       << " isValid=" << (dt.isValid() ? "true" : "false");

          if (dt.isValid()) {

            success = true;
            value = dt.toTime_t();
            iterating = false; // Stop iterating

          }
        } else {

          QRegExp reg (formatDateTime);
          if (reg.exactMatch(string)) {

            success = true; // Note that value does not get set in QRegExp case
            iterating = false; // Stop iterating

          }
        }
      }
    }
  }
}

QString FormatDateTime::formatOutput (CoordUnitsDate coordUnitsDate,
                                      CoordUnitsTime coordUnitsTime,
                                      unsigned long value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::formatOutput";

  ENGAUGE_ASSERT (m_formatsDateFormat.contains (coordUnitsDate));
  ENGAUGE_ASSERT (m_formatsTimeFormat.contains (coordUnitsTime));

  QString format = m_formatsDateFormat [coordUnitsDate] + " " + m_formatsTimeFormat [coordUnitsTime];
  format = format.trimmed();

  QDateTime dt = QDateTime::fromTime_t (value);

  return dt.toString (format);
}

void FormatDateTime::loadFormatsFormat()
{
  m_formatsDateFormat [COORD_UNITS_DATE_SKIP] = "";
  m_formatsDateFormat [COORD_UNITS_DATE_MONTH_DAY_YEAR] = "MM/dd/yyyy";
  m_formatsDateFormat [COORD_UNITS_DATE_DAY_MONTH_YEAR] = "dd/MM/yyyy";
  m_formatsDateFormat [COORD_UNITS_DATE_YEAR_MONTH_DAY] = "yyyy/MM/dd";

  ENGAUGE_ASSERT (m_formatsDateFormat.count () == NUM_COORD_UNITS_DATE);

  m_formatsTimeFormat [COORD_UNITS_TIME_SKIP] = "";
  m_formatsTimeFormat [COORD_UNITS_TIME_HOUR_MINUTE] = "hh/mm";
  m_formatsTimeFormat [COORD_UNITS_TIME_HOUR_MINUTE_SECOND] = "hh:mm:ss";

  ENGAUGE_ASSERT (m_formatsTimeFormat.count () == NUM_COORD_UNITS_TIME);
}

void FormatDateTime::loadFormatsParseAcceptable()
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::loadFormatsParseAcceptable";

  QStringList skip, dayMonth, dayMonthYear, monthDay, monthDayYear, yearMonthDay;

  // COORD_UNITS_DATE_SKIP and COORD_UNITS_TIME_SKIP allow date/time respectively even when skipped,
  // although there can be ambiguity with between COORD_UNITS_DATE_MONTH_DAY_YEAR and COORD_UNITS_DATE_DAY_MONTH_YEAR
  skip << "";

  dayMonth << "dd/MM"
           << "dd-MM"
           << "dd/MMM"
           << "ddd-MMM"
           << "dd/MMMM"
           << "dd-MMMM";
  dayMonthYear << "dd/MM/yyyy" << "dd/MM/yy"
               << "dd-MM-yyyy" << "dd-MM-yy"
               << "dd/MMM/yyyy" << "dd/MMM/yy"
               << "dd-MMM-yyyy" << "dd-MMM-yy"
               << "dd MMM yyyy" << "dd MMM yy"
               << "dd/MMMM/yyyy" << "dd/MMMM/yy"
               << "dd-MMMM-yyyy" << "dd-MMMM-yy"
               << "dd MMMM yyyy" << "dd MMMM yy";
  monthDay << "MM/dd"
           << "MMM dd"
           << "MMMM dd";
  monthDayYear << "MM/dd/yyyy" << "MM/dd/yy"
               << "MM-dd-yyyy" << "MM-dd-yy" 
               << "MMM dd yyyy"
               << "MMMM dd yyyy";
  yearMonthDay << "yyyy/MM/dd" 
               << "yyyy-MM-dd"
               << "yyyy MM dd"
               << "yyyy/MMM/dd"
               << "yyyy-MMM-dd"
               << "yyyy MMM dd"
               << "yyyy/MMMM/dd"
               << "yyyy-MMMM-dd"
               << "yyyy MMMM dd";

  // Potential day-month ambiguity for COORD_UNITS_DATE_SKIP gets treated as month/day
  m_formatsDateParseAcceptable [COORD_UNITS_DATE_SKIP] = skip + monthDay + monthDayYear + yearMonthDay;
  m_formatsDateParseAcceptable [COORD_UNITS_DATE_MONTH_DAY_YEAR] = skip + monthDay + monthDayYear + yearMonthDay;
  m_formatsDateParseAcceptable [COORD_UNITS_DATE_DAY_MONTH_YEAR] = skip + dayMonth + dayMonthYear + yearMonthDay;
  m_formatsDateParseAcceptable [COORD_UNITS_DATE_YEAR_MONTH_DAY] = skip + monthDay + monthDayYear + yearMonthDay;

  ENGAUGE_ASSERT (m_formatsDateParseAcceptable.count () == NUM_COORD_UNITS_DATE);

  QStringList hourMinute, hourMinuteSecond, hourMinutePm, hourMinuteSecondPm;

  hourMinute << "hh:mm";
  hourMinuteSecond << "hh:mm:ss";
  hourMinutePm << "hh:mmA"
               << "hh:mm A"
               << "hh:mma"
               << "hh:mm a";
  hourMinuteSecondPm << "hh:mm:ssA"
                     << "hh:mm:ss A"
                     << "hh:mm:ssa"
                     << "hh:mm:ss a";

  m_formatsTimeParseAcceptable [COORD_UNITS_TIME_SKIP] = skip + hourMinute + hourMinuteSecond + hourMinutePm + hourMinuteSecondPm;
  m_formatsTimeParseAcceptable [COORD_UNITS_TIME_HOUR_MINUTE] = skip + hourMinute + hourMinutePm + hourMinuteSecond + hourMinuteSecondPm;
  m_formatsTimeParseAcceptable [COORD_UNITS_TIME_HOUR_MINUTE_SECOND] = skip + hourMinute + hourMinutePm + hourMinuteSecond + hourMinuteSecondPm;

  ENGAUGE_ASSERT (m_formatsTimeParseAcceptable.count () == NUM_COORD_UNITS_TIME);
}

void FormatDateTime::loadFormatsParseIncomplete()
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::loadFormatsParseIncomplete";

  QStringList skip, day, dayMonth, month, monthDay, monthDayYear, year, yearMonth;

  // COORD_UNITS_DATE_SKIP and COORD_UNITS_TIME_SKIP allow date/time respectively even when skipped,
  // although there can be ambiguity with between COORD_UNITS_DATE_MONTH_DAY_YEAR and COORD_UNITS_DATE_DAY_MONTH_YEAR
  skip << "";

  day << "\\d{1,2}"
      << "\\d{1,2}/"
      << "\\d{1,2}-";
  dayMonth << "\\d{1,2}/\\d{1,2}"
           << "\\d{1,2}/\\d{1,2} "
           << "\\d{1,2}/\\d{1,2}/"
           << "\\d{1,2}-\\d{1,2}-"
           << "\\d{1,2}/[a-zA-Z]{1,12}/"
           << "\\d{1,2}-[a-zA-Z]{1,12}-"
           << "\\d{1,2} [a-zA-Z]{1,12} ";
  month << "\\d{1,2}"
        << "\\d{1,2}/"
        << "[a-zA-Z]{1,12}"
        << "[a-zA-Z]{1,12} ";
  monthDay << "\\d{1,2}/\\d{1,2}"
           << "\\d{1,2}/\\d{1,2} "
           << "\\d{1,2}/\\d{1,2}/"
           << "\\d{1,2} \\d{1,2}"
           << "\\d{1,2} \\d{1,2} "
           << "\\d{1,2}-\\d{1,2}-"
           << "[a-zA-Z]{1,12}"
           << "[a-zA-Z]{1,12} "
           << "[a-zA-Z]{1,12} \\d{1,2}"
           << "[a-zA-Z]{1,12} \\d{1,2} ";
  monthDayYear << "\\d{1,2}/\\d{1,2}/\\d{1,4}"
               << "\\d{1,2}/\\d{1,2}/\\d{1,4} "
               << "\\d{1,2}-\\d{1,2}-\\d{1,4}"
               << "\\d{1,2}-\\d{1,2}-\\d{1,4} "
               << "\\d{1,2} \\d{1,2} \\d{1,4}"
               << "\\d{1,2} \\d{1,2} \\d{1,4} ";
  year << "\\d{1,4}"
       << "\\d{1,4} "
       << "\\d{2,4}/"
       << "\\d{2,4}-";
  yearMonth << "\\d{4}/\\d{1,2}"
            << "\\d{4}/\\d{1,2} "
            << "\\d{4}/\\d{1,2}/"
            << "\\d{4}-\\d{1,2}"
            << "\\d{4}-\\d{1,2} "
            << "\\d{4}-\\d{1,2}-"
            << "\\d{4} \\d{1,2}"
            << "\\d{4} \\d{1,2} "
            << "\\d{4}/[a-zA-Z]{1,12}"
            << "\\d{4}/[a-zA-Z]{1,12} "
            << "\\d{4}/[a-zA-Z]{1,12}/"
            << "\\d{4}-[a-zA-Z]{1,12}"
            << "\\d{4}-[a-zA-Z]{1,12} "
            << "\\d{4}-[a-zA-Z]{1,12}-"
            << "\\d{4} [a-zA-Z]{1,12}"
            << "\\d{4} [a-zA-Z]{1,12} ";

  // For every entry, the possible states leading up to the Acceptable states in m_formatsDateParseIncomplete are all included.
  // Potential day-month ambiguity for COORD_UNITS_DATE_SKIP gets treated as month/day.
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_SKIP] = skip + month + monthDay + monthDayYear + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_MONTH_DAY_YEAR] = skip + month + monthDay + monthDayYear + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_DAY_MONTH_YEAR] = skip + day + dayMonth + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_YEAR_MONTH_DAY] = skip + month + monthDay + monthDayYear + year + yearMonth;

  ENGAUGE_ASSERT (m_formatsDateParseIncomplete.count () == NUM_COORD_UNITS_DATE);

  QStringList hour, hourMinute, hourMinuteAmPm, hourMinuteSecond,  hourMinuteSecondAmPm;

  hour << "\\d{1,2}"
       << "\\d{1,2}:";
  hourMinute << "\\d{1,2}:\\d{1,2}"
             << "\\d{1,2}:\\d{1,2}:"
             << "\\d{1,2}:\\d{1,2} ";
  hourMinuteAmPm << "\\d{1,2}:\\d{1,2} [ap]";
  hourMinuteSecond << "\\d{1,2}:\\d{1,2}:\\d{1,2}"
                   << "\\d{1,2}:\\d{1,2}:\\d{1,2} ";
  hourMinuteSecondAmPm << "\\d{1,2}:\\d{1,2}:\\d{1,2} [ap]";

  // For every entry, the possible states leading up to the Acceptable states in m_formatsTimeParseIncomplete are all included.
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_SKIP] = skip +
                                                         hour +
                                                         hourMinute + hourMinuteAmPm +
                                                         hourMinuteSecond + hourMinuteSecondAmPm;
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_HOUR_MINUTE] = skip +
                                                                hour +
                                                                hourMinute + hourMinuteAmPm +
                                                                hourMinuteSecond + hourMinuteSecondAmPm;
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_HOUR_MINUTE_SECOND] = skip +
                                                                       hour +
                                                                       hourMinute + hourMinuteAmPm +
                                                                       hourMinuteSecond + hourMinuteSecondAmPm;

  ENGAUGE_ASSERT (m_formatsTimeParseIncomplete.count () == NUM_COORD_UNITS_TIME);
}

QValidator::State FormatDateTime::parseInput (CoordUnitsDate coordUnitsDate,
                                              CoordUnitsTime coordUnitsTime,
                                              const QString &string,
                                              unsigned long &value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::parseInput"
                              << " date=" << coordUnitsDateToString (coordUnitsDate).toLatin1().data()
                              << " time=" << coordUnitsTimeToString (coordUnitsTime).toLatin1().data()
                              << " string=" << string.toLatin1().data();

  const bool USE_QREGEXP = true, DO_NOT_USE_QREGEXP = false;

  QValidator::State state = QValidator::Invalid;

  // First see if value is acceptable
  bool success = false;
  dateTimeLookup (m_formatsDateParseAcceptable,
                  m_formatsTimeParseAcceptable,
                  coordUnitsDate,
                  coordUnitsTime,
                  string,
                  USE_QREGEXP,
                  value,
                  success);
  if (success) {

    state = QValidator::Acceptable;

  } else {

    // Not acceptable, but perhaps it is just incomplete
    dateTimeLookup (m_formatsDateParseIncomplete,
                    m_formatsTimeParseIncomplete,
                    coordUnitsDate,
                    coordUnitsTime,
                    string,
                    DO_NOT_USE_QREGEXP,
                    value,
                    success);
    if (success) {

      state = QValidator::Intermediate;

    }
  }

  return state;
}
