/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef JPEG2000_CALLBACKS_H
#define JPEG2000_CALLBACKS_H

extern void errorCallback (const char *msg,
                           void *clientData);
extern void infoCallback (const char *msg,
                          void *clientData);
extern void warningCallback (const char *msg,
                             void *clientData);

#endif // JPEG2000_CALLBACKS_H
