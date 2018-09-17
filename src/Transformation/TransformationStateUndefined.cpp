/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QImage>
#include "Transformation.h"
#include "TransformationStateContext.h"
#include "TransformationStateUndefined.h"

TransformationStateUndefined::TransformationStateUndefined(TransformationStateContext &context,
                                                           QGraphicsScene & /* scene */) :
  TransformationStateAbstractBase (context)
{
}

void TransformationStateUndefined::begin(bool /* isGnuplot */,
                                         CmdMediator & /* cmdMediator */,
                                         const Transformation & /* transformation */,
                                         const QString & /* selectedGraphCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::begin";
}

void TransformationStateUndefined::end(CmdMediator & /* cmdMediator */,
                                       const Transformation & /* transformation */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::end";
}

void TransformationStateUndefined::updateAxesChecker (CmdMediator & /* cmdMediator */,
                                                           const Transformation & /* transformation */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateUndefined::updateAxesChecker";

  // Noop
}
