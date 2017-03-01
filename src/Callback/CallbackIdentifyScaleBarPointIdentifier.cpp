/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackIdentifyScaleBarPointIdentifier.h"
#include "Curve.h"
#include "DocumentModelExportFormat.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackIdentifyScaleBarPointIdentifier::CallbackIdentifyScaleBarPointIdentifier()
{
}

CallbackSearchReturn CallbackIdentifyScaleBarPointIdentifier::callback (const QString &curveName,
                                                                        const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackIdentifyScaleBarPointIdentifier::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  if (curveName == AXIS_CURVE_NAME) {

    if (point.posGraph ().x () != 0 ||
        point.posGraph ().y () != 0) {

      m_scaleBarPointIdentifier = point.identifier ();
    }
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

QString CallbackIdentifyScaleBarPointIdentifier::scaleBarPointIdentifier () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackIdentifyScaleBarPointIdentifier::scaleBarPointIdentifier";

  return m_scaleBarPointIdentifier;
}
