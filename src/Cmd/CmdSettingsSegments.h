#ifndef CMD_SETTINGS_SEGMENTS_H
#define CMD_SETTINGS_SEGMENTS_H

#include "CmdAbstract.h"
#include "DocumentModelSegments.h"

/// Command for DlgSettingsSegments
class CmdSettingsSegments : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsSegments(MainWindow &mainWindow,
                      Document &document,
                      const DocumentModelSegments &modelSegmentsBefore,
                      const DocumentModelSegments &modelSegmentsAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdSettingsSegments();

  DocumentModelSegments m_modelSegmentsBefore;
  DocumentModelSegments m_modelSegmentsAfter;
};

#endif // CMD_SETTINGS_SEGMENTS_H
