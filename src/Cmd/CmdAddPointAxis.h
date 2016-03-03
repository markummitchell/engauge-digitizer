/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_ADD_POINT_AXIS_H
#define CMD_ADD_POINT_AXIS_H

#include "CmdAbstract.h"
#include <QPointF>

class QXmlStreamReader;

/// Command for adding one axis point.
class CmdAddPointAxis : public CmdAbstract
{
 public:
  /// Constructor for normal creation
  CmdAddPointAxis(MainWindow &mainWindow,
                  Document &document,
                  const QPointF &posScreen,
                  const QPointF &posGraph,
                  double ordinal,
                  bool isXOnly);

  /// Constructor for parsing error report file xml
  CmdAddPointAxis(MainWindow &mainWindow,
                  Document &document,
                  const QString &cmdDescription,
                  QXmlStreamReader &reader);

  virtual ~CmdAddPointAxis();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdAddPointAxis();

  QPointF m_posScreen;
  QPointF m_posGraph;
  QString m_identifierAdded; // Point that got added
  double m_ordinal;
  bool m_isXOnly;
};

#endif // CMD_ADD_POINT_AXIS_H
