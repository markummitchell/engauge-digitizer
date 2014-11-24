#ifndef DLG_MODEL_CURVE_PROPERTIES_H
#define DLG_MODEL_CURVE_PROPERTIES_H

#include "LineStyle.h"
#include "PointStyle.h"
#include <QHash>

typedef QHash<QString, LineStyle> LineStyles;
typedef QHash<QString, PointStyle> PointStyles;

class CmdMediator;

/// Model for DlgSettingsCurveProperties and CmdSettingsCurveProperties.
class DlgModelCurveProperties
{
public:
  /// Initial constructor from Document.
  DlgModelCurveProperties(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelCurveProperties (const DlgModelCurveProperties &other);

  /// Assignment constructor.
  DlgModelCurveProperties &operator=(const DlgModelCurveProperties &other);

  /// Line style for specified curve.
  LineStyle lineStyleForCurveName (const QString &curveName) const;

  /// Get method for line styles.
  LineStyles lineStyles () const;

  /// Point style for specified curve.
  PointStyle pointStyleForCurveName (const QString &curveName) const;

  /// Get method for point styles.
  PointStyles pointStyles () const;

  /// Set method for line style of one curve.
  void setLineStyleForCurveName(const QString &curveName,
                                const LineStyle &lineStyle);

  /// Set method for point style of one curve.
  void setPointStyleForCurveName(const QString &curveName,
                                 const PointStyle &pointStyle);

private:
  DlgModelCurveProperties();

  LineStyles m_lineStyles;
  PointStyles m_pointStyles;
};

#endif // DLG_MODEL_CURVE_PROPERTIES_H
