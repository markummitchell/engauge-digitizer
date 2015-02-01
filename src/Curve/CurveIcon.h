#ifndef CURVE_ICON_H
#define CURVE_ICON_H

#include "PointStyle.h"
#include <QPixmap>

/// Class that creates an icon for the combobox in MainWindow, given the PointStyle
class CurveIcon
{
public:
  /// Single constructor.
  CurveIcon(const PointStyle &pointStyle);

  /// Icon from PointStyle.
  QPixmap pixmap () const;

private:
  CurveIcon();

  PointStyle m_pointStyle;
};

#endif // CURVE_ICON_H
