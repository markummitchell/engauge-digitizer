#ifndef VIEW_SEGMENT_FILTER_H
#define VIEW_SEGMENT_FILTER_H

#include <QLabel>

/// Class that displays the current Segment Filter in a MainWindow toolbar. A gradient is displayed
class ViewSegmentFilter : public QLabel
{
public:
  /// Single constructor.
  ViewSegmentFilter(QWidget *parent = 0);

  virtual void paintEvent(QPaintEvent *event);

private:
};

#endif // VIEW_SEGMENT_FILTER_H
