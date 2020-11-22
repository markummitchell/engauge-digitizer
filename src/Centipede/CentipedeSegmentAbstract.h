/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_SEGMENT_ABSTRACT_H
#define CENTIPEDE_SEGMENT_ABSTRACT_H

#include "DocumentModelGuideline.h"
#include <QObject>
#include <QPointF>
#include "Transformation.h"

class QGraphicsItem;

/// Intersect with one of the following XT or YT coordinates for constant YR or XT respectively
enum IntersectionType {
  INTERSECTION_LOW,    /// Intersection along circle perimeter with lowest value of XT or YR
  INTERSECTION_CENTER, /// Intersection of circle center with XT or YR
  INTERSECTION_HIGH    /// Intersection along circle perimeter with highest value of XT or YR
};

/// Line segment along one of the two coordinate directions (X/T or Y/R).
/// Centipede instances are distinguished by coordinate direction, and implemented with either line or ellipse graphics item
///
/// This class inherits from QObject so its subclasses can send signals
class CentipedeSegmentAbstract : public QObject
{
  Q_OBJECT;

public:
  /// Constructor with individual coordinates
  CentipedeSegmentAbstract(const DocumentModelGuideline &modelGuideline,
                           const Transformation &transformation,
                           const QPointF &posClickScreen);
  virtual ~CentipedeSegmentAbstract ();

  /// Return distance to closest endpoint
  virtual double distanceToClosestEndpoint (const QPointF &posScreen) const = 0;

  /// Update geometry to reflect cursor movement
  virtual void updateRadius (double radius) = 0;
  
protected:

  /// Loop to find closest angle to angleCenter
  double closestAngleToCentralAngle (double angleCenter,
                                     double angleOld) const;

  /// Settings
  const DocumentModelGuideline &modelGuideline () const;

  /// Center of circle in screen coordinates
  QPointF posClickScreen () const;
  
  /// Transformation which is static through the entire lifetime of the Centipede class instances
  Transformation transformation() const;
  
private:
  CentipedeSegmentAbstract();

  DocumentModelGuideline m_modelGuideline;
  Transformation m_transformation;
  QPointF m_posClickScreen;

};

#endif // CENTIPEDE_SEGMENT_ABSTRACT_H
