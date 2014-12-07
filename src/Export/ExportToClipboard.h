#ifndef EXPORT_TO_CLIPBOARD_H
#define EXPORT_TO_CLIPBOARD_H

class CurvesGraphs;
class QStringList;
class QTextStream;

/// Strategy class for exporting to the clipboard. This strategy is external to the Document class so that class is simpler.
class ExportToClipboard
{
public:
  /// Single constructor.
  ExportToClipboard();

  /// Export, curve-by-curve, raw data points to a string that will be copied to the clipboard.
  void exportToClipboard (const QStringList &selected,
                          bool transformIsDefined,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          CurvesGraphs &curvesGraphs) const;
};

#endif // EXPORT_TO_CLIPBOARD_H
