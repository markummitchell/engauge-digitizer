#ifndef CMD_ADD_POINT_AXIS_H
#define CMD_ADD_POINT_AXIS_H

#include "CmdAbstract.h"
#include <QPointF>

/// Command for adding one axis point.
class CmdAddPointAxis : public CmdAbstract
{
 public:
  /// Single constructor.
  CmdAddPointAxis(MainWindow &mainWindow,
                  Document &document,
                  const QPointF &posScreen,
                  const QPointF &posGraph);
  virtual ~CmdAddPointAxis();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdAddPointAxis();

  QPointF m_posScreen;
  QPointF m_posGraph;
  QString m_identifierAdded; // Point that got added
};

#endif // CMD_ADD_POINT_AXIS_H
