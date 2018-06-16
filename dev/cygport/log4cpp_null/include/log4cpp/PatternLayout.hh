 #ifndef PATTERN_LAYOUT_HH
#define PATTERN_LAYOUT_HH

#include "log4cpp/Configurator.hh"
#include "log4cpp/Layout.hh"
#include <string>

namespace log4cpp {

  class LoggingEvent;

  /// Layout class
  class PatternLayout : public Layout
  {
  public:
    PatternLayout ();
    virtual ~PatternLayout ();

    virtual std::string format(const LoggingEvent &event);
    virtual void setConversionPattern (const std::string &conversionPattern) throw (ConfigureFailure);

  private:
    std::string m_conversionPattern;
  };
}

#endif // PATTERN_LAYOUT_HH
