#include "EnumsToQt.h"
#include "Logger.h"
#include "Xml.h"

QXmlStreamReader::TokenType loadNextFromReader (QXmlStreamReader &reader)
{
  QXmlStreamReader::TokenType tokenType = reader.readNext();

  LOG4CPP_DEBUG_S ((*mainCat)) << "loadNextFromReader "
                               << " tokenType=" << XmlReaderTokenTypeToString (tokenType).toLatin1().data()
                               << " tag=" << reader.name().toLatin1().data();

  return tokenType;
}
