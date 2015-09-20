#include "CmdSettingsDigitizeCurve.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("DigitizeCurve settings");

CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve(MainWindow &mainWindow,
                                                   Document &document,
                                                   const DocumentModelDigitizeCurve &modelDigitizeCurveBefore,
                                                   const DocumentModelDigitizeCurve &modelDigitizeCurveAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelDigitizeCurveBefore (modelDigitizeCurveBefore),
  m_modelDigitizeCurveAfter (modelDigitizeCurveAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve";
}

CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve (MainWindow &mainWindow,
                                                    Document &document,
                                                    const QString &cmdDescription,
                                                    QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve";

  m_modelDigitizeCurveBefore.loadXml (reader);
  m_modelDigitizeCurveAfter.loadXml (reader);
}

CmdSettingsDigitizeCurve::~CmdSettingsDigitizeCurve ()
{
}

void CmdSettingsDigitizeCurve::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::cmdRedo";

  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsDigitizeCurve::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::cmdUndo";

  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsDigitizeCurve::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_DIGITIZE_CURVE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelDigitizeCurveBefore.saveXml (writer);
  m_modelDigitizeCurveAfter.saveXml(writer);
  writer.writeEndElement();
}
