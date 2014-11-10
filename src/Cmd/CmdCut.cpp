#include "CmdCut.h"
#include "DataKey.h"
#include "Document.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"

CmdCut::CmdCut(MainWindow &mainWindow,
               Document &document,
               const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              "Cut"),
  m_transformIsDefined (mainWindow.transformIsDefined())
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::CmdCut"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";

  QTextStream strCsv (&m_csv), strHtml (&m_html);
  document.exportToClipboard (selected,
                              mainWindow.transformIsDefined(),
                              strCsv,
                              strHtml,
                              m_curvesGraphs);
}

void CmdCut::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::cmdRedo";

  MimePoints *mimePoints;
  if (m_transformIsDefined) {
    mimePoints = new MimePoints (m_csv,
                                 m_html);
  } else {
    mimePoints = new MimePoints (m_csv);
  }

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setMimeData (mimePoints, QClipboard::Clipboard);

  document().removePointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}

void CmdCut::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCut::cmdUndo";

  document().addPointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}
