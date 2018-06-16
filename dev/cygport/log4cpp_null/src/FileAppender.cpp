#include "log4cpp/FileAppender.hh"

namespace log4cpp {

  FileAppender::FileAppender (const std::string &name) :
    LayoutAppender (name)
  {
  }

  FileAppender::~FileAppender ()
  {
  }
}
