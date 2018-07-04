#ifndef APPENDER_HH
#define APPENDER_HH

namespace log4cpp {

  /// Noop class that mimics the same class in the log4cpp library
  class Appender
  {
  public:
    virtual ~Appender();

  };
}

#endif // APPENDER_HH
