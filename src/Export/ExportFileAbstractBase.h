/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_ABSTRACT_BASE_H
#define EXPORT_FILE_ABSTRACT_BASE_H

#include "CurveConnectAs.h"
#include "ExportHeader.h"
#include <QPointF>
#include <QStringList>
#include <QVector>
#include <vector>

class Document;
class DocumentModelCoords;
class DocumentModelExportFormat;
class QTextStream;
class SplinePair;
class Transformation;

/// Strategy base class for exporting to a file. This class provides common methods
class ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileAbstractBase();
  virtual ~ExportFileAbstractBase ();
  
protected:

  /// Identify curves to include in export. The specified DocumentModelExportFormat overrides same data in Document for previewing window
  QStringList curvesToInclude (const DocumentModelExportFormat &modelExportOverride,
                               const Document &document,
                               const QStringList &curvesGraphsNames,
                               CurveConnectAs curveConnectAs1,
                               CurveConnectAs curveConnectAs2) const;

  /// Deallocate memory for array
  void destroy2DArray (QVector<QVector<QString*> > &array) const;

  /// Gnuplot comment delimiter
  QString gnuplotComment() const;

  /// Insert line(s) between successive sets of curves
  void insertLineSeparator (bool isFirst,
                            ExportHeader exportHeader,
                            QTextStream &str) const;

  /// Interpolate (if xThetaValue is between posGraphBefore.x() and posGraph.x()) or
  /// extrapolate (if xThetaValue < posGraphBefore.x() or xThetaValue > posGraph.x())
  /// the given x/theta value using the two specified graph points
  double linearlyInterpolateYRadiusFromTwoPoints (double xThetaValue,
                                                  const DocumentModelCoords &modelCoords,
                                                  const QPointF &posGraphBefore,
                                                  const QPointF &posGraph) const;

  /// RFC 4180 says if values are delimited by a comma AND a value has commas in it (for locale like
  /// English/Switzerland when dealing with numbers) then double quotes are required for the value.
  /// In other cases this method is a noop
  QString wrapInDoubleQuotesIfNeeded (const DocumentModelExportFormat &modelExportOverride,
                                      const QString &valueString) const;
};

#endif // EXPORT_FILE_ABSTRACT_BASE_H
