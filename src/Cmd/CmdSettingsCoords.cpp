#include "CmdSettingsCoords.h"
#include "DocumentModelCoords.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCoords::CmdSettingsCoords(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelCoords &modelCoordsBefore,
                                     const DocumentModelCoords &modelCoordsAfter) :
  CmdAbstract(mainWindow,
              document,
              "Coordinate settings"),
  m_modelCoordsBefore (modelCoordsBefore),
  m_modelCoordsAfter (modelCoordsAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::CmdSettingsCoords";
}

void CmdSettingsCoords::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdRedo";

  mainWindow().updateSettingsCoords(m_modelCoordsAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCoords::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdUndo";

  mainWindow().updateSettingsCoords(m_modelCoordsBefore);
  mainWindow().updateAfterCommand();
}
