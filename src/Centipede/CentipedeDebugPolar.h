/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_DEBUG_POLAR_H
#define CENTIPEDE_DEBUG_POLAR_H

#include <QPointF>

class DocumentModelCoords;
class QGraphicsScene;
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
                      double bAligned);

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
                const Transformation &transformation) const;

  /// Get method for bottom left corner of rectangle  
  QPointF posScreenParallelogramBL () const;

  /// Get method for bottom right corner of rectangle  
  QPointF posScreenParallelogramBR () const;

  /// Get method for top left corner of rectangle  
  QPointF posScreenParallelogramTL () const;

  /// Get method for top right corner of rectangle  
  QPointF posScreenParallelogramTR () const;
  
private:

  QPointF m_posScreenParallelogramTL;
  QPointF m_posScreenParallelogramTR;
  QPointF m_posScreenParallelogramBL;
  QPointF m_posScreenParallelogramBR;
  double m_angleGraphAxisFromScreenAxis;
  double m_angleEllipseFromMajorAxis;
  double m_aAligned;
  double m_bAligned;
};

#endif // CENTIPEDE_DEBUG_POLAR_H
