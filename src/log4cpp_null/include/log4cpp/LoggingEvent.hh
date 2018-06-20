#ifndef LOGGING_EVENT_HH
#define LOGGING_EVENT_HH

#include "log4cpp/Priority.hh"
#include <string>

namespace log4cpp {

  /// Noop class that mimics the same class in the log4cpp library
  class LoggingEvent
  {
  public:
    /// Single constructor
    LoggingEvent (const std::string &category,
                  const std::string &message,
                  const std::string &ndc,
                  Priority::Value priority);
  };
}

#endif // LOGGING_EVENT_HH
