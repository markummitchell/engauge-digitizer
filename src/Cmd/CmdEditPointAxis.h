#ifndef CMD_EDIT_POINT_AXIS_H
#define CMD_EDIT_POINT_AXIS_H

#include "CmdAbstract.h"
#include <QPointF>

/// Command for editing the graph coordinates one axis point. The screen coordinates are
/// handled by another command
class CmdEditPointAxis : public CmdAbstract
{
 public:
  /// Single constructor.
  CmdEditPointAxis(MainWindow &mainWindow,
                   Document &document,
                   const QString &pointIdentifier,
                   const QPointF &posGraphBefore,
                   const QPointF &posGraphAfter);
  virtual ~CmdEditPointAxis();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdEditPointAxis();

  QString m_pointIdentifier;
  QPointF m_posGraphBefore;
  QPointF m_posGraphAfter;
};

#endif // CMD_EDIT_POINT_AXIS_H
