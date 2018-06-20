#ifndef PRIORITY_HH
#define PRIORITY_HH

namespace log4cpp {

  /// This class provides importance levels for categorizing log messages
  class Priority {
  public:
    /// Enum for debug levels
    typedef enum {
      EMERG  = 0,
      FATAL  = 0,
      ALERT  = 100,
      CRIT   = 200,
      ERROR  = 300,
      WARN   = 400,
      NOTICE = 500,
      INFO   = 600,
      DEBUG  = 700,
      NOTSET = 800
    } PriorityLevel;

    /// Priority level
    typedef int Value;
  };  
}

#endif // PRIORITY_HH
