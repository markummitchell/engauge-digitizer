#ifndef LOGGER_H
#define LOGGER_H

#include <log4cpp/Category.hh>
#include <QString>

extern log4cpp::Category *mainCat;

extern void initializeLogging (const QString &name,
                               const QString &filename);

#endif // LOGGER_H
