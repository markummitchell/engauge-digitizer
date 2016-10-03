/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackBoundingRects.h"
#include "Document.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGridDisplay.h"
#include "DocumentModelGridRemoval.h"
#include "GridLineLimiter.h"
#include "MainWindowModel.h"
#include <qmath.h>
#include "Transformation.h"

const int DEFAULT_MAXIMUM_GRID_LINES = 25;

GridLineLimiter::GridLineLimiter ()
{
}

QRectF GridLineLimiter::documentBounds (const Document &document,
                                        const Transformation &transformation) const
{
  // Get graph coordinate bounds
  CallbackBoundingRects ftor (transformation);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackBoundingRects::callback);
  document.iterateThroughCurvePointsAxes (ftorWithCallback);
  document.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  bool isEmpty;
  QRectF boundingRectGraph = ftor.boundingRectGraph(isEmpty);

  return boundingRectGraph;
}

void GridLineLimiter::limitForXTheta (const Document &document,
                                      const Transformation &transformation,
                                      const DocumentModelCoords &modelCoords,
                                      const MainWindowModel &modelMainWindow,
                                      const DocumentModelGridDisplay &modelGrid,
                                      double &startX,
                                      double &stepX) const
{
  startX = modelGrid.startX();
  double stopX = modelGrid.stopX();
  stepX = modelGrid.stepX();

  if (modelCoords.coordScaleXTheta() == COORD_SCALE_LINEAR) {

    // Linear
    bool needNewStep = (stepX <= 0); // Prevent divide-by-zero in next computation
    if (!needNewStep) {
      double count = 1.0 + (stopX - startX) / stepX;
      needNewStep = ((int) count > modelMainWindow.maximumGridLines());
    }

    if (needNewStep) {

      // Adjust step so maximum grid lines limit is met
      stepX = (stopX - startX) / (modelMainWindow.maximumGridLines() - 1);

    }

  } else {

    // Log
    if (startX <= 0) {

      // Start value is invalid so override both start and step
      QRectF boundingRectGraph = documentBounds (document,
                                                 transformation);

      // Override lower bound
      startX = boundingRectGraph.left ();
    }

    bool needNewStep = (stepX <= 1); // Prevent divide-by-zero in next computation
    if (!needNewStep) {
      double count = 1.0 + (qLn (stopX) - qLn (startX)) / qLn (stepX);
      needNewStep = ((int) count > modelMainWindow.maximumGridLines());
    }

    if (needNewStep) {

      // Adjust step so maximum grid lines limit is met
      stepX = qExp ((qLn (stopX) - qLn (startX)) / (modelMainWindow.maximumGridLines() - 1));

    }
  }
}

void GridLineLimiter::limitForYRadius (const Document &document,
                                       const Transformation &transformation,
                                       const DocumentModelCoords &modelCoords,
                                       const MainWindowModel &modelMainWindow,
                                       const DocumentModelGridDisplay &modelGrid,
                                       double &startY,
                                       double &stepY) const
{
  startY = modelGrid.startY();
  double stopY = modelGrid.stopY();
  stepY = modelGrid.stepY();

  if (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR) {

    // Linear
    bool needNewStep = (stepY <= 0); // Prevent divide-by-zero in next computation
    if (!needNewStep) {
      double count = 1.0 + (stopY - startY) / stepY;
      needNewStep = ((int) count > modelMainWindow.maximumGridLines());
    }

    if (needNewStep) {

      // Adjust step so maximum grid lines limit is met
      stepY = (stopY - startY) / (modelMainWindow.maximumGridLines() - 1);

    }

  } else {

    // Log
    if (startY <= 0) {

      // Start value is invalid so override both start and step
      QRectF boundingRectGraph = documentBounds (document,
                                                 transformation);

      // Override lower bound
      startY = boundingRectGraph.top ();
    }

    bool needNewStep = (stepY <= 1); // Prevent divide-by-zero in next computation
    if (!needNewStep) {
      double count = 1.0 + (qLn (stopY) - qLn (startY)) / qLn (stepY);
      needNewStep = ((int) count > modelMainWindow.maximumGridLines());
    }

    if (needNewStep) {

      // Adjust step so maximum grid lines limit is met
      stepY = qExp ((qLn (stopY) - qLn (startY)) / (modelMainWindow.maximumGridLines() - 1));

    }
  }
}
