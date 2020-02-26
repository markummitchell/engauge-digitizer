/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GUIDELINE_REMOVE_X_T_H
#define CMD_GUIDELINE_REMOVE_X_T_H

#include "CmdAbstract.h"
#include "GuidelineValues.h"

class QXmlStreamReader;

/// Command for removing one X/T Guideline value
class CmdGuidelineRemoveXT : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGuidelineRemoveXT(MainWindow &mainWindow,
                       Document &document,
                       const QString &identifier,
                       double valueBefore);

  /// Constructor for parsing error report file xml
  CmdGuidelineRemoveXT(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);

  virtual ~CmdGuidelineRemoveXT();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGuidelineRemoveXT();

  // Value
  QString m_identifier;
  double m_valueBefore;
};

#endif // CMD_GUIDELINE_REMOVE_X_T_H
