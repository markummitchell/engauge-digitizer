#ifndef CONFIGURATOR_HH
#define CONFIGURATOR_HH

#include <string>
#include <stdexcept>

namespace log4cpp {

  class ConfigureFailure : public std::runtime_error
  {
  public:
    ConfigureFailure (const std::string &reason);
  };
}

#endif // CONFIGURATOR_HH
