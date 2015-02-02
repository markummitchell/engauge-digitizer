#ifndef VIEW_SEGMENT_FILTER_H
#define VIEW_SEGMENT_FILTER_H

#include <QLabel>

/// Class that displays the current Segment Filter in a MainWindow toolbar. A gradient is displayed. No border
/// is drawn so the appearance is consistent with ViewPointStyle which would not work with a border.
class ViewSegmentFilter : public QLabel
{
public:
  /// Single constructor.
  ViewSegmentFilter(QWidget *parent = 0);

  /// Paint with a horizontal linear gradient.
  virtual void paintEvent(QPaintEvent *event);

private:
};

#endif // VIEW_SEGMENT_FILTER_H
