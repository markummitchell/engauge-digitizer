/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
