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

  /// Get method for line styles.
  LineStyles lineStyles () const;

  /// Get method for point styles.
  PointStyles pointStyles () const;

private:
  DlgModelCurveProperties();

  LineStyles m_lineStyles;
  PointStyles m_pointStyles;
};

#endif // DLG_MODEL_CURVE_PROPERTIES_H
