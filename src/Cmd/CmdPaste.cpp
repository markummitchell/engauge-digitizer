#include "CmdPaste.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QGraphicsItem>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Paste");

CmdPaste::CmdPaste(MainWindow &mainWindow,
                   Document &document,
                   const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
    m_copiedPoints [selectedPointIdentifier] = true;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdPaste::CmdPaste"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";
}

CmdPaste::CmdPaste (MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPaste::CmdPaste";

  QXmlStreamAttributes attributes = reader.attributes();
}

CmdPaste::~CmdPaste ()
{
}

void CmdPaste::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPaste::cmdRedo"
                              << " pasting=" << m_copiedPoints.count ();

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setMimeData (&m_mimePoints, QClipboard::Clipboard);

  mainWindow().updateAfterCommand();
}

void CmdPaste::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPaste::cmdUndo"
                              << " pasting=" << m_copiedPoints.count ();

  mainWindow().updateAfterCommand();
}

void CmdPaste::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_PASTE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeStartElement(DOCUMENT_SERIALIZE_IDENTIFIERS);
  PointIdentifiers::const_iterator itr;
  for (itr = m_copiedPoints.begin(); itr != m_copiedPoints.end (); itr++) {
    QString identifier = itr.key();
    bool value = itr.value();
    writer.writeStartElement (DOCUMENT_SERIALIZE_IDENTIFIER);
    writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER_NAME, identifier);
    writer.writeAttribute(DOCUMENT_SERIALIZE_COPIED,
                          value ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
    writer.writeEndElement();
  }
  writer.writeEndElement();
  writer.writeEndElement();
}
