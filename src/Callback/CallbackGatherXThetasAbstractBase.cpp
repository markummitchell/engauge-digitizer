/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetasAbstractBase.h"
#include "DocumentModelExportFormat.h"
#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetasAbstractBase::CallbackGatherXThetasAbstractBase(const DocumentModelExportFormat &modelExport,
                                                                     const QStringList &curvesIncluded,
                                                                     const Transformation &transformation) :
  m_curvesIncluded (curvesIncluded),
  m_transformation (transformation)
{
  bool firstCurveOnly = (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);

  // Include just the first curve, or all curves depending on DocumentModelExportFormat
  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;
    m_curvesIncludedHash [curveIncluded] = true;

    if (firstCurveOnly) {

      // We only want points belonging to the first included curve so exit this loop
      break;

    }
  }
}

CallbackGatherXThetasAbstractBase::~CallbackGatherXThetasAbstractBase()
{
}

void CallbackGatherXThetasAbstractBase::addGraphX (double xGraph)
{
  m_xThetaValues [xGraph] = true;
}

QStringList CallbackGatherXThetasAbstractBase::curvesIncluded () const
{
  return m_curvesIncluded;
}

CurvesIncludedHash CallbackGatherXThetasAbstractBase::curvesIncludedHash () const
{
  return m_curvesIncludedHash;
}

const Transformation &CallbackGatherXThetasAbstractBase::transformation () const
{
  return m_transformation;
}

ValuesVectorXOrY CallbackGatherXThetasAbstractBase::xThetaValuesRaw () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetasAbstractBase::xThetaValuesRaw";

  return m_xThetaValues;
}
