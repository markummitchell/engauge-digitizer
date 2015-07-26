#ifndef EXPORT_FILE_ABSTRACT_BASE_H
#define EXPORT_FILE_ABSTRACT_BASE_H

#include "CurveConnectAs.h"
#include "ExportFileAbstractBase.h"
#include "ExportHeader.h"
#include <QStringList>
#include <QVector>
#include <vector>

class Document;
class DocumentModelExport;
class QTextStream;
class SplinePair;
class Transformation;

/// Strategy base class for exporting to a file. This class provides common methods
class ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileAbstractBase();

 protected:
  /// Identify curves to include in export
  QStringList curvesToInclude (const DocumentModelExport &modelExport,
                               const Document &document,
                               const QStringList &curvesGraphsNames,
                               CurveConnectAs curveConnectAs1,
                               CurveConnectAs curveConnectAs2) const;

  /// Deallocate memory for array
  void destroy2DArray (QVector<QVector<QString*> > &array) const;

  /// Gnuplot comment delimiter
  QString gnuplotComment() const;

  /// Insert line(s) between successive sets of curves
  void insertLineSeparator (bool &isFirst,
                            ExportHeader exportHeader,
                            QTextStream &str) const;

  /// Load t (=ordinal) and xy (=screen position) spline pairs, without any conversion to graph coordinates
  void loadSplinePairsWithoutTransformation (const Points &points,
                                             std::vector<double> &t,
                                             std::vector<SplinePair> &xy) const;

  /// Load t (=ordinal) and xy (=screen position) spline pairs, converting screen coordinates to graph coordinates
  void loadSplinePairsWithTransformation (const Points &points,
                                          const Transformation &transformation,
                                          std::vector<double> &t,
                                          std::vector<SplinePair> &xy) const;
};

#endif // EXPORT_FILE_ABSTRACT_BASE_H
