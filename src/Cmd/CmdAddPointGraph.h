#ifndef CMD_ADD_POINT_GRAPH_H
#define CMD_ADD_POINT_GRAPH_H

#include "CmdAbstract.h"
#include <QPointF>

/// Command for adding one graph point.
class CmdAddPointGraph : public CmdAbstract
{
 public:
  /// Single constructor.
  CmdAddPointGraph(MainWindow &mainWindow,
                   Document &document,
                   const QString &curveName,
                   const QPointF &posScreen);
  virtual ~CmdAddPointGraph();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdAddPointGraph();

  const QString m_curveName;
  QPointF m_posScreen;
  QString m_identifierAdded; // Point that got added
};

#endif // CMD_ADD_POINT_GRAPH_H
