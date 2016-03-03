/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackUpdateTransform.h"
#include "Point.h"

CallbackUpdateTransform::CallbackUpdateTransform(const DocumentModelCoords &modelCoords,
                                                 DocumentAxesPointsRequired documentAxesPointsRequired) :
  CallbackAxisPointsAbstract (modelCoords,
                              documentAxesPointsRequired)
{
}

bool CallbackUpdateTransform::transformIsDefined () const
{
  if (documentAxesPointsRequired () == DOCUMENT_AXES_POINTS_REQUIRED_3) {
    return !isError () && (numberAxisPoints () == 3);
  } else {
    return !isError () && (numberAxisPoints () == 4);
  }
}
