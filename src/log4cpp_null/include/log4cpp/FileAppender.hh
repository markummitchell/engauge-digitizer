#ifndef FILE_APPENDER_HH
#define FILE_APPENDER_HH

#include "log4cpp/LayoutAppender.hh"
#include <string>

namespace log4cpp {

  /// Noop class that mimics the same class in log4cpp library
  class FileAppender : public LayoutAppender
  {
  public:
    /// Single constructor
    FileAppender(const std::string &name);
    virtual ~FileAppender();
  };
}

#endif // FILE_APPENDER_HH
