#ifndef CMD_MOVE_BY_H
#define CMD_MOVE_BY_H

#include "CmdAbstract.h"
#include <QHash>
#include <QPointF>
#include <QStringList>

typedef QHash<QString, bool> PointIdentifiers;

/// Command for moving all selected Points by a specified translation.
class CmdMoveBy : public CmdAbstract
{
public:
  /// Single constructor.
  CmdMoveBy(MainWindow &mainWindow,
            Document &document,
            const QPointF &deltaScreen,
            const QString &moveText,
            const QStringList &selectedPointIdentifiers);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdMoveBy();

  void moveBy (const QPointF &deltaScreen);

  QPointF m_deltaScreen;
  PointIdentifiers m_movedPoints;
};

#endif // CMD_MOVE_BY_H
