#include "Logger.h"
#include <QFileDevice>
#include <QMessageBox>
#include "QtToString.h"
#include "Xml.h"

QXmlStreamReader::TokenType loadNextFromReader (QXmlStreamReader &reader)
{
  QXmlStreamReader::TokenType tokenType = reader.readNext();

  LOG4CPP_DEBUG_S ((*mainCat)) << "loadNextFromReader "
                               << " tokenType=" << QXmlStreamReaderTokenTypeToString (tokenType).toLatin1().data()
                               << " tag=" << reader.name().toLatin1().data();

  return tokenType;
}

void xmlExitWithError (QXmlStreamReader &reader,
                           const QString &message)
{
  // Try to extract as much useful context as possible
  QString context;
  QFileDevice *fileDevice = dynamic_cast<QFileDevice*> (reader.device());
  if (fileDevice == 0) {

    context = QString ("String at line %1: ")
              .arg (reader.lineNumber());

  } else {

    context = QString ("File %1 at line %2: ")
              .arg (fileDevice->fileName())
              .arg (reader.lineNumber());

  }

  // Context plus original message gets displayed
  QString adornedMsg = QString ("%1%2. Quitting")
                       .arg (context)
                       .arg (message);

  QMessageBox::critical (0,
                         "Error reading xml",
                         adornedMsg);

  LOG4CPP_ERROR_S ((*mainCat)) << "xmlExitWithError error='" << adornedMsg.toLatin1().data() << "'";

  exit (-1);
}
