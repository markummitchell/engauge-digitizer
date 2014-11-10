#include <QTransform>
#include "QtToString.h"

QString QPointFToString (const QPointF &pos)
{
  QString str = QString ("(%1, %2)")
                .arg (pos.x ())
                .arg (pos.y ());

  return str;
}

QString QtCursorToString (Qt::CursorShape cursorShape)
{
  switch (cursorShape) {
    case Qt::ArrowCursor:
      return "Qt::ArrowCursor";
      break;

    case Qt::CrossCursor:
      return "Qt::CrossCursor";
      break;

    case Qt::WaitCursor:
      return "Qt::WaitCursor";
      break;

    default:
      return "Qt::<unknown>";
      break;
  }
}

QString QTransformToString (const QTransform &transform)
{
  const int FIELD_WIDTH = 12;

  QString str = QString ("   %1   %2   %3\n"
                         "   %4   %5   %6\n"
                         "   %7   %8   %9\n")
                 .arg (transform.m11 (), FIELD_WIDTH)
                 .arg (transform.m12 (), FIELD_WIDTH)
                 .arg (transform.m13 (), FIELD_WIDTH)
                 .arg (transform.m21 (), FIELD_WIDTH)
                 .arg (transform.m22 (), FIELD_WIDTH)
                 .arg (transform.m23 (), FIELD_WIDTH)
                 .arg (transform.m31 (), FIELD_WIDTH)
                 .arg (transform.m32 (), FIELD_WIDTH)
                 .arg (transform.m33 (), FIELD_WIDTH);

  return str;
}
