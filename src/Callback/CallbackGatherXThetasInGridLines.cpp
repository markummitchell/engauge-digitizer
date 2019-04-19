/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetasInGridLines.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "GridLineLimiter.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include "Point.h"
#include <qmath.h>

const bool NOT_FIRST_CURVE_ONLY = false;

CallbackGatherXThetasInGridLines::CallbackGatherXThetasInGridLines(const MainWindowModel &modelMainWindow,
                                                                   const DocumentModelExportFormat &modelExport,
                                                                   const QStringList &curvesIncluded,
                                                                   const Transformation &transformation,
                                                                   const Document &document) :
  CallbackGatherXThetasAbstractBase (NOT_FIRST_CURVE_ONLY,
                                     modelExport.extrapolateOutsideEndpoints (),
                                     curvesIncluded,
                                     transformation)
{
  addGridLines (modelMainWindow,
                transformation,
                document);
}

void CallbackGatherXThetasInGridLines::addGridLines (const MainWindowModel &modelMainWindow,
                                                     const Transformation &transformation,
                                                     const Document &document)
{
  DocumentModelGridDisplay gridLines = document.modelGridDisplay();

  // Prevent overflow
  GridLineLimiter gridLineLimiter;
  double startX = document.modelGridDisplay().startX();
  double stepX = document.modelGridDisplay().stepX();
  double stopX = document.modelGridDisplay().stopX();
  gridLineLimiter.limitForXTheta (document,
                                  transformation,
                                  document.modelCoords(),
                                  modelMainWindow,
                                  document.modelGridDisplay(),
                                  startX,
                                  stepX,
                                  stopX);
  if (document.modelCoords().coordScaleXTheta() == COORD_SCALE_LINEAR) {
    // Linear
    int countX = qFloor (0.5 + 1 + (stopX - startX) / stepX);
    for (int i = 0; i < countX; i++) {
      double x = startX + i * stepX;
      addGraphX (x);
    }
  } else {
    // Log
    int countX = qFloor (1.0 + (qLn (stopX) - qLn (startX)) / qLn (stepX));
    for (int i = 0; i < countX; i++) {
      double x = startX * qPow (stepX, i);
      addGraphX (x);
    }
  }
}

CallbackSearchReturn CallbackGatherXThetasInGridLines::callback (const QString &curveName,
                                                                 const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetasInGridLines::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  updateMinMax (curveName,
                point);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
