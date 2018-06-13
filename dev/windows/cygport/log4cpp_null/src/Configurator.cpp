#include "log4cpp/Configurator.hh"

namespace log4cpp {

  ConfigureFailure::ConfigureFailure (const std::string &reason) :
    std::runtime_error (reason)
  {
  }
}
