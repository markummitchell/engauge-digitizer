#include "EngaugeAssert.h"
#include "FormatDateTime.h"
#include "Logger.h"

FormatDateTime::FormatDateTime()
{
  loadFormatsFormat();
  loadFormatsParse();
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

void FormatDateTime::loadFormatsParse()
{
  // COORD_UNITS_DATE_SKIP and COORD_UNITS_TIME_SKIP allow date/time respectively even when skipped,
  // although there can be ambiguity with between COORD_UNITS_DATE_MONTH_DAY_YEAR and COORD_UNITS_DATE_DAY_MONTH_YEAR

  QStringList skip;

  skip << "";

  QStringList monthDayYear;
  QStringList dayMonthYear;
  QStringList yearMonthDay;

  monthDayYear << "MM/dd/yyyy" << "MM/dd/yy" 
               << "MM-dd-yyyy" << "MM-dd-yy" 
               << "MM/dd"
               << "MMM dd yyyy"
               << "MMM dd"
               << "MMMM dd yyyy"
               << "MMMM dd";
  dayMonthYear << "dd/MM/yyyy" << "dd/MM/yy"
               << "dd-MM-yyyy" << "dd-MM-yy"
               << "dd/MM"
               << "dd/MMM/yyyy" << "dd/MMM/yy"
               << "dd-MMM-yyyy" << "dd-MMM-yy"
               << "dd MMM yyyy" << "dd MMM yy"
               << "dd/MMMM/yyyy" << "dd/MMMM/yy"
               << "dd-MMMM-yyyy" << "dd-MMMM-yy"
               << "dd MMMM yyyy" << "dd MMMM yy";
  yearMonthDay << "yyyy/MM/dd" 
               << "yyyy-MM-dd"
               << "yyyy MM dd"
               << "yyyy/MMM/dd"
               << "yyyy-MMM-dd"
               << "yyyy MMM dd"
               << "yyyy/MMMM/dd"
               << "yyyy-MMMM-dd"
               << "yyyy MMMM dd";

  m_formatsDateParse [COORD_UNITS_DATE_SKIP] = skip + monthDayYear + yearMonthDay; // Day-month ambiguity gets treated as month/day
  m_formatsDateParse [COORD_UNITS_DATE_MONTH_DAY_YEAR] = skip + monthDayYear;
  m_formatsDateParse [COORD_UNITS_DATE_DAY_MONTH_YEAR] = skip + dayMonthYear;
  m_formatsDateParse [COORD_UNITS_DATE_YEAR_MONTH_DAY] = skip + yearMonthDay;

  ENGAUGE_ASSERT (m_formatsDateParse.count () == NUM_COORD_UNITS_DATE);

  QStringList hourMinute;
  QStringList hourMinuteSecond;
  QStringList hourMinutePm;
  QStringList hourMinuteSecondPm;

  hourMinute << "hh:mm";
  hourMinuteSecond << "HH:mm:ss";
  hourMinutePm << "hh:mmA"
               << "hh:mm A"
               << "hh:mma"
               << "hh:mm a";
  hourMinuteSecondPm << "hh:mm:ssA"
                     << "hh:mm:ss A"
                     << "hh:mm:ssa"
                     << "hh:mm:ss a";

  m_formatsTimeParse [COORD_UNITS_TIME_SKIP] = skip + hourMinute + hourMinuteSecond + hourMinutePm + hourMinuteSecondPm;
  m_formatsTimeParse [COORD_UNITS_TIME_HOUR_MINUTE] = skip + hourMinute + hourMinutePm;
  m_formatsTimeParse [COORD_UNITS_TIME_HOUR_MINUTE_SECOND] = skip + hourMinuteSecond + hourMinuteSecondPm;

  ENGAUGE_ASSERT (m_formatsTimeParse.count () == NUM_COORD_UNITS_TIME);
}

unsigned long FormatDateTime::parseInput (CoordUnitsDate coordUnitsDate,
                                          CoordUnitsTime coordUnitsTime,
                                          const QString &string,
                                          bool &success) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDateTime::parse"
                              << " date=" << coordUnitsDateToString (coordUnitsDate).toLatin1().data()
                              << " time=" << coordUnitsTimeToString (coordUnitsTime).toLatin1().data()
                              << " string=" << string.toLatin1().data();

  unsigned long value = 0;
  success = false;

  ENGAUGE_ASSERT (m_formatsDateParse.contains (coordUnitsDate));
  ENGAUGE_ASSERT (m_formatsTimeParse.contains (coordUnitsTime));

  QStringList formatsDate = m_formatsDateParse [coordUnitsDate];
  QStringList formatsTime = m_formatsTimeParse [coordUnitsTime];

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

        LOG4CPP_DEBUG_S ((*mainCat)) << "FormatDateTime::parse"
                                     << " format=" << formatDateTime.toLatin1().data()
                                     << " isValid=" << (dt.isValid() ? "true" : "false");
        
        if (dt.isValid()) {

          success = true;
          value = dt.toTime_t();
        }
      }
    }
  }

  return value;
}
