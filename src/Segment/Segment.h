/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SEGMENT_H
#define SEGMENT_H

#include <QList>
#include <QObject>
#include <QPointF>

class DocumentModelSegments;
class QGraphicsScene;
class QTextStream;
class SegmentLine;

/// Selectable piecewise-defined line that follows a filtered line in the image. Clicking on a
/// Segment results in the immediate creation of multiple Points along that Segment.
class Segment : public QObject
{ 
  Q_OBJECT;

public:
  /// Single constructor.
  Segment(QGraphicsScene &scene,
          int yLast,
          bool isGnuplot);
  ~Segment();

  /// Add some more pixels in a new column to an active segment
  void appendColumn(int x, int y, const DocumentModelSegments &modelSegments);

  /// Create evenly spaced points along the segment
  QList<QPoint> fillPoints(const DocumentModelSegments &modelSegments);

  /// Coordinates of first point in Segment. This info can be used to uniquely identify a Segment. This method relies
  /// on SegmentFactory::removeEmptySegments to guarantee every Segment has at least one line
  QPointF firstPoint () const;

  /// Forward mouse press event from a component SegmentLine that was just clicked on
  void forwardMousePress ();

  /// Get method for length in pixels
  double length() const;

  /// Get method for number of lines
  int lineCount() const;

  /// Try to compress a segment that was just completed, by folding together line from
  /// point i to point i+1, with the line from i+1 to i+2, then the line from i+2 to i+3,
  /// until one of the points is more than a half pixel from the folded line. this should
  /// save memory and improve user interface responsiveness
  void removeUnneededLines(int *foldedLines);

  /// Update this segment given the new settings
  void updateModelSegment(const DocumentModelSegments &modelSegments);

public slots:

  /// Slot for hover enter/leave events in the associated SegmentLines
  void slotHover (bool hover);

signals:

  /// Pass mouse press event, with coordinates of first point in the Segment since that info uniquely identifies the owning Segment
  void signalMouseClickOnSegment (QPointF posSegmentStart);

private:
  Segment();

  // While filling corners, create a point if any of the following are true:
  // -it is the first point of the any line segment
  // -it is different than the previous point
  // While not filling corners, create a point if any of the following are true:
  // -it is the first point of the first line segment
  // -it is different than the previous point
  void createAcceptablePoint(bool *pFirst,
                             QList<QPoint> *pList,
                             double *xPrev,
                             double *yPrev,
                             double x,
                             double y);

  /// Dump pixels into gnuplot script file with embedded data, ready for input straight into gnuplot. This
  /// method revealed, when called from removeUnneededLines, that the algorithms have to allow for cases
  /// when lineOld->line().p2() is not equal to lineNew->line().p1(). In those cases, one Segment is ending
  /// and another is starting
  ///
  /// This method does nothing unless the logging level is set to DEBUG
  void dumpToGnuplot (QTextStream &strDump,
                      int xInt,
                      int yInt,
                      const SegmentLine *lineOld,
                      const SegmentLine *lineNew) const;

  // Create evenly spaced points along the segment, with extra points to fill in corners.This algorithm is the
  // same as fillPointsWithoutFillingCorners except extra points are inserted at the corners
  QList<QPoint> fillPointsFillingCorners(const DocumentModelSegments &modelSegments);

  // Create evenly spaced points along the segment, without extra points in corners
  QList<QPoint> fillPointsWithoutFillingCorners(const DocumentModelSegments &modelSegments);

  // A corner is defined as a point where the incoming slope is positive and the outgoing slope is zero
  // or negative, or incoming slope is negative and the outgoing slope is zero or positive
  bool isCorner (double yLast,
                 double yPrev,
                 double yNext) const;

  // Return true if point are a half pixel or less away from a line
  bool pointIsCloseToLine(double xLeft, double yLeft, double xInt, double yInt,
    double xRight, double yRight);

  // Return true if points are a half pixel or less away from a line
  bool pointsAreCloseToLine(double xLeft, double yLeft, QList<QPoint> removedPoints,
    double xRight, double yRight);

  QGraphicsScene &m_scene;

  // Y value of last point which is in previous column
  int m_yLast;

  // Total length of lines owned by this segment, as floating point to allow fractional increments
  double m_length;

  // This segment is drawn as a series of line segments
  QList<SegmentLine*> m_lines;

  // True for gnuplot input files for debugging
  bool m_isGnuplot;
};

#endif // SEGMENT_H
