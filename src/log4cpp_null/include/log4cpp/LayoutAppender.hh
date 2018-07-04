#ifndef LAYOUT_APPENDER_HH
#define LAYOUT_APPENDER_HH

#include "log4cpp/Appender.hh"
#include <string>

namespace log4cpp {

  class Layout;

  /// Noop class that mimics the same class in the log4cpp library
  class LayoutAppender : public Appender
  {
  public:
    /// Single constructor
    LayoutAppender(const std::string &);
    virtual ~LayoutAppender();

    /// Set the layout for this Appender
    virtual void setLayout(Layout *layout) = 0;
  };
}

#endif // LAYOUT_APPENDER_HH
