#ifndef CATEGORY_HH
#define CATEGORY_HH

#include "log4cpp/Appender.hh"
#include "log4cpp/CategoryStream.hh"
#include "log4cpp/convenience.h"
#include "log4cpp/Priority.hh"
#include <sstream>

namespace log4cpp
{

  /// Noop class that mimics class of the same name in log4cpp library
  class Category
  {
  public:
    Category();
    virtual ~Category();

    void addAppender (Appender *appender);

    /// Returns unused priority
    Priority::Value getPriority() const;

    static Category &getRoot();

    /// Returns a stream
    CategoryStream getStream(Priority::Value value);
    
    /// Stream that never gets used, as seen by inspection of convenience.h
    inline CategoryStream nullStream() { return getStream (Priority::NOTSET); }

    void setPriority (Priority::Value priority);

  private:

    static Category *m_category;
  };
}

#endif // CATEGORY_HH
