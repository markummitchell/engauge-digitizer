/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsDigitizeCurve.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Digitize Curve settings");

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

  bool success = true;

  // Read until end of this subtree
  bool isBefore = true;
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CMD)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      xmlExitWithError (reader,
                        QString ("%1 %2")
                        .arg (QObject::tr ("Reached end of file before finding end element for"))
                        .arg (DOCUMENT_SERIALIZE_CMD));
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_DIGITIZE_CURVE)) {

      if (isBefore) {

        m_modelDigitizeCurveBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelDigitizeCurveAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read digitize curve settings");
  }
}

CmdSettingsDigitizeCurve::~CmdSettingsDigitizeCurve ()
{
}

void CmdSettingsDigitizeCurve::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveAfter);
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSettingsDigitizeCurve::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsDigitizeCurve::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateSettingsDigitizeCurve(m_modelDigitizeCurveBefore);
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
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
