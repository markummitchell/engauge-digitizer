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
    double count = 1.0 + (stopX - startX) / stepX;
    if ((int) count > modelMainWindow.maximumGridLines()) {

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

    double count = 1.0 + (qLn (stopX) - qLn (startX)) / qLn (modelMainWindow.maximumGridLines());
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      stepX = qExp ((qLn (stopX) - qLn (startX)) / (modelMainWindow.maximumGridLines() - 1));

    }
  }
}

void GridLineLimiter::limitForYRange (const Document &document,
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
    double count = 1.0 + (stopY - startY) / stepY;
    if ((int) count > modelMainWindow.maximumGridLines()) {

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

    double count = 1.0 + (qLn (stopY) - qLn (startY)) / qLn (modelMainWindow.maximumGridLines());
    if ((int) count > modelMainWindow.maximumGridLines()) {

      // Adjust step so maximum grid lines limit is met
      stepY = qExp ((qLn (stopY) - qLn (startY)) / (modelMainWindow.maximumGridLines() - 1));

    }
  }
}
