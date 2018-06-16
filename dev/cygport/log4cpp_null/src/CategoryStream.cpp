#include "log4cpp/Category.hh"
#include "log4cpp/CategoryStream.hh"

namespace log4cpp {

  CategoryStream::CategoryStream(Category &category,
                                 Priority::Value) :
    m_category (category)
  {
  }

  CategoryStream::~CategoryStream()
  {
  }
}



