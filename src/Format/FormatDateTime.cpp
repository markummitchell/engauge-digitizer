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
  for (itrDate = formatsDate.begin(); itrDate != formatsDate.end(); itrDate++) {

    QString formatDate = *itrDate;

    for (itrTime = formatsTime.begin(); itrTime != formatsTime.end(); itrTime++) {

      QString formatTime = *itrTime;

      QString formatDateTime = formatDate + " " + formatTime;
      formatDateTime = formatDateTime.trimmed (); // Remove leading/trailing blanks from skipped date or time

      if (!formatDateTime.isEmpty()) {

        // Try parsing according to the current format
        QDateTime dt = QDateTime::fromString (string,
                                              formatDateTime);

        LOG4CPP_DEBUG_S ((*mainCat)) << "FormatDateTime::dateTimeLookup"
                                     << " format=" << formatDateTime.toLatin1().data()
                                     << " isValid=" << (dt.isValid() ? "true" : "false");

        if (dt.isValid()) {

          success = true;
          value = dt.toTime_t();
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

  QStringList skip, day, dayMonth, month, monthDay, year, yearMonth;

  // COORD_UNITS_DATE_SKIP and COORD_UNITS_TIME_SKIP allow date/time respectively even when skipped,
  // although there can be ambiguity with between COORD_UNITS_DATE_MONTH_DAY_YEAR and COORD_UNITS_DATE_DAY_MONTH_YEAR
  skip << "";

  day << "d"
      << "dd/"
      << "dd-";
  dayMonth << "dd/M"
           << "dd/MM/"
           << "dd-MM-"
           << "dd/MMM/"
           << "dd-MMM-"
           << "dd MMM "
           << "dd/MMMM/"
           << "dd-MMMM-"
           << "dd MMMM ";
  month << "M"
        << "MM/"
        << "MMM "
        << "MMMM ";
  monthDay << "MM/dd/"
           << "MM-dd-"
           << "MMM dd "
           << "MMMM dd ";
  year << "y"
       << "yy/"
       << "yyyy-"
       << "yyyy/";
  yearMonth << "yyyy/M"
            << "yyyy-M"
            << "yyyy M"
            << "yyyy/MM/"
            << "yyyy-MM-"
            << "yyyy MM "
            << "yyyy/MMM/"
            << "yyyy-MMM-"
            << "yyyy MMM "
            << "yyyy/MMMM/"
            << "yyyy-MMMM-"
            << "yyyy MMMM ";

  // For every entry, the possible states leading up to the Acceptable states in m_formatsDateParseIncomplete are all included.
  // Potential day-month ambiguity for COORD_UNITS_DATE_SKIP gets treated as month/day.
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_SKIP] = skip + month + monthDay + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_MONTH_DAY_YEAR] = skip + month + monthDay + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_DAY_MONTH_YEAR] = skip + day + dayMonth + year + yearMonth;
  m_formatsDateParseIncomplete [COORD_UNITS_DATE_YEAR_MONTH_DAY] = skip + year + yearMonth;

  ENGAUGE_ASSERT (m_formatsDateParseIncomplete.count () == NUM_COORD_UNITS_DATE);

  QStringList hour, hourMinute, hourMinuteSecond;

  hour << "h" << "hh" << "hh:";
  hourMinute << "hh:m"
             << "hh:mm:"
             << "hh:mm ";
  hourMinuteSecond << "hh:mm:s"
                   << "hh:mm:ss ";

  // For every entry, the possible states leading up to the Acceptable states in m_formatsTimeParseIncomplete are all included.
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_SKIP] = skip + hour + hourMinute + hourMinuteSecond;
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_HOUR_MINUTE] = skip + hour + hourMinute + hourMinuteSecond;
  m_formatsTimeParseIncomplete [COORD_UNITS_TIME_HOUR_MINUTE_SECOND] = skip + hour + hourMinute + hourMinuteSecond;

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

  QValidator::State state = QValidator::Invalid;

  // First see if value is acceptable
  bool success = false;
  dateTimeLookup (m_formatsDateParseAcceptable,
                  m_formatsTimeParseAcceptable,
                  coordUnitsDate,
                  coordUnitsTime,
                  string,
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
                    value,
                    success);
    if (success) {

      state = QValidator::Intermediate;

    }
  }

  return state;
}
