#include "CurveFilter.h"
#include <QPainter>
#include "ViewSegmentFilter.h"

ViewSegmentFilter::ViewSegmentFilter(QWidget *parent) :
  QLabel (parent),
  m_filterIsDefined (false)
{
  // Note the size is set externally by the layout engine
}

QColor ViewSegmentFilter::colorHigh () const
{
  QColor color (Qt::red);

  switch (m_curveFilter.filterMode ())
  {
    case FILTER_MODE_FOREGROUND:
      break;

    case FILTER_MODE_HUE:
      break;

    case FILTER_MODE_INTENSITY:
      break;

    case FILTER_MODE_SATURATION:
      break;

    case FILTER_MODE_VALUE:
      break;

    default:
      Q_ASSERT (false);
  }

  return color;
}

QColor ViewSegmentFilter::colorLow () const
{
  QColor color (Qt::green);

  switch (m_curveFilter.filterMode ())
  {
    case FILTER_MODE_FOREGROUND:
      break;

    case FILTER_MODE_HUE:
      break;

    case FILTER_MODE_INTENSITY:
      break;

    case FILTER_MODE_SATURATION:
      break;

    case FILTER_MODE_VALUE:
      break;

    default:
      Q_ASSERT (false);
  }

  return color;
}

void ViewSegmentFilter::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  if (m_filterIsDefined) {

    // Start and end points are midway up on both sides
    QLinearGradient gradient (0, height()/2, width(), height()/2);

    // One color at either end
    gradient.setColorAt (0.0, colorLow ());
    gradient.setColorAt (1.0, colorHigh ());
    painter.setBrush (gradient);

    // No border, which is consistent with ViewPointStyle and cleaner
    painter.setPen (Qt::NoPen);

    painter.drawRect (0, 0, width(), height());

  } else {

    painter.fillRect (0, 0, width (), height (), QBrush (Qt::white));

  }
}

void ViewSegmentFilter::setCurveFilter (const CurveFilter &curveFilter)
{
  m_curveFilter = curveFilter;
  m_filterIsDefined = true;

  // Force a redraw
  update();
}

void ViewSegmentFilter::unsetCurveFilter ()
{
  m_filterIsDefined = false;

  // Force a redraw
  update();
}
