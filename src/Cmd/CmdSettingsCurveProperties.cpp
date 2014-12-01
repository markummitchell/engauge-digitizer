#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDebug>

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
  qDebug()<<"CmdSettingsCurveProperties constructor";
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
}

void CmdSettingsCurveProperties::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdRedo";

  qDebug()<<"CmdSettingsCurveProperties before cmdRedo";
  mainWindow().updateSettingsCurveProperties(m_modelCurvePropertiesAfter);
  qDebug()<<"CmdSettingsCurveProperties after cmdRedo";
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  mainWindow().updateSettingsCurveProperties(m_modelCurvePropertiesBefore);
  mainWindow().updateAfterCommand();
}
