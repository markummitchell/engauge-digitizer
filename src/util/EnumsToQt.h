#ifndef ENUMS_TO_QT_H
#define ENUMS_TO_QT_H

#include "ColorPalette.h"
#include <QColor>
#include <QString>
#include <QXmlStreamReader>

extern QColor ColorPaletteToQColor (ColorPalette color);
extern QString XmlReaderTokenTypeToString (QXmlStreamReader::TokenType tokenType);

#endif // ENUMS_TO_QT_H
