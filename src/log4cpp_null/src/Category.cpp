#include "log4cpp/Category.hh"

namespace log4cpp {

  Category *Category::m_category = nullptr;

  Category::Category()
  {
  }

  Category::~Category()
  {
  }

  void Category::addAppender (Appender *)
  {
  }

  Priority::Value Category::getPriority () const
  {
    return Priority::NOTSET;
  }

  Category &Category::getRoot()
  {
    if (m_category == nullptr) {
      m_category = new Category();
    }

    return *m_category;
  }

  CategoryStream Category::getStream (Priority::Value)
  {
    return CategoryStream (*this, Priority::NOTSET);
  }

  void Category::setPriority (Priority::Value)
  {
  }
}
