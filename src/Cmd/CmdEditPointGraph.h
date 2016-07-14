/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_EDIT_POINT_GRAPH_H
#define CMD_EDIT_POINT_GRAPH_H

#include "CmdPointChangeBase.h"
#include <QPointF>
#include <QStringList>

class QXmlStreamReader;

/// Command for editing the graph coordinates of one or more graph points. The screen coordinates are
/// handled by another command
class CmdEditPointGraph : public CmdPointChangeBase
{
 public:
  /// Constructor for normal creation
  CmdEditPointGraph(MainWindow &mainWindow,
                    Document &document,
                    const QStringList &pointIdentifiers,
                    bool isX,
                    bool isY,
                    double x,
                    double y);

  /// Constructor for parsing error report file xml
  CmdEditPointGraph(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdEditPointGraph();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdEditPointGraph();

  QStringList m_pointIdentifiers;
  bool m_isX;
  bool m_isY;
  double m_x;
  double m_y;
};

#endif // CMD_EDIT_POINT_GRAPH_H
