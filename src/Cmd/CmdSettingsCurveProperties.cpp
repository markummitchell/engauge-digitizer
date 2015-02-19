#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDebug>

CmdSettingsCurveProperties::CmdSettingsCurveProperties(MainWindow &mainWindow,
                                                       Document &document,
                                                       const CurveStyles &modelCurveStylesBefore,
                                                       const CurveStyles &modelCurveStylesAfter) :
  CmdAbstract(mainWindow,
              document,
              "Curve Properties settings"),
  m_modelCurveStylesBefore (modelCurveStylesBefore),
  m_modelCurveStylesAfter (modelCurveStylesAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
}

void CmdSettingsCurveProperties::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdRedo";

  mainWindow().updateSettingsCurveStyles(m_modelCurveStylesAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  mainWindow().updateSettingsCurveStyles(m_modelCurveStylesBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_PROPERTIES);
  m_modelCurveStylesBefore.saveXml(writer);
  m_modelCurveStylesAfter.saveXml(writer);
  writer.writeEndElement();
}
