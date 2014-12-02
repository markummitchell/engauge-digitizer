#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDebug>

CmdSettingsCurveProperties::CmdSettingsCurveProperties(MainWindow &mainWindow,
                                                       Document &document,
                                                       const DocumentModelCurveProperties &modelCurvePropertiesBefore,
                                                       const DocumentModelCurveProperties &modelCurvePropertiesAfter) :
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

  mainWindow().updateSettingsCurveProperties(m_modelCurvePropertiesAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  mainWindow().updateSettingsCurveProperties(m_modelCurvePropertiesBefore);
  mainWindow().updateAfterCommand();
}
