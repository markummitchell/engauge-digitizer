#ifndef LOGGING_EVENT_HH
#define LOGGING_EVENT_HH

#include "log4cpp/Priority.hh"
#include <string>

namespace log4cpp {

  class LoggingEvent
  {
  public:
    LoggingEvent (const std::string &category,
                  const std::string &message,
                  const std::string &ndc,
                  Priority::Value priority);
  };
}

#endif // LOGGING_EVENT_HH
