#include "CmdSettingsCurves.h"
#include "CurveNameList.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCurves::CmdSettingsCurves(MainWindow &mainWindow,
                                     Document &document,
                                     const CurveNameList &modelCurves) :
  CmdAbstract(mainWindow,
              document,
              "Curves settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::CmdSettingsCurves";

  m_curvesGraphsBefore = document.curvesGraphs ();

  // Build the 'after' state
  for (int row = 0; row < modelCurves.rowCount (); row++) {

    QModelIndex idxCurrent = modelCurves.index (row, 0);
    QModelIndex idxOriginal = modelCurves.index (row, 1);

    QString curveNameCurrent = modelCurves.data (idxCurrent).toString ();
    QString curveNameOriginal = modelCurves.data (idxOriginal).toString ();
    if (!curveNameOriginal.isEmpty ()) {

      // There was an original Curve
      const Curve *curveOriginal = ((const Document&) document).curveForCurveName (curveNameOriginal);
      Curve curveCurrent (*curveOriginal);
      curveCurrent.setCurveName (curveNameCurrent);

      m_curvesGraphsAfter.addGraphCurveAtEnd (curveCurrent); // Save Curve

    } else {

      // There was no original Curve
      Curve curveCurrent (curveNameCurrent,
                          CurveFilter::defaultFilter(),
                          LineStyle::defaultGraphCurve(m_curvesGraphsAfter.numCurves()),
                          PointStyle::defaultGraphCurve(m_curvesGraphsAfter.numCurves()));

      m_curvesGraphsAfter.addGraphCurveAtEnd (curveCurrent); // Save Curve
    }
  }
}

void CmdSettingsCurves::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::cmdRedo";

  mainWindow().updateSettingsCurves(m_curvesGraphsAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurves::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::cmdUndo";

  mainWindow().updateSettingsCurves(m_curvesGraphsBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCurves::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVES);
  m_curvesGraphsBefore.saveXml(writer);
  m_curvesGraphsAfter.saveXml(writer);
  writer.writeEndElement();
}
