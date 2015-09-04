#include "Logger.h"
#include <QHash>
#include <QTransform>
#include "QtToString.h"

static QHash<int, QString> rolesAsStringsLookupTable; // For logging

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

    case Qt::BitmapCursor:
      return "Qt::BitmapCursor";
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

  QString str = QString ("%1   %2   %3   %4\n"
                         "%5   %6   %7   %8\n"
                         "%9   %10   %11   %12")
                .arg (INDENTATION_PAST_TIMESTAMP)
                .arg (transform.m11 (), FIELD_WIDTH)
                .arg (transform.m12 (), FIELD_WIDTH)
                .arg (transform.m13 (), FIELD_WIDTH)
                .arg (INDENTATION_PAST_TIMESTAMP)
                .arg (transform.m21 (), FIELD_WIDTH)
                .arg (transform.m22 (), FIELD_WIDTH)
                .arg (transform.m23 (), FIELD_WIDTH)
                .arg (INDENTATION_PAST_TIMESTAMP)
                .arg (transform.m31 (), FIELD_WIDTH)
                .arg (transform.m32 (), FIELD_WIDTH)
                .arg (transform.m33 (), FIELD_WIDTH);

  return str;
}

QString QXmlStreamReaderTokenTypeToString (QXmlStreamReader::TokenType tokenType)
{
  switch (tokenType) {
    case QXmlStreamReader::Characters:
      return "Characters";
    case QXmlStreamReader::Comment:
      return "Comment";
    case QXmlStreamReader::DTD:
      return "DTD";
    case QXmlStreamReader::EndDocument:
      return "EndDocument";
    case QXmlStreamReader::EndElement:
      return "EndElement";
    case QXmlStreamReader::EntityReference:
      return "EntityReference";
    case QXmlStreamReader::Invalid:
      return "Invalid";
    case QXmlStreamReader::NoToken:
      return "NoToken";
    case QXmlStreamReader::ProcessingInstruction:
      return "ProcessingInstruction";
    case QXmlStreamReader::StartDocument:
      return "StartDocument";
    case QXmlStreamReader::StartElement:
      return "StartElement";
  }

  return "<Unknown>";
}

QString roleAsString (int role)
{
  if (rolesAsStringsLookupTable.count () == 0) {

    // List from qnamespace.h
    rolesAsStringsLookupTable [Qt::AccessibleDescriptionRole] = "AccessibleDescriptionRole";
    rolesAsStringsLookupTable [Qt::AccessibleTextRole] = "AccessibleTextRole";
    rolesAsStringsLookupTable [Qt::BackgroundRole] = "BackgroundRole";
    rolesAsStringsLookupTable [Qt::BackgroundColorRole] = "BackgroundColorRole";
    rolesAsStringsLookupTable [Qt::CheckStateRole] = "CheckStateRole";
    rolesAsStringsLookupTable [Qt::DecorationRole] = "DecorationRole";
    rolesAsStringsLookupTable [Qt::DisplayRole] = "DisplayRole";
    rolesAsStringsLookupTable [Qt::EditRole] = "EditRole";
    rolesAsStringsLookupTable [Qt::FontRole] = "FontRole";
    rolesAsStringsLookupTable [Qt::ForegroundRole] = "ForegroundRole";
    rolesAsStringsLookupTable [Qt::InitialSortOrderRole] = "InitialSortOrderRole";
    rolesAsStringsLookupTable [Qt::SizeHintRole] = "SizeHintRole";
    rolesAsStringsLookupTable [Qt::StatusTipRole] = "StatusTipRole";
    rolesAsStringsLookupTable [Qt::TextAlignmentRole] = "TextAlignmentRole";
    rolesAsStringsLookupTable [Qt::TextColorRole] = "TextColorRole";
    rolesAsStringsLookupTable [Qt::ToolTipRole] = "ToolTipRole";
    rolesAsStringsLookupTable [Qt::UserRole] = "UserRole";
    rolesAsStringsLookupTable [Qt::WhatsThisRole] = "WhatsThisRole";
  }

  if (rolesAsStringsLookupTable.contains (role)) {

    return rolesAsStringsLookupTable [role];

  } else {

    return QString ("%1?").arg (role);

  }
}

QString rolesAsString (const QVector<int> &roles)
{
  QString str;

  for (int i = 0; i < roles.count (); i++) {
    if (i > 0) {
      str += ",";
    }
    str += roleAsString (roles [i]);
  }

  return str;
}
