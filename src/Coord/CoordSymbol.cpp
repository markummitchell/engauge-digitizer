#include "CoordSymbol.h"

const int COORD_SYMBOL_DEGREES = 0260; // Ascii
const int COORD_SYMBOL_MINUTES_PRIME = 0x2032; // Unicode value for QChar
const int COORD_SYMBOL_MINUTES_APOSTROPHE = 0xb4; // Ascii
const int COORD_SYMBOL_SECONDS_DOUBLE_PRIME = 0x2033; // Unicode value for QChar
const int COORD_SYMBOL_SECONDS_QUOTATIONS = 0x22; // Ascii

const QChar THETA (QChar(0x98, 0x03));

const QString POLAR_UNITS_DEGREES = QString("Degrees (DDD.DDDDD") + QChar(0260) + QString (")");
const QString POLAR_UNITS_DEGREES_MINUTES = QString("Degrees Minutes (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                            QString(" MM.MMM") + QChar(COORD_SYMBOL_MINUTES_PRIME) +
                                            QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                                    QString(" MM") + QChar(COORD_SYMBOL_MINUTES_PRIME) +
                                                    QString(" SS.S") + QChar(COORD_SYMBOL_SECONDS_DOUBLE_PRIME) + QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS_NSEW = QString("Degrees Minutes Seconds (DDD") + QChar(COORD_SYMBOL_DEGREES) +
                                                         QString(" MM") + QChar(COORD_SYMBOL_MINUTES_PRIME) +
                                                         QString(" SS.S") + QChar(COORD_SYMBOL_SECONDS_DOUBLE_PRIME) + QString(" NSEW)");
const QString POLAR_UNITS_GRADIANS = "Gradians";
const QString POLAR_UNITS_RADIANS = "Radians";
const QString POLAR_UNITS_TURNS = "Turns";
