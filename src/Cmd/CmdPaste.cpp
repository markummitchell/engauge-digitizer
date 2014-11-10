#include "CmdPaste.h"
#include "DataKey.h"
#include "Document.h"
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

CmdPaste::CmdPaste(MainWindow &mainWindow,
                   Document &document,
                   const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              "Paste")
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
