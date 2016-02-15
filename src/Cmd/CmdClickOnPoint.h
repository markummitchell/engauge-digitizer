#ifndef CMD_CLICK_ON_POINT_H
#define CMD_CLICK_ON_POINT_H

#include "CmdAbstract.h"
#include <QPointF>

class QXmlStreamReader;

/// Command for clicking on a point. The effect will be as if a click had been made on the GraphicsView
class CmdClickOnPoint : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdClickOnPoint(MainWindow &mainWindow,
                  Document &document,
                  const QPointF &point);

  /// Constructor for parsing error report file xml
  CmdClickOnPoint(MainWindow &mainWindow,
                  Document &document,
                  const QString &cmdDescription,
                  QXmlStreamReader &reader);

  virtual ~CmdClickOnPoint();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdClickOnPoint();

  QPointF m_point;
};

#endif // CMD_CLICK_ON_POINT_H
