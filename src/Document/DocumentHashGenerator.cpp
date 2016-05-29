/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackDocumentHash.h"
#include "Document.h"
#include "DocumentHashGenerator.h"
#include "Logger.h"

DocumentHashGenerator::DocumentHashGenerator()
{
}

DocumentHash DocumentHashGenerator::generate (const Document &document) const
{
  // Get hash by letting functor iterate through Document
  CallbackDocumentHash ftor (document.documentAxesPointsRequired());

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackDocumentHash::callback);

  document.iterateThroughCurvePointsAxes (ftorWithCallback);
  document.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  return ftor.hash ();
}
