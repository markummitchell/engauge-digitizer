#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"
#include "DocumentModelCoords.h"

class QXmlStreamReader;

/// Command for DlgSettingsCoords
class CmdSettingsCoords : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCoords(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelCoords &modelCoordsBefore,
                    const DocumentModelCoords &modelCoordsAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsCoords(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsCoords();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCoords();

  DocumentModelCoords m_modelCoordsBefore;
  DocumentModelCoords m_modelCoordsAfter;
};

#endif // CMD_SETTINGS_COORDS_H
