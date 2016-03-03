/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_ABSTRACT_BASE_H
#define EXPORT_FILE_ABSTRACT_BASE_H

#include "CurveConnectAs.h"
#include "ExportFileAbstractBase.h"
#include "ExportHeader.h"
#include <QStringList>
#include <QVector>
#include <vector>

class Document;
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

 protected:
  /// Gnuplot requires, and other graphing tools probably prefer, blank lines between successive curves
  QString curveSeparator (const QString *string) const;

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
  void insertLineSeparator (bool &isFirst,
                            ExportHeader exportHeader,
                            QTextStream &str) const;
};

#endif // EXPORT_FILE_ABSTRACT_BASE_H
