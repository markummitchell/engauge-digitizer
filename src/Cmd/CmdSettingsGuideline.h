/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_GUIDELINE_H
#define CMD_SETTINGS_GUIDELINE_H

#include "CmdAbstract.h"
#include "DocumentModelGuideline.h"

class QXmlStreamReader;

/// Command for DlgSettingsGuideline
class CmdSettingsGuideline : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsGuideline(MainWindow &mainWindow,
                       Document &document,
                       const DocumentModelGuideline &modelGuidelineBefore,
                       const DocumentModelGuideline &modelGuidelineAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsGuideline(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);

  virtual ~CmdSettingsGuideline();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsGuideline();

  DocumentModelGuideline m_modelGuidelineBefore;
  DocumentModelGuideline m_modelGuidelineAfter;
};

#endif // CMD_SETTINGS_GUIDELINE_H
