#ifndef CMD_DELETE_H
#define CMD_DELETE_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

/// Command for deleting all selected Points.
class CmdDelete : public CmdAbstract
{
public:
  /// Single constructor.
  CmdDelete(MainWindow &mainWindow,
            Document &document,
            const QStringList &selectedPointIdentifiers);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdDelete();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphs;
};

#endif // CMD_DELETE_H
