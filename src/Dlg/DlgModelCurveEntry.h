#ifndef DLG_MODEL_CURVE_ENTRY_H
#define DLG_MODEL_CURVE_ENTRY_H

#include <QString>

/// Single curve name entry in DlgPreferencesPageCurves, as a wrapper around QVariant. The userType
/// of the QVariant is QString
class DlgModelCurveEntry
{
 public:
  /// Constructor for converting to QVariant.
  DlgModelCurveEntry (const QString &curveNameCurrent,
                      const QString &curveNameOriginal);
  /// Constructor for converting from QVariant.
  DlgModelCurveEntry (const QString &fromText);

  /// Curve name displayed in DlgPreferencesPageCurves.
  QString curveNameCurrent () const;

  /// Original curve name in document. Empty if there was no original curve
  QString curveNameOriginal () const;

  /// QString for creating QVariant.
  QString toString () const;

private:
  DlgModelCurveEntry ();

  QString m_curveNameCurrent;
  QString m_curveNameOriginal;
};

#endif // DLG_MODEL_CURVE_ENTRY_H
