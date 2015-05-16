#ifndef LOGGER_H
#define LOGGER_H

#include <log4cpp/Category.hh>
#include <QString>

extern log4cpp::Category *mainCat;

extern void initializeLogging (const QString &name,
                               const QString &filename,
                               bool isDebug);

// Indentation increments between successive levels of indentation
extern const QString INDENTATION_DELTA;

#endif // LOGGER_H
