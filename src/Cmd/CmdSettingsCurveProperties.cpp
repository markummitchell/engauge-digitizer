#include "CmdSettingsCurveProperties.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDebug>
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Curve Properties settings");

CmdSettingsCurveProperties::CmdSettingsCurveProperties(MainWindow &mainWindow,
                                                       Document &document,
                                                       const CurveStyles &modelCurveStylesBefore,
                                                       const CurveStyles &modelCurveStylesAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelCurveStylesBefore (modelCurveStylesBefore),
  m_modelCurveStylesAfter (modelCurveStylesAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
}

CmdSettingsCurveProperties::CmdSettingsCurveProperties (MainWindow &mainWindow,
                                                        Document &document,
                                                        const QString &cmdDescription,
                                                        QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::CmdSettingsCurveProperties";
  
  m_modelCurveStylesBefore.loadXml (reader);
  m_modelCurveStylesAfter.loadXml (reader);
}

CmdSettingsCurveProperties::~CmdSettingsCurveProperties ()
{
}

void CmdSettingsCurveProperties::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdRedo";

  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateSettingsCurveStyles(m_modelCurveStylesAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveProperties::cmdUndo";

  document().updatePointOrdinals (mainWindow().transformation());
  mainWindow().updateSettingsCurveStyles(m_modelCurveStylesBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurveProperties::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_PROPERTIES);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelCurveStylesBefore.saveXml(writer);
  m_modelCurveStylesAfter.saveXml(writer);
  writer.writeEndElement();
}
