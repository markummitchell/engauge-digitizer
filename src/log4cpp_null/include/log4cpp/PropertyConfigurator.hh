#ifndef PROPERTY_CONFIGURATOR_HH
#define PROPERTY_CONFIGURATOR_HH

#include "log4cpp/LayoutAppender.hh"
#include <string>

namespace log4cpp {

  /// Noop class that mimics the same class in the log4cpp library
  class PropertyConfigurator
  {
  public:
    /// Noop method for configuration
    static void configure (const std::string &initFilename);
  };
}

#endif // PROPERTY_CONFIGURATOR_HH
