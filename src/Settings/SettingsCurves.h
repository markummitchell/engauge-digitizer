#ifndef SETTINGS_CURVES_H
#define SETTINGS_CURVES_H

#include "PointStyle.h"
#include <QMap>
#include "SettingsCurve.h"

typedef QMap<QString, SettingsCurve> SettingsCurveList;

/// Settings for all Curves.
class SettingsCurves
{
public:
  /// Default constructor.
  SettingsCurves();

  /// Copy constructor.
  SettingsCurves (const SettingsCurves &other);

  /// Assignment constructor.
  SettingsCurves &operator=(const SettingsCurves &other);

  /// Curve names of all Curves.
  QStringList curveNames () const;

  /// See SettingsCurve::pointStyle.
  PointStyle pointStyleAxis() const;

  /// See SettingsCurve::pointStyle.
  PointStyle pointStyleForCurveName (const QString &curveName) const;

  /// Settings for the specified Curve.
  SettingsCurve settingsCurve (const QString &curveName) const;

private:

  void addCurve (const QString &curveName,
                 const SettingsCurve &settingsCurve);

  SettingsCurveList m_settingsCurves; // Axis and graph curves
};

#endif // SETTINGS_CURVES_H
