#ifndef QT_ENUM_TO_STRING_H
#define QT_ENUM_TO_STRING_H

#include <QCursor>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

class QPointF;
class QTransform;

extern QString QPointFToString (const QPointF &pos);
extern QString QtCursorToString (Qt::CursorShape cursorShape);
extern QString QTransformToString (const QTransform &transform);
extern QString QXmlStreamReaderTokenTypeToString (QXmlStreamReader::TokenType tokenType);
extern QString roleAsString (int role);
extern QString rolesAsString (const QVector<int> &roles);

#endif // QT_ENUM_TO_STRING_H
