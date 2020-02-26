#ifndef CATEGORY_STREAM_HH
#define CATEGORY_STREAM_HH

#include <ios>
#include "log4cpp/Priority.hh"

namespace log4cpp {

  class Category;
  class CategoryStream;

  CategoryStream &eol (CategoryStream &os);

  /// Streaming of simple types and objects to a category
  class CategoryStream
  {
  public:
    /// Single constructor
    CategoryStream(Category &category,
                   Priority::Value priority);

    virtual ~CategoryStream();

    /// Return useless value
    inline Category &getCategory() const { return m_category; }

    /// Return useless value
    inline Priority::Value getPriority () {
      return m_priority;
    }

    /// Noop
    void flush ();

    /// Stream of arbitrary types and objects
    template<typename T>
    CategoryStream &operator<<(const T&) {
      return *this;
    }

    /// Noop insertion method for character
    CategoryStream &operator<<(const char*) {
      return *this;
    }

    /// Noop insertion method for string
    CategoryStream &operator<<(const std::string &) {
      return *this;
    }

    /// Noop method to get width
    std::streamsize width(std::streamsize wide);

  private:

    Category &m_category;
    Priority::Value m_priority;
  };
}

#endif // CATEGORY_STREAM_HH
