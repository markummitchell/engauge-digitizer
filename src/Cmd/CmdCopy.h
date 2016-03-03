/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_COPY_H
#define CMD_COPY_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

class QXmlStreamReader;

/// Command for moving all selected Points by a specified translation.
class CmdCopy : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdCopy(MainWindow &mainWindow,
          Document &document,
          const QStringList &selectedPointIdentifiers);

  /// Constructor for parsing error report file xml
  CmdCopy(MainWindow &mainWindow,
          Document &document,
          const QString &cmdDescription,
          QXmlStreamReader &reader);

  virtual ~CmdCopy();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdCopy();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphs;
};

#endif // CMD_COPY_H
