#ifndef CMD_EDIT_POINT_AXIS_H
#define CMD_EDIT_POINT_AXIS_H

#include "CmdAbstract.h"
#include <QPointF>

class QXmlStreamReader;

/// Command for editing the graph coordinates one axis point. The screen coordinates are
/// handled by another command
class CmdEditPointAxis : public CmdAbstract
{
 public:
  /// Constructor for normal creation
  CmdEditPointAxis(MainWindow &mainWindow,
                   Document &document,
                   const QString &pointIdentifier,
                   const QPointF &posGraphBefore,
                   const QPointF &posGraphAfter);

  /// Constructor for parsing error report file xml
  CmdEditPointAxis(MainWindow &mainWindow,
                   Document &document,
                   const QString &cmdDescription,
                   QXmlStreamReader &reader);

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
