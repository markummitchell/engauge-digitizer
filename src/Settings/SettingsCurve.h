#ifndef SETTINGS_CURVE_H
#define SETTINGS_CURVE_H

#include "ColorPalette.h"
#include "PointStyle.h"

/// Settings for one Curve.
class SettingsCurve
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  SettingsCurve ();

  /// Normal constructor.
  SettingsCurve (PointShape pointShape,
                 unsigned int radius,
                 ColorPalette paletteColor);

  /// Copy constructor.
  SettingsCurve (const SettingsCurve &other);

  /// Assignment constructor.
  SettingsCurve &operator=(const SettingsCurve &other);

  /// Point style accessor.
  PointStyle pointStyle () const;

private:

  PointStyle m_pointStyle;
};

#endif // SETTINGS_CURVE_H
