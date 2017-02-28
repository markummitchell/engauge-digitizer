/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_ADD_SCALE_H
#define CMD_ADD_SCALE_H

#include "CmdPointChangeBase.h"
#include <QPointF>

class QXmlStreamReader;

/// Command for adding one scale point.
class CmdAddScale : public CmdPointChangeBase
{
 public:
  /// Constructor for normal creation
  CmdAddScale(MainWindow &mainWindow,
              Document &document,
              const QPointF &posScreen0,
              const QPointF &posScreen1,
              double scaleLength,
              double ordinal0,
              double ordinal1);

  /// Constructor for parsing error report file xml
  CmdAddScale(MainWindow &mainWindow,
              Document &document,
              const QString &cmdDescription,
              QXmlStreamReader &reader);

  virtual ~CmdAddScale();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdAddScale();

  QPointF m_posScreen0;
  QPointF m_posScreen1;
  double m_scaleLength;
  QString m_identifierAdded0; // First point that got added
  QString m_identifierAdded1; // Second point that got added
  double m_ordinal0;
  double m_ordinal1;
};

#endif // CMD_ADD_SCALE_H
