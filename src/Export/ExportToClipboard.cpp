/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurvesGraphs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportToClipboard.h"
#include <QStringList>
#include <QTextStream>

ExportToClipboard::ExportToClipboard()
{
}

void ExportToClipboard::exportToClipboard (const QStringList &selected,
                                           const Transformation &transformation,
                                           QTextStream &strCsv,
                                           QTextStream &strHtml,
                                           const Curve &curveAxis,
                                           const CurvesGraphs &curvesGraphsAll,
                                           CurvesGraphs &curvesGraphsSelected) const
{
  // For speed, build a hash as a fast lookup table
  QHash<QString, bool> selectedHash;
  QStringList::const_iterator itrH;
  for (itrH = selected.begin (); itrH != selected.end (); itrH++) {
    QString pointIdentifier = *itrH;
    selectedHash [pointIdentifier] = false;
  }

  // List of curve names. Although we do not want axis points to be exported to the real
  // clipboard, leaving out the axis curve would result in axis points not getting
  // deleted. So we include the axis curve
  QStringList curveNames = curvesGraphsAll.curvesGraphsNames();
  curveNames << AXIS_CURVE_NAME;

  // Export
  QStringList::const_iterator itrC;
  for (itrC = curveNames.begin(); itrC != curveNames.end (); itrC++) {

    QString curveName = *itrC;
    if (curveName == AXIS_CURVE_NAME) {
      curveAxis.exportToClipboard (selectedHash,
                                   transformation,
                                   strCsv,
                                   strHtml,
                                   curvesGraphsSelected);
    } else {
      const Curve *curve = curvesGraphsAll.curveForCurveName(curveName);
      ENGAUGE_CHECK_PTR (curve);
      curve->exportToClipboard (selectedHash,
                                transformation,
                                strCsv,
                                strHtml,
                                curvesGraphsSelected);
    }
  }
}
