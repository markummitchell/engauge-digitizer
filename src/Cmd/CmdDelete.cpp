#include "CmdDelete.h"
#include "DataKey.h"
#include "Document.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include <QtToString.h>

CmdDelete::CmdDelete(MainWindow &mainWindow,
                     Document &document,
                     const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              "Delete")
{
  QStringList selected;
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::CmdDelete"
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";

  QTextStream strCsv (&m_csv), strHtml (&m_html);
  document.exportToClipboard (selected,
                              mainWindow.transformIsDefined(),
                              strCsv,
                              strHtml,
                              m_curvesGraphs);
}

void CmdDelete::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdRedo";

  document().removePointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}

void CmdDelete::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDelete::cmdUndo";

  document().addPointsInCurvesGraphs (m_curvesGraphs);

  mainWindow().updateAfterCommand();
}
