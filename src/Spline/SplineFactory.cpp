/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "SplineFactory.h"
#include "SplineMultiValued.h"
#include "SplineSingleValued.h"

using namespace std;

SplineFactory::SplineFactory()
{
}

SplineFactory::~SplineFactory()
{
}

SplineAbstract *SplineFactory::create (CurveConnectAs curveConnectAs,
                                       const vector<double> &t,
                                       const vector<SplinePair> &xy) const
{
  if (curveConnectAs == CONNECT_AS_FUNCTION_SMOOTH_LEGACY ||
      curveConnectAs == CONNECT_AS_RELATION_SMOOTH) {
    return new SplineMultiValued (t,
                                  xy);
  } else {
    return new SplineSingleValued (t,
                                   xy);
  }
}
