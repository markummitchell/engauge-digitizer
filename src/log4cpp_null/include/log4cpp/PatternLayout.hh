 #ifndef PATTERN_LAYOUT_HH
#define PATTERN_LAYOUT_HH

#include "log4cpp/Configurator.hh"
#include "log4cpp/Layout.hh"
#include <string>

namespace log4cpp {

  class LoggingEvent;

  /// Noop class that mimics the same class in the log4cpp library
  class PatternLayout : public Layout
  {
  public:
    /// Single constructor
    PatternLayout ();
    virtual ~PatternLayout ();

    /// Noop method for formatting an event
    virtual std::string format(const LoggingEvent &event);

    /// Noop method for setting the conversion pattern. This used to throw
    /// ConfigureFailure but newer compilers do not like explicit throws
    void setConversionPattern (const std::string &conversionPattern);

  private:
    std::string m_conversionPattern;
  };
}

#endif // PATTERN_LAYOUT_HH
