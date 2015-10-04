#include "Jpeg2000Callbacks.h"
#include "Logger.h"

void errorCallback (const char *msg,
                    void */* clientData */) 
{
  LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000Callbacks::errorCallback " << msg;
}

void infoCallback (const char *msg,
                   void */* clientData */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Jpeg2000Callbacks::infoCallback " << msg;
}

void warningCallback (const char *msg,
                      void */* clientData */)
{
  LOG4CPP_WARN_S ((*mainCat)) << "Jpeg2000Callbacks::warningCallback " << msg;
}
