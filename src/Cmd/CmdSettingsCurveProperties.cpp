#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCurveProperties::CmdSettingsCurveProperties(MainWindow &mainWindow,
                                                       Document &document,
                                                       const DlgModelCurveProperties &modelCurvePropertiesBefore,
                                                       const DlgModelCurveProperties &modelCurvePropertiesAfter) :
  CmdAbstract(mainWindow,
              document,
              "Curve Properties settings"),
  m_modelCurvePropertiesBefore (modelCurvePropertiesBefore),
  m_modelCurvePropertiesAfter (modelCurvePropertiesAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
}

void CmdSettingsCurveProperties::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdRedo";

  mainWindow().updateCurveProperties(m_modelCurvePropertiesAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  mainWindow().updateCurveProperties(m_modelCurvePropertiesBefore);
  mainWindow().updateAfterCommand();
}
