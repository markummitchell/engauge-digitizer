#ifndef VIEW_POINT_STYLE_H
#define VIEW_POINT_STYLE_H

#include "PointStyle.h"
#include <QLabel>
#include <QPixmap>

/// Class that displays a view of the current Curve's point style. Do NOT apply a visible border since that would
/// hide a square drawn just inside the four sides.
class ViewPointStyle : public QLabel
{
public:
  /// Single constructor.
  ViewPointStyle(QWidget *parent = 0);

  /// Apply the PointStyle of the currently selected curve.
  void setPointStyle (const PointStyle &pointStyle);

  /// Apply no PointStyle
  void unsetPointStyle ();

private:

  QPixmap pixmap (const PointStyle &pointStyle) const;

};

#endif // VIEW_POINT_STYLE_H
