/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_TO_CLIPBOARD_H
#define EXPORT_TO_CLIPBOARD_H

class Curve;
class CurvesGraphs;
class Document;
class QStringList;
class QTextStream;
class Transformation;

/// Strategy class for exporting to the clipboard. This strategy is external to the Document class so that class is simpler.
class ExportToClipboard
{
public:
  /// Single constructor.
  ExportToClipboard();

  /// Export, curve-by-curve, raw data points to a string that will be copied to the clipboard.
  /// \param[in] selected Simple list of selected points that will be exported
  /// \param[in] transformation Transformation which may or may not be defined
  /// \param[out] strCsv Selected points as comma separated value list
  /// \param[out] strHtml Selected points as html
  /// \param[in] curveAxis Axis curve in the Document and its points
  /// \param[in] curvesGraphsAll All graph curves in the Document and their points
  /// \param[out] curvesGraphsSelected Selected points as a subset of document.curvesGraphs()
  void exportToClipboard (const QStringList &selected,
                          const Transformation &transformation,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          const Curve &curveAxis,
                          const CurvesGraphs &curvesGraphsAll,
                          CurvesGraphs &curvesGraphsSelected) const;
};

#endif // EXPORT_TO_CLIPBOARD_H
