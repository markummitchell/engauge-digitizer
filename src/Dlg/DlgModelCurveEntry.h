#ifndef DLG_MODEL_CURVE_ENTRY_H
#define DLG_MODEL_CURVE_ENTRY_H

#include <QString>

/// Utility class for converting the QVariant in DlgModelCurves to/from the curve names as QStrings, for use by
/// the DlgModelCurves model class. Subclassing QVariant brings up difficult challenges, so the QString userType
/// was chosen.
///
/// Each entry has the current and original curve names, separated by a delimiter.
class DlgModelCurveEntry
{
 public:
  /// Constructor for empty entry.
  DlgModelCurveEntry ();

  /// Constructor for converting to QVariant.
  DlgModelCurveEntry (const QString &curveNameCurrent,
                      const QString &curveNameOriginal);
  /// Constructor for converting from QVariant.
  DlgModelCurveEntry (const QString &fromText);

  /// Curve name displayed in DlgPreferencesPageCurves.
  QString curveNameCurrent () const;

  /// Original curve name in document. Empty if there was no original curve
  QString curveNameOriginal () const;

  /// Set method for current curve name.
  void setCurveNameCurrent (const QString &curveNameCurrent);

  /// Set method for original curve name.
  void setCurveNameOriginal (const QString &curveNameOriginal);

  /// QString for creating QVariant.
  QString toString () const;

private:

  QString m_curveNameCurrent;
  QString m_curveNameOriginal;
};

#endif // DLG_MODEL_CURVE_ENTRY_H
