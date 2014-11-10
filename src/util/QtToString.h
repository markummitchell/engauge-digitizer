#ifndef QT_ENUM_TO_STRING_H
#define QT_ENUM_TO_STRING_H

#include <QCursor>
#include <QString>

class QPointF;
class QTransform;

extern QString QPointFToString (const QPointF &pos);
extern QString QtCursorToString (Qt::CursorShape cursorShape);
extern QString QTransformToString (const QTransform &transform);

#endif // QT_ENUM_TO_STRING_H
