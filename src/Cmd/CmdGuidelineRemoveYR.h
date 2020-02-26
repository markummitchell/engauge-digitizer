/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GUIDELINE_REMOVE_Y_R_H
#define CMD_GUIDELINE_REMOVE_Y_R_H

#include "CmdAbstract.h"
#include "GuidelineValues.h"

class QXmlStreamReader;

/// Command for removing one Y/R Guideline value
class CmdGuidelineRemoveYR : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGuidelineRemoveYR(MainWindow &mainWindow,
                       Document &document,
                       const QString &identifier,
                       double oldBefore);

  /// Constructor for parsing error report file xml
  CmdGuidelineRemoveYR(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);

  virtual ~CmdGuidelineRemoveYR();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGuidelineRemoveYR();

  // Value
  QString m_identifier;
  double m_valueBefore;
};

#endif // CMD_GUIDELINE_REMOVE_Y_R_H
