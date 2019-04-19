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

const int DEFAULT_MAXIMUM_GRID_LINES = 100;

GridLineLimiter::GridLineLimiter ()
{
}

void GridLineLimiter::documentBounds (const Document &document,
                                      const Transformation &transformation,
                                      QPointF &boundingRectMin,
                                      QPointF &boundingRectMax) const
{
  // Get graph coordinate bounds
  CallbackBoundingRects ftor (document.documentAxesPointsRequired(),
                              transformation);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackBoundingRects::callback);
  document.iterateThroughCurvePointsAxes (ftorWithCallback);
  document.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  bool isEmpty;
  boundingRectMin = ftor.boundingRectGraphMin (isEmpty);
  boundingRectMax = ftor.boundingRectGraphMax (isEmpty);
}

void GridLineLimiter::limitForXTheta (const Document &document,
                                      const Transformation &transformation,
                                      const DocumentModelCoords &modelCoords,
                                      const MainWindowModel &modelMainWindow,
                                      const DocumentModelGridDisplay &modelGrid,
                                      double &startX,
                                      double &stepX,
                                      double &stopX) const
{
  startX = modelGrid.startX();
  stopX = modelGrid.stopX();
  stepX = modelGrid.stepX();
  int countX = signed (modelGrid.countX());

  bool needReduction = (countX > modelMainWindow.maximumGridLines());

  if (modelCoords.coordScaleXTheta() == COORD_SCALE_LINEAR) {

    // Linear
    if (!needReduction) {
      if (stepX <= 0) {
        stepX = 0;
        needReduction = true;
      } else {
        countX = qFloor (1.0 + (stopX - startX) / stepX);
        needReduction = (countX > modelMainWindow.maximumGridLines());
      }
    }

    if (needReduction) {
      stopX = startX + stepX * (modelMainWindow.maximumGridLines() - 1);
    }

  } else {

    // Log
    if (startX <= 0) {

      // Start value is invalid so override both start and step
      QPointF boundingRectGraphMin, boundingRectGraphMax;
      documentBounds (document,
                      transformation,
                      boundingRectGraphMin,
                      boundingRectGraphMax);

      // Override lower bound
      startX = boundingRectGraphMin.x ();
    }

    if (!needReduction) {
      if (stepX <= 1) {
        stepX = 1;
        needReduction = true;        
      } else {
        countX = qFloor (1.0 + (qLn (stopX) - qLn (startX)) / qLn (stepX));
        needReduction = (countX > modelMainWindow.maximumGridLines());
      }
    }

    if (needReduction) {
      stopX = qExp (qLn (startX) + qLn (stepX) * (modelMainWindow.maximumGridLines() - 1));
    }
  }
}

void GridLineLimiter::limitForYRadius (const Document &document,
                                       const Transformation &transformation,
                                       const DocumentModelCoords &modelCoords,
                                       const MainWindowModel &modelMainWindow,
                                       const DocumentModelGridDisplay &modelGrid,
                                       double &startY,
                                       double &stepY,
                                       double &stopY) const
{
  startY = modelGrid.startY();
  stopY = modelGrid.stopY();
  stepY = modelGrid.stepY();
  int countY = signed (modelGrid.countY());

  bool needReduction = (countY > modelMainWindow.maximumGridLines());

  if (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR) {

    // Linear
    if (!needReduction) {
      if (stepY <= 0) {
        stepY = 0;
        needReduction = true;        
      } else {
        countY = qFloor (1.0 + (stopY - startY) / stepY);
        needReduction = (countY > modelMainWindow.maximumGridLines());
      }
    }

    if (needReduction) {
      stopY = startY + stepY * (modelMainWindow.maximumGridLines() - 1);
    }

  } else {

    // Log
    if (startY <= 0) {

      // Start value is invalid so override both start and step
      QPointF boundingRectGraphMin, boundingRectGraphMax;
      documentBounds (document,
                      transformation,
                      boundingRectGraphMin,
                      boundingRectGraphMax);

      // Override lower bound
      startY = boundingRectGraphMin.y ();
    }

    if (!needReduction) {
      if (stepY <= 1) {
        stepY = 1;
        needReduction = true;        
      } else {
        countY = qFloor (1.0 + (qLn (stopY) - qLn (startY)) / qLn (stepY));
        needReduction = (countY > modelMainWindow.maximumGridLines());
      }
    }

    if (needReduction) {
      stopY = qExp (qLn (startY) + qLn (stepY) * (modelMainWindow.maximumGridLines() - 1));
    }
  }
}
