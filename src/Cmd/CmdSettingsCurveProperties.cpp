#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCurveProperties::CmdSettingsCurveProperties(MainWindow &mainWindow,
                                                       Document &document,
                                                       DlgModelCurveProperties &modelCurveProperties) :
  CmdAbstract(mainWindow,
              document,
              "Curve Properties settings"),
  m_modelCurveProperties (modelCurveProperties)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
}

void CmdSettingsCurveProperties::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdRedo";

  mainWindow().updateCurveProperties();
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  mainWindow().updateCurveProperties();
  mainWindow().updateAfterCommand();
}
