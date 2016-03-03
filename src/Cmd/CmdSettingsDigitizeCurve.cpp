#include "CmdSettingsDigitizeCurve.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION("Digitize Curve settings");

CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve(
    MainWindow &mainWindow, Document &document,
    const DocumentModelDigitizeCurve &modelDigitizeCurveBefore,
    const DocumentModelDigitizeCurve &modelDigitizeCurveAfter)
    : CmdAbstract(mainWindow, document, CMD_DESCRIPTION),
      m_modelDigitizeCurveBefore(modelDigitizeCurveBefore),
      m_modelDigitizeCurveAfter(modelDigitizeCurveAfter) {
  LOG4CPP_INFO_S((*mainCat))
      << "CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve";
}

CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve(
    MainWindow &mainWindow, Document &document, const QString &cmdDescription,
    QXmlStreamReader &reader)
    : CmdAbstract(mainWindow, document, cmdDescription) {
  LOG4CPP_INFO_S((*mainCat))
      << "CmdSettingsDigitizeCurve::CmdSettingsDigitizeCurve";

  bool success = true;

  // Read until end of this subtree
  bool isBefore = true;
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
         (reader.name() != DOCUMENT_SERIALIZE_CMD)) {
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      xmlExitWithError(
          reader, QString("%1 %2")
                      .arg(QObject::tr(
                          "Reached end of file before finding end element for"))
                      .arg(DOCUMENT_SERIALIZE_CMD));
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_DIGITIZE_CURVE)) {

      if (isBefore) {

        m_modelDigitizeCurveBefore.loadXml(reader);
        isBefore = false;

      } else {

        m_modelDigitizeCurveAfter.loadXml(reader);
      }
    }
  }

  if (!success) {
    reader.raiseError("Cannot read digitize curve settings");
  }
}

CmdSettingsDigitizeCurve::~CmdSettingsDigitizeCurve() {}

void CmdSettingsDigitizeCurve::cmdRedo() {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSettingsDigitizeCurve::cmdRedo";

  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsDigitizeCurve::cmdUndo() {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSettingsDigitizeCurve::cmdUndo";

  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsDigitizeCurve::saveXml(QXmlStreamWriter &writer) const {
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE,
                        DOCUMENT_SERIALIZE_CMD_SETTINGS_DIGITIZE_CURVE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION,
                        QUndoCommand::text());
  m_modelDigitizeCurveBefore.saveXml(writer);
  m_modelDigitizeCurveAfter.saveXml(writer);
  writer.writeEndElement();
}
