/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef QT_ENUM_TO_STRING_H
#define QT_ENUM_TO_STRING_H

#include <QCursor>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

class QLocale;
class QPointF;
class QTransform;

extern QString QPointFToString (const QPointF &pos);
extern QString QLocaleToString (const QLocale &locale);
extern QString QtCursorToString (Qt::CursorShape cursorShape);
extern QString QTransformToString (const QTransform &transform);
extern QString QXmlStreamReaderTokenTypeToString (QXmlStreamReader::TokenType tokenType);
extern QString roleAsString (int role);
extern QString rolesAsString (const QVector<int> &roles);

#endif // QT_ENUM_TO_STRING_H
