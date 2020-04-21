/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GUIDELINE_VIEW_STATE_H
#define CMD_GUIDELINE_VIEW_STATE_H

#include "CmdAbstract.h"
#include "GuidelineViewState.h"

class QXmlStreamReader;

/// Command for changing the View / Guidelines state
class CmdGuidelineViewState : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGuidelineViewState(MainWindow &mainWindow,
                       Document &document,
                       GuidelineViewState stateBefore,
                       GuidelineViewState stateAfter);
  
  /// Constructor for parsing error report file xml
  CmdGuidelineViewState(MainWindow &mainWindow,
                     Document &document,
                     const QString &cmdDescription,
                     QXmlStreamReader &reader);

  virtual ~CmdGuidelineViewState();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGuidelineViewState();

  // Values
  GuidelineViewState m_stateBefore;
  GuidelineViewState m_stateAfter;
};

#endif // CMD_GUIDELINE_VIEW_STATE_H
