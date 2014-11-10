#ifndef PLOT_CLASSIFIER_H
#define PLOT_CLASSIFIER_H

#include <QDialog>
#include <QImage>
#include <QList>
#include <QPoint>

class QLabel;
class QPixmap;

typedef QList<QPoint> PerimeterPixels;

/// Class that classifies a plot as cartesian or polar, linear or logarithmic. Experimental.
class PlotClassifier : public QDialog
{
public:
  /// Single constructor.
  PlotClassifier(const QPixmap &pixmap,
                 QWidget *parent = 0);

  virtual void showEvent(QShowEvent *);

private:
  PlotClassifier();

  /// Do the work here.
  void classify ();

  // Recursively mark neighborhood points, which will always be within the perimeter points. A pathological case is
  // a figure eight which has two disjoint neighborhoods - for cases like this we probably have to recurse on perimeter
  // points as well as interior points
  void markNeighborhoodPixelsAsProcessed (int xPerim,
                                          int yPerim);
  void outputHistogram (long histogram [],
                        int grayPeakLow,
                        int grayPeakHigh,
                        int countPeak);
  // Recursively isolate perimeter points.
  void pushPerimeterPointAndRecurse (PerimeterPixels &perimeterPixels,
                                     int xPerim,
                                     int yPerim,
                                     int xObstacle,
                                     int yObstacle);

  QLabel *m_lbl;
};

#endif // PLOT_CLASSIFIER_H
