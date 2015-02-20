#include "CurvesGraphs.h"
#include "EngaugeAssert.h"
#include "ExportToClipboard.h"
#include <QStringList>
#include <QTextStream>

ExportToClipboard::ExportToClipboard()
{
}

void ExportToClipboard::exportToClipboard (const QStringList &selected,
                                           bool transformIsDefined,
                                           QTextStream &strCsv,
                                           QTextStream &strHtml,
                                           CurvesGraphs &curvesGraphs) const
{
  // For speed, build a hash as a fast lookup table
  QHash<QString, bool> selectedHash;
  QStringList::const_iterator itrH;
  for (itrH = selected.begin (); itrH != selected.end (); itrH++) {
    QString pointIdentifier = *itrH;
    selectedHash [pointIdentifier] = false;
  }

  // Export
  QStringList curveNames = curvesGraphs.curvesGraphsNames();
  QStringList::const_iterator itrC;
  for (itrC = curveNames.begin(); itrC != curveNames.end (); itrC++) {

    QString curveName = *itrC;
    const Curve *curve = curvesGraphs.curveForCurveName(curveName);
    ENGAUGE_CHECK_PTR (curve);
    curve->exportToClipboard (selectedHash,
                              transformIsDefined,
                              strCsv,
                              strHtml,
                              curvesGraphs);
  }
}
