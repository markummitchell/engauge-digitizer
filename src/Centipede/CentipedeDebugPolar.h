/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_DEBUG_POLAR_H
#define CENTIPEDE_DEBUG_POLAR_H

#include <QPointF>

class DocumentModelCoords;
class QColor;
class QGraphicsEllipseItem;
class QGraphicsScene;
class QLineF;
class Transformation;

/// Class for collecting and then displaying debug information computed during constant R ellipse calculations
class CentipedeDebugPolar
{
public:
  /// Default constructor with initial values overwritten later
  CentipedeDebugPolar();

  /// Constructor with parallelogram (TL=top left, BR=bottom right,...) that circumscribes the ellipse, which
  /// gets converted into a right-angle rectangle
  CentipedeDebugPolar(const QPointF &posScreenParallelogramTL,
                      const QPointF &posScreenParallelogramTR,
                      const QPointF &posScreenParallelogramBL,
                      const QPointF &posScreenParallelogramBR,
                      double angleGraphAxisFromScreenAxis,
                      double angleEllipseFromMajorAxis,
                      double aAligned,
                      double bAligned,
                      double radius);

  /// Copy constructor
  CentipedeDebugPolar (const CentipedeDebugPolar &other);

  /// Assignment operator
  CentipedeDebugPolar &operator= (const CentipedeDebugPolar &other);

  virtual ~CentipedeDebugPolar ();

  /// Get method for top left corner of rectangle  
  double aAligned () const;

  /// Get method for top left corner of rectangle  
  double angleEllipseFromMajorAxis () const;

  /// Get method for top left corner of rectangle  
  double angleGraphAxisFromScreenAxis () const;

  /// Get method for top left corner of rectangle  
  double bAligned () const;

  /// Display member variable values on scene
  void display (QGraphicsScene &scene,
                const DocumentModelCoords &modelCoords,
                const Transformation &transformation);

  /// Dump ellipse grahics item. This is expected to be called just after all geometry settings for a
  /// QGraphicsEllipseItem have been completed in the Centipede code, and later in the Guideline code,
  /// so they can be compared when there is a problem. The broken code is adjusted to produce the values
  /// of the good ellipse (assuming there  is one)
  void dumpEllipseGraphicsItem (const QString &callerMethod,
                                const QGraphicsEllipseItem *ellipse) const;

  /// Get method for bottom left corner of rectangle  
  QPointF posScreenParallelogramBL () const;

  /// Get method for bottom right corner of rectangle  
  QPointF posScreenParallelogramBR () const;

  /// Get method for top left corner of rectangle  
  QPointF posScreenParallelogramTL () const;

  /// Get method for top right corner of rectangle  
  QPointF posScreenParallelogramTR () const;
  
  /// Get method for radius
  double radius () const;

private:

  /// Append new entry to legend
  void addToLegend (QGraphicsScene &scene,
                    const QString &entry,
                    const QColor &color);

  /// Display a full circle or ellipse of tics on the circumference
  void displayTics (QGraphicsScene &scene,
                    const Transformation &transformation,
                    const QPointF &posOriginScreen,
                    const QPointF &posAAxisScreen,
                    const QColor &colorGraphCoordinates,
                    const QColor &colorScreenCoordinates);

  /// Convert a radial line into a (much shorter) tic mark using the last part of the given line
  QLineF portionOfLineLast (const QLineF &line,
                            int degrees,
                            int degreesBetweenHighlights) const;

  /// Convert a radial line into a (much shorter) tic mark using the next part of the given line when extended
  QLineF portionOfLineNext (const QLineF &line,
                            int degrees,
                            int degreesBetweenHighlights) const;

  QPointF m_posScreenParallelogramTL;
  QPointF m_posScreenParallelogramTR;
  QPointF m_posScreenParallelogramBL;
  QPointF m_posScreenParallelogramBR;
  double m_angleGraphAxisFromScreenAxis;
  double m_angleEllipseFromMajorAxis;
  double m_aAligned;
  double m_bAligned;
  double m_radius;
  int m_legendYPos; // Positions legend entries
};

#endif // CENTIPEDE_DEBUG_POLAR_H
