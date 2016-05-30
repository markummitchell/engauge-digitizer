/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_CUT_H
#define CMD_CUT_H

#include "CmdPointChangeBase.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

class QXmlStreamReader;

/// Command for cutting all selected Points.
class CmdCut : public CmdPointChangeBase
{
public:
  /// Constructor for normal creation
  CmdCut(MainWindow &mainWindow,
         Document &document,
         const QStringList &selectedPointIdentifiers);

  /// Constructor for parsing error report file xml
  CmdCut(MainWindow &mainWindow,
         Document &document,
         const QString &cmdDescription,
         QXmlStreamReader &reader);

  virtual ~CmdCut();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdCut();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphsRemoved;

};

#endif // CMD_CUT_H
