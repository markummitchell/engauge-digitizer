#include "EnumsToQt.h"

QColor ColorPaletteToQColor (ColorPalette color) {
  switch (color) {
    case COLOR_PALETTE_BLACK:
      return QColor (Qt::black);
      break;

    case COLOR_PALETTE_BLUE:
      return QColor (Qt::blue);
      break;

    case COLOR_PALETTE_CYAN:
      return QColor (Qt::cyan);
      break;

    case COLOR_PALETTE_GOLD:
      return QColor (255, 215, 0);
      break;

    case COLOR_PALETTE_GREEN:
      return QColor (Qt::green);
      break;

    case COLOR_PALETTE_MAGENTA:
      return QColor (255, 0, 255);
      break;

    case COLOR_PALETTE_RED:
      return QColor (Qt::red);
      break;

    case COLOR_PALETTE_YELLOW:
      return QColor (255, 255, 0);
      break;

    case COLOR_PALETTE_TRANSPARENT:
      return QColor (Qt::transparent);
      break;

    default:
      break;
  }

  Q_ASSERT (false);
  return QColor (Qt::black);
}

QString XmlReaderTokenTypeToString (QXmlStreamReader::TokenType tokenType)
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
