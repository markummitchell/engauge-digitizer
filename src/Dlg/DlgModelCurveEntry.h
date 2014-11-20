#ifndef DLG_MODEL_CURVE_ENTRY_H
#define DLG_MODEL_CURVE_ENTRY_H

#include <QString>

const int COL_CURVE_NAME_CURRENT = 0;
const int COL_CURVE_NAME_ORIGINAL = 1;
const int COL_NUM_POINTS = 2;

/// Utility class for converting the QVariant in DlgModelCurves to/from the curve names as QStrings, for use by
/// the DlgModelCurves model class. Subclassing QVariant brings up difficult challenges, so the QString userType
/// was chosen.
///
/// Each entry has the current curve name, original curve name and point count, separated by a delimiter.
class DlgModelCurveEntry
{
 public:
  /// Constructor for empty entry.
  DlgModelCurveEntry ();

  /// Constructor for converting to QVariant.
  DlgModelCurveEntry (const QString &curveNameCurrent,
                      const QString &curveNameOriginal,
                      int numPoints);
  /// Constructor for converting from QVariant.
  DlgModelCurveEntry (const QString &fromText);

  /// Curve name displayed in DlgSettingsCurves.
  QString curveNameCurrent () const;

  /// Original curve name in document. Empty if there was no original curve
  QString curveNameOriginal () const;

  /// Number of points in curve.
  int numPoints () const;

  /// Set method for current curve name.
  void setCurveNameCurrent (const QString &curveNameCurrent);

  /// Set method for original curve name.
  void setCurveNameOriginal (const QString &curveNameOriginal);

  /// Set method for point count.
  void setNumPoints (int numPoints);

  /// QString for creating QVariant.
  QString toString () const;

private:

  QString m_curveNameCurrent;
  QString m_curveNameOriginal;
  int m_numPoints;
};

#endif // DLG_MODEL_CURVE_ENTRY_H
