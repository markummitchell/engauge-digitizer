#ifndef CMD_CUT_H
#define CMD_CUT_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

/// Command for cutting all selected Points.
class CmdCut : public CmdAbstract
{
public:
  /// Single constructor.
  CmdCut(MainWindow &mainWindow,
         Document &document,
         const QStringList &selectedPointIdentifiers);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdCut();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphs;
};

#endif // CMD_CUT_H
