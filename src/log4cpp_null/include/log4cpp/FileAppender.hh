#ifndef FILE_APPENDER_HH
#define FILE_APPENDER_HH

#include "log4cpp/LayoutAppender.hh"
#include <string>

namespace log4cpp {

  class FileAppender : public LayoutAppender
  {
  public:
    FileAppender(const std::string &name);
    virtual ~FileAppender();
  };
}

#endif // FILE_APPENDER_HH
