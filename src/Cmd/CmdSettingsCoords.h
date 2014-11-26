#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"
#include "DlgModelCoords.h"

/// Command for DlgSettingsCoords
class CmdSettingsCoords : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCoords(MainWindow &mainWindow,
                    Document &document,
                    const DlgModelCoords &modelCoordsBefore,
                    const DlgModelCoords &modelCoordsAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsCoords();

  DlgModelCoords m_modelCoordsBefore;
  DlgModelCoords m_modelCoordsAfter;
};

#endif // CMD_SETTINGS_COORDS_H
