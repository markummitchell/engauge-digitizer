#ifndef LAYOUT_HH
#define LAYOUT_HH

#include <string>

namespace log4cpp {

  class LoggingEvent;

  /// Noop version that mimics the same class in the log4cpp library
  class Layout
  {
  public:
    /// Single constructor
    Layout();
    virtual ~Layout();

    /// Noop method that would format an event
    virtual std::string format(const LoggingEvent &event) = 0;
  };
}

#endif // LAYOUT_HH
