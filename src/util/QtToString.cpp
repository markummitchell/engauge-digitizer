/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include <QHash>
#include <QLocale>
#include <QTransform>
#include "QtToString.h"

static QHash<Qt::CursorShape, QString> cursorShapesLookupTable;
static QHash<int, QString> rolesAsStringsLookupTable;
static QHash<QXmlStreamReader::TokenType, QString> xmlTokenTypeLookupTable;

QString QPointFToString (const QPointF &pos)
{
  QString str = QString ("(%1, %2)")
                .arg (pos.x ())
                .arg (pos.y ());

  return str;
}

QString QRectFToString (const QRectF &rectF)
{
  QString str = QString ("(%1x%2+%3+%4)")
                .arg (rectF.width())
                .arg (rectF.height())
                .arg (rectF.x())
                .arg (rectF.y());

  return str;
}

QString QtCursorToString (Qt::CursorShape cursorShape)
{
  if (cursorShapesLookupTable.count () == 0) {

    // Initialize
    cursorShapesLookupTable [Qt::ArrowCursor] = "Qt::ArrowCursor";
    cursorShapesLookupTable [Qt::BitmapCursor] = "Qt::BitmapCursor";
    cursorShapesLookupTable [Qt::CrossCursor] = "Qt::CrossCursor";
    cursorShapesLookupTable [Qt::WaitCursor] = "Qt::WaitCursor";
  }

  if (cursorShapesLookupTable.contains (cursorShape)) {

    return cursorShapesLookupTable [cursorShape];

  } else {

    return "Qt::<unknown>";

  } 
}

QString QLocaleToString (const QLocale &locale)
{
  return QString ("%1/%2")
      .arg (QLocale::languageToString (locale.language()))
      .arg (QLocale::countryToString(locale.country()));
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
  if (xmlTokenTypeLookupTable.count () == 0) {

    // Initialize
    xmlTokenTypeLookupTable [QXmlStreamReader::Characters] = "Characters";
    xmlTokenTypeLookupTable [QXmlStreamReader::Comment] = "Comment";
    xmlTokenTypeLookupTable [QXmlStreamReader::DTD] = "DTD";
    xmlTokenTypeLookupTable [QXmlStreamReader::EndDocument] = "EndDocument";
    xmlTokenTypeLookupTable [QXmlStreamReader::EndElement] = "EndElement";
    xmlTokenTypeLookupTable [QXmlStreamReader::EntityReference] = "EntityReference";
    xmlTokenTypeLookupTable [QXmlStreamReader::Invalid] = "Invalid";
    xmlTokenTypeLookupTable [QXmlStreamReader::NoToken] = "NoToken";
    xmlTokenTypeLookupTable [QXmlStreamReader::ProcessingInstruction] = "ProcessingInstruction";
    xmlTokenTypeLookupTable [QXmlStreamReader::StartDocument] = "StartDocument";
    xmlTokenTypeLookupTable [QXmlStreamReader::StartElement] = "StartElement";
  }

  if (xmlTokenTypeLookupTable.contains (tokenType)) {

    return xmlTokenTypeLookupTable [tokenType];

  } else {

    return "<Unknown>";

  } 
}

QString roleAsString (int role)
{
  if (rolesAsStringsLookupTable.count () == 0) {

    // Initialize with list from qnamespace.h
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
