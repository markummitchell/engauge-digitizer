#ifndef CONFIGURATOR_HH
#define CONFIGURATOR_HH

#include <string>
#include <stdexcept>

namespace log4cpp {

  /// Noop class that mimics the same class in the log4cpp library
  class ConfigureFailure : public std::runtime_error
  {
  public:
    /// Single constructor
    ConfigureFailure (const std::string &reason);
  };
}

#endif // CONFIGURATOR_HH
