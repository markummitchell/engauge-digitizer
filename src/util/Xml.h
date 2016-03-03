#ifndef XML_H
#define XML_H

#include <QString>
#include <QXmlStreamReader>

/// Load next token from xml reader
extern QXmlStreamReader::TokenType loadNextFromReader(QXmlStreamReader &reader);

/// Show specified message for an error while reading xml, then quit. The reader
/// will provide filename
/// (if available) and line number
extern void xmlExitWithError(QXmlStreamReader &reader, const QString &message);

#endif // XML_H
