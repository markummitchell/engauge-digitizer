#ifndef LAYOUT_HH
#define LAYOUT_HH

#include <string>

namespace log4cpp {

  class LoggingEvent;

  class Layout
  {
  public:
    Layout();
    virtual ~Layout();

    virtual std::string format(const LoggingEvent &event) = 0;
  };
}

#endif // LAYOUT_HH
