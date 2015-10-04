#ifndef JPEG2000_CALLBACKS_H
#define JPEG2000_CALLBACKS_H

extern void errorCallback (const char *msg,
                           void *clientData);
extern void infoCallback (const char *msg,
                          void *clientData);
extern void warningCallback (const char *msg,
                             void *clientData);

#endif // JPEG2000_CALLBACKS_H
