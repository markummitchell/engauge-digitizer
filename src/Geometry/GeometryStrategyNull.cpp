/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyNull.h"
#include "Transformation.h"

GeometryStrategyNull::GeometryStrategyNull()
{
}

GeometryStrategyNull::~GeometryStrategyNull()
{
}

void GeometryStrategyNull::calculateGeometry (const Points & /* points */,
                                              const DocumentModelCoords & /* modelCoords */,
                                              const DocumentModelGeneral & /* modelGeneral */,
                                              const MainWindowModel & /* modelMainWindow */,
                                              const Transformation & /* transformation */,
                                              QString & /* funcArea */,
                                              QString & /* polyArea */,
                                              QVector<QString> & /* x */,
                                              QVector<QString> & /* y */,
                                              QVector<QString> & /* distanceGraphForward */,
                                              QVector<QString> & /* distancePercentForward */,
                                              QVector<QString> & /* distanceGraphBackward */,
                                              QVector<QString> & /* distancePercentBackward */) const
{
}
