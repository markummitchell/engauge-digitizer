#ifndef VIEW_SEGMENT_FILTER_H
#define VIEW_SEGMENT_FILTER_H

#include "CurveFilter.h"
#include <QColor>
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

  /// Apply the CurveStyle of the currently selected curve.
  void setCurveFilter (const CurveFilter &curveFilter);

  /// Apply no CurveStyle
  void unsetCurveFilter ();

private:

  QColor colorHigh () const;
  QColor colorLow () const;

  CurveFilter m_curveFilter;
  bool m_filterIsDefined;
};

#endif // VIEW_SEGMENT_FILTER_H
