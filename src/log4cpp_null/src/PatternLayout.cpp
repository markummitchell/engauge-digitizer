#include "log4cpp/LoggingEvent.hh"
#include "log4cpp/PatternLayout.hh"

using namespace log4cpp;
using namespace std;

PatternLayout::PatternLayout() :
  Layout()
{
}

PatternLayout::~PatternLayout()
{
}

string PatternLayout::format(const LoggingEvent &)
{
  string empty;
  return empty;
}

void PatternLayout::setConversionPattern (const std::string &conversionPattern)
{
  if (conversionPattern == "") {
    throw ConfigureFailure("Empty reason");
  }

  m_conversionPattern = conversionPattern;
}


