/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsCurveList.h"
#include "CurveNameList.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Curve list");

CmdSettingsCurveList::CmdSettingsCurveList(MainWindow &mainWindow,
                                           Document &document,
                                           const CurveNameList &modelCurves) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveList::CmdSettingsCurveList";

  m_curvesGraphsBefore = document.curvesGraphs ();

  // Build the 'after' state
  for (int row = 0; row < modelCurves.rowCount (); row++) {

    QModelIndex idxCurrent = modelCurves.index (row, CURVE_NAME_LIST_COLUMN_CURRENT);

    QString curveNameCurrent = modelCurves.data (idxCurrent).toString ();
    QString curveNameOriginal = modelCurves.currentCurveToOriginalCurve (curveNameCurrent);
    if (!curveNameOriginal.isEmpty ()) {

      // There was an original Curve
      const Document &documentConst = const_cast<Document&> (document);
      const Curve *curveOriginal = documentConst.curveForCurveName (curveNameOriginal);
      Curve curveCurrent (*curveOriginal);
      curveCurrent.setCurveName (curveNameCurrent);

      m_curvesGraphsAfter.addGraphCurveAtEnd (curveCurrent); // Save Curve

    } else {

      // There was no original Curve
      Curve curveCurrent (curveNameCurrent,
                          ColorFilterSettings::defaultFilter(),
                          CurveStyle (LineStyle::defaultGraphCurve(m_curvesGraphsAfter.numCurves()),
                                      PointStyle::defaultGraphCurve(m_curvesGraphsAfter.numCurves())));

      m_curvesGraphsAfter.addGraphCurveAtEnd (curveCurrent); // Save Curve
    }
  }
}

CmdSettingsCurveList::CmdSettingsCurveList (MainWindow &mainWindow,
                                            Document &document,
                                            const QString &cmdDescription,
                                            QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveList::CmdSettingsCurveList";

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
        (reader.name() == DOCUMENT_SERIALIZE_CURVES_GRAPHS)) {

      if (isBefore) {

        m_curvesGraphsBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_curvesGraphsAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read curve add/remove settings");
  }
}

CmdSettingsCurveList::~CmdSettingsCurveList ()
{
}

void CmdSettingsCurveList::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveList::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateSettingsCurveList(m_curvesGraphsAfter);
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSettingsCurveList::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurveList::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateSettingsCurveList(m_curvesGraphsBefore);
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdSettingsCurveList::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_LIST);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_curvesGraphsBefore.saveXml(writer);
  m_curvesGraphsAfter.saveXml(writer);
  writer.writeEndElement();
}
