/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H
#define CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H

#include "CallbackSearchReturn.h"
#include "CurvesIncludedHash.h"
#include "ExportValuesXOrY.h"
#include "Transformation.h"
#include "ValuesVectorXOrY.h"

class DocumentModelExportFormat;
class Point;

/// Base callback for collecting X/Theta independent variables, for functions, in preparation for exporting
class CallbackGatherXThetasAbstractBase
{
public:
  /// Single constructor.
  CallbackGatherXThetasAbstractBase(const DocumentModelExportFormat &modelExport,
                                    const QStringList &curvesIncluded,
                                    const Transformation &transformation);
  virtual ~CallbackGatherXThetasAbstractBase ();

  /// Callback method.
  virtual CallbackSearchReturn callback (const QString &curveName,
                                         const Point &point) = 0;

  /// Perform final processing after iterating through points in Document
  virtual void finalize () = 0;

  /// Resulting x/theta values for all included functions
  ValuesVectorXOrY xThetaValuesRaw () const;

protected:

  /// Save one graph x value
  void addGraphX (double xGraph);
  
  /// Get method for included names
  QStringList curvesIncluded () const;
  
  /// Get method for included names as hash
  CurvesIncludedHash curvesIncludedHash () const;

  /// Get method for transformation
  const Transformation &transformation() const;
  
private:
  CallbackGatherXThetasAbstractBase();

  QStringList m_curvesIncluded;
  const Transformation m_transformation;
  CurvesIncludedHash m_curvesIncludedHash;
  ValuesVectorXOrY m_xThetaValues;
};

#endif // CALLBACK_GATHER_X_THETAS_ABSTRACT_BASE_H
