/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackScaleBar.h"
#include "Curve.h"
#include "DocumentModelExportFormat.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackScaleBar::CallbackScaleBar() :
  m_scaleBarLength (0)
{
}

QStringList CallbackScaleBar::axisCurvePointIdentifiers () const
{
  return m_axisCurvePointIdentifiers;
}

CallbackSearchReturn CallbackScaleBar::callback (const QString &curveName,
                                                 const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackScaleBar::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  if (curveName == AXIS_CURVE_NAME) {

    bool isNonzeroX = (qAbs (point.posGraph ().x ()) > 0);
    bool isNonzeroY = (qAbs (point.posGraph ().y ()) > 0);
    
    if (isNonzeroX || isNonzeroY) {

      m_scaleBarPointIdentifier = point.identifier ();
      m_scaleBarLength = (isNonzeroX ?
                          point.posGraph ().x () :
                          point.posGraph ().y ());
    }

    m_axisCurvePointIdentifiers << point.identifier ();
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

double CallbackScaleBar::scaleBarLength () const
{
  return m_scaleBarLength;
}

QString CallbackScaleBar::scaleBarPointIdentifier () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackScaleBar::scaleBarPointIdentifier";

  return m_scaleBarPointIdentifier;
}
