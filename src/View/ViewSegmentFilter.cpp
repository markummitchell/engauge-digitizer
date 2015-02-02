#include <QPainter>
#include "ViewSegmentFilter.h"

ViewSegmentFilter::ViewSegmentFilter(QWidget *parent) :
  QLabel (parent)
{
  // Note the size is set externally by the layout engine
}

void ViewSegmentFilter::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  // Start and end points are midway up on both sides
  QLinearGradient gradient (0, height()/2, width(), height()/2);

  // One color at either end
  gradient.setColorAt (0.0, QColor (Qt::green));
  gradient.setColorAt (1.0, QColor (Qt::red));
  painter.setBrush (gradient);

  // No border, which is consistent with ViewPointStyle and cleaner
  painter.setPen (Qt::NoPen);

  painter.drawRect (0, 0, width(), height());
}
