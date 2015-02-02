#ifndef VIEW_POINT_STYLE_H
#define VIEW_POINT_STYLE_H

#include <QLabel>

/// Class that displays a view of the current Curve's point style.
class ViewPointStyle : public QLabel
{
public:
  /// Single constructor.
  ViewPointStyle(QWidget *parent = 0);

  /// Paint image of point.
  virtual void paintEvent(QPaintEvent *event);

private:
};

#endif // VIEW_POINT_STYLE_H
