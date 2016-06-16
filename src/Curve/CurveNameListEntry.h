/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURVE_NAME_LIST_ENTRY_H
#define CURVE_NAME_LIST_ENTRY_H

#include <QString>

class QXmlStreamWriter;

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

  /// Get method for current curve name constant
  static int COL_CURVE_NAME_CURRENT () { return 0; }

  /// Get method for original curve name constant
  static int COL_CURVE_NAME_ORIGINAL () { return 1; }

  /// Get method for number of points constant
  static int COL_NUM_POINTS () { return 2; }

  /// Curve name displayed in DlgSettingsCurveAddRemove.
  QString curveNameCurrent () const;

  /// Original curve name in document. Empty if there was no original curve
  QString curveNameOriginal () const;

  /// Return true if entry is unpopulated. This is true between insertRows (where added to model) and setData (where fields are set)
  bool entryHasNotBeenPopulated () const;

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

#endif // CURVE_NAME_LIST_ENTRY_H
