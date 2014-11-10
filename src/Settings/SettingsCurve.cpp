#include "SettingsCurve.h"

SettingsCurve::SettingsCurve ()
{
}

SettingsCurve::SettingsCurve(PointShape pointShape,
                             unsigned int radius,
                             ColorPalette paletteColor) :
  m_pointStyle (pointShape,
                radius,
                paletteColor)
{
}

SettingsCurve::SettingsCurve (const SettingsCurve &other)
{
  m_pointStyle = other.pointStyle ();
}

SettingsCurve &SettingsCurve::operator=(const SettingsCurve &other)
{
  m_pointStyle = other.pointStyle ();

  return *this;
}

PointStyle SettingsCurve::pointStyle () const
{
  return m_pointStyle;
}
