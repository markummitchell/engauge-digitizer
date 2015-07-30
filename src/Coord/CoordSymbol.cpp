#include "CoordSymbol.h"

const int COORD_SYMBOL_DEGREES = 0260; // Ascii
const int COORD_SYMBOL_MINUTES = 0x2032; // Unicode value for QChar
const int COORD_SYMBOL_SECONDS = 0x2033; // Unicode value for QChar

const QChar THETA (QChar(0x98, 0x03));

const QString POLAR_UNITS_DEGREES = QString("Degrees (DDD.DDDDD") + QChar(0260) + QString (")");
const QString POLAR_UNITS_DEGREES_MINUTES = QString("Degrees Minutes (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                            QString(" MM.MMM") + QChar(COORD_SYMBOL_MINUTES) +
                                            QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                                    QString(" MM") + QChar(COORD_SYMBOL_MINUTES) +
                                                    QString(" SS.S") + QChar(COORD_SYMBOL_SECONDS) + QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW = QString("Degrees Minutes Seconds (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                                         QString(" MM") + QChar(COORD_SYMBOL_MINUTES) +
                                                         QString(" SS.S") + QChar(COORD_SYMBOL_SECONDS) + QString(" NSEW)");
const QString POLAR_UNITS_GRADIANS = "Gradians";
const QString POLAR_UNITS_RADIANS = "Radians";
const QString POLAR_UNITS_TURNS = "Turns";
