#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"
#include "DocumentModelCoords.h"

/// Command for DlgSettingsCoords
class CmdSettingsCoords : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCoords(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelCoords &modelCoordsBefore,
                    const DocumentModelCoords &modelCoordsAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCoords();

  DocumentModelCoords m_modelCoordsBefore;
  DocumentModelCoords m_modelCoordsAfter;
};

#endif // CMD_SETTINGS_COORDS_H
