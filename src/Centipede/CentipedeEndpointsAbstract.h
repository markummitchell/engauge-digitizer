/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_ENDPOINTS_ABSTRACT_H
#define CENTIPEDE_ENDPOINTS_ABSTRACT_H

#include "DocumentModelGuideline.h"
#include <QPointF>
#include "Transformation.h"

/// Base class for cartesian/polar calculations for centipedes
class CentipedeEndpointsAbstract
{
public:
  /// Constructor with individual coordinates
  CentipedeEndpointsAbstract(const DocumentModelGuideline &modelGuideline,
                           const Transformation &transformation,
                           const QPointF &posClickScreen);
  virtual ~CentipedeEndpointsAbstract ();
  
protected:

  /// Generate a pair of points next to each other along a screen circle with the specified radius, given the index
  void generatePreviousAndNextPoints (double radius,
                                      int i,
                                      QPointF &posGraphPrevious,
                                      QPointF &posGraphNext,
                                      QPointF &posScreen,
                                      double angleOffset = 0) const;

  /// Settings
  const DocumentModelGuideline &modelGuideline () const;

  /// Center of circle in screen coordinates
  QPointF posClickScreen () const;
  
  /// Transformation which is static through the entire lifetime of the Centipede class instances
  const Transformation &transformation() const;
  
private:
  CentipedeEndpointsAbstract();

  DocumentModelGuideline m_modelGuideline;
  Transformation m_transformation;
  QPointF m_posClickScreen;

};

#endif // CENTIPEDE_ENDPOINTS_ABSTRACT_H
