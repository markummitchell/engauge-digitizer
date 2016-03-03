/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdPaste.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
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
    m_copiedPoints.setKeyValue (selectedPointIdentifier, true);
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

  m_copiedPoints.loadXml (reader);
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
  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateAfterCommand();
  resetSelection(m_copiedPoints);
}

void CmdPaste::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPaste::cmdUndo"
                              << " pasting=" << m_copiedPoints.count ();

  mainWindow().updateAfterCommand();
  resetSelection(m_copiedPoints);
}

void CmdPaste::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_PASTE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_copiedPoints.saveXml (writer);
  writer.writeEndElement();
}
