#ifndef PROPERTY_CONFIGURATOR_HH
#define PROPERTY_CONFIGURATOR_HH

#include "log4cpp/LayoutAppender.hh"
#include <string>

namespace log4cpp {

  /// Property configuration
  class PropertyConfigurator
  {
  public:
    static void configure (const std::string &initFilename);
  };
}

#endif // PROPERTY_CONFIGURATOR_HH
