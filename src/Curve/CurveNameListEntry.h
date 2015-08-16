#ifndef CURVE_NAME_LIST_ENTRY_H
#define CURVE_NAME_LIST_ENTRY_H

#include <QString>

class QXmlStreamWriter;

const int COL_CURVE_NAME_CURRENT = 0;
const int COL_CURVE_NAME_ORIGINAL = 1;
const int COL_NUM_POINTS = 2;

/// Utility class for converting the QVariant in CurveNameList to/from the curve names as QStrings, for use by
/// the CurveNameList model class. Subclassing QVariant brings up difficult challenges, so the QString userType
/// was chosen.
///
/// Each entry has the current curve name, original curve name and point count, separated by a delimiter.
class CurveNameListEntry
{
 public:
  /// Constructor for empty entry.
  CurveNameListEntry ();

  /// Constructor for converting to QVariant.
  CurveNameListEntry (const QString &curveNameCurrent,
                      const QString &curveNameOriginal,
                      int numPoints);
  /// Constructor for converting from QVariant.
  CurveNameListEntry (const QString &fromText);

  /// Curve name displayed in DlgSettingsCurveNames.
  QString curveNameCurrent () const;

  /// Original curve name in document. Empty if there was no original curve
  QString curveNameOriginal () const;

  /// Number of points in curve.
  int numPoints () const;

  /// Serialize into stream
  void saveXml(QXmlStreamWriter &writer) const;

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

#endif // CURVE_NAME_LIST_ENTRY_H
