#ifndef EXPORT_TO_CLIPBOARD_H
#define EXPORT_TO_CLIPBOARD_H

class CurvesGraphs;
class Document;
class QStringList;
class QTextStream;

/// Strategy class for exporting to the clipboard. This strategy is external to the Document class so that class is simpler.
class ExportToClipboard
{
public:
  /// Single constructor.
  ExportToClipboard();

  /// Export, curve-by-curve, raw data points to a string that will be copied to the clipboard.
  /// \param[in] selected Simple list of selected points that will be exported
  /// \param[in] transformIsDefined True if transformation is defined
  /// \param[out] strCsv Selected points as comma separated value list
  /// \param[out] strHtml Selected points as html
  /// \param[in] curvesGraphsAll All points in Document
  /// \param[out] curvesGraphsSelected Selected points as a subset of document.curvesGraphs()
  void exportToClipboard (const QStringList &selected,
                          bool transformIsDefined,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          const CurvesGraphs &curvesGraphsAll,
                          CurvesGraphs &curvesGraphsSelected) const;
};

#endif // EXPORT_TO_CLIPBOARD_H
