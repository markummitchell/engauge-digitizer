#ifndef LAYOUT_APPENDER_HH
#define LAYOUT_APPENDER_HH

#include "log4cpp/Appender.hh"
#include <string>

namespace log4cpp {

  class Layout;

  class LayoutAppender : public Appender
  {
  public:
    LayoutAppender(const std::string &);
    virtual ~LayoutAppender();

    virtual void setLayout(Layout *layout) = 0;
  };
}

#endif // LAYOUT_APPENDER_HH
