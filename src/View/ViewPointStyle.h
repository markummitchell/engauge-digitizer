#ifndef VIEW_POINT_STYLE_H
#define VIEW_POINT_STYLE_H

#include "PointStyle.h"
#include <QLabel>
#include <QPixmap>

/// Class that displays a view of the current Curve's point style. Do NOT apply
/// a visible border since that would
/// hide a square drawn just inside the four sides.
class ViewPointStyle : public QLabel {
public:
  /// Single constructor.
  ViewPointStyle(QWidget *parent = 0);

  /// Show the style with semi-transparency or full-transparency to indicate if
  /// associated Curve is active or not
  void setEnabled(bool enabled);

  /// Apply the PointStyle of the currently selected curve.
  void setPointStyle(const PointStyle &pointStyle);

  /// Apply no PointStyle
  void unsetPointStyle();

private:
  QPixmap pixmapForCurrentSettings() const;

  // Current settings
  PointStyle m_pointStyle;
  bool m_enabled;
};

#endif // VIEW_POINT_STYLE_H
