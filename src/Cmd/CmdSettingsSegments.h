#ifndef CMD_SETTINGS_SEGMENTS_H
#define CMD_SETTINGS_SEGMENTS_H

#include "CmdAbstract.h"
#include "DlgModelSegments.h"

/// Command for DlgSettingsSegments
class CmdSettingsSegments : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsSegments(MainWindow &mainWindow,
                      Document &document,
                      const DlgModelSegments &modelSegmentsBefore,
                      const DlgModelSegments &modelSegmentsAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsSegments();

  DlgModelSegments m_modelSegmentsBefore;
  DlgModelSegments m_modelSegmentsAfter;
};

#endif // CMD_SETTINGS_SEGMENTS_H
