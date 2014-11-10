#include <QList>
#include "SettingsCurves.h"

extern const QString AXIS_CURVE_NAME;

SettingsCurves::SettingsCurves()
{
  addCurve (AXIS_CURVE_NAME,
            SettingsCurve (POINT_SHAPE_CROSS,
                           10,
                           COLOR_PALETTE_RED));
  addCurve ("Curve1",
            SettingsCurve (POINT_SHAPE_X,
                           10,
                           COLOR_PALETTE_BLUE));
}

SettingsCurves::SettingsCurves (const SettingsCurves &other)
{
  QStringList curveNames = other.curveNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {

    QString curveName = *itr;

    SettingsCurve settingsCurve = other.settingsCurve (curveName);

    addCurve (curveName,
              settingsCurve);
  }
}

SettingsCurves &SettingsCurves::operator=(const SettingsCurves &other)
{
  QStringList curveNames = other.curveNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {

    QString curveName = *itr;

    SettingsCurve settingsCurve = other.settingsCurve (curveName);

    addCurve (curveName,
              settingsCurve);
  }

  return *this;
}

QStringList SettingsCurves::curveNames () const
{
  QList<QString> keys = m_settingsCurves.keys ();

  return keys;
}

PointStyle SettingsCurves::pointStyleAxis() const
{
  return pointStyleForCurveName (AXIS_CURVE_NAME);
}

void SettingsCurves::addCurve (const QString &curveName,
                               const SettingsCurve &settingsCurve)
{
  m_settingsCurves [curveName] = settingsCurve;
}

PointStyle SettingsCurves::pointStyleForCurveName (const QString &curveNameWanted) const
{
  Q_ASSERT (m_settingsCurves.count () > 0);

  PointStyle pointStyle = m_settingsCurves.first ().pointStyle();

  SettingsCurveList::const_iterator itr;
  for (itr = m_settingsCurves.begin (); itr != m_settingsCurves.end (); itr++) {

    QString curveNameGot = itr.key();

    if (curveNameGot == curveNameWanted) {

      const SettingsCurve &settingsCurve = itr.value();
      return settingsCurve.pointStyle();
    }
  }

  Q_ASSERT (false);

  return pointStyle;
}

SettingsCurve SettingsCurves::settingsCurve (const QString &curveName) const
{
  Q_ASSERT (m_settingsCurves.contains (curveName));

  return m_settingsCurves [curveName];
}
