#include "CmdCopy.h"
#include "DataKey.h"
#include "Document.h"
#include "ExportToClipboard.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"

CmdCopy::CmdCopy(MainWindow &mainWindow,
                 Document &document,
                 const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              "Copy"),
  m_transformIsDefined (mainWindow.transformIsDefined())
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::CmdCopy"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";

  ExportToClipboard exportStrategy;
  QTextStream strCsv (&m_csv), strHtml (&m_html);
  exportStrategy.exportToClipboard (selected,
                                    mainWindow.transformIsDefined(),
                                    strCsv,
                                    strHtml,
                                    m_curvesGraphs);
}

void CmdCopy::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::cmdRedo";

  MimePoints *mimePoints;
  if (m_transformIsDefined) {
    mimePoints = new MimePoints (m_csv,
                                 m_html);
  } else {
    mimePoints = new MimePoints (m_csv);
  }

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setMimeData (mimePoints, QClipboard::Clipboard);

  mainWindow().updateAfterCommand();
}

void CmdCopy::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCopy::cmdUndo";

  mainWindow().updateAfterCommand();
}
