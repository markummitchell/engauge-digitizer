#ifndef SEGMENT_H
#define SEGMENT_H

#include <QList>

class DocumentModelSegments;
class QGraphicsScene;
class QTextStream;
class SegmentLine;

/// Selectable piecewise-defined line that follows a filtered line in the image. Clicking on a
/// Segment results in the immediate creation of multiple Points along that Segment.
class Segment
{ 
public:
  /// Single constructor.
  Segment(QGraphicsScene &scene,
          int yLast);

  /// Add some more pixels in a new column to an active segment
  void appendColumn(int x, int y, const DocumentModelSegments &modelSegments);

  /// Create evenly spaced points along the segment
  QList<QPoint> fillPoints(const DocumentModelSegments &modelSegments);

  /// Get method for length in pixels
  double length() const;

  /// Get method for number of lines
  int lineCount() const;

  /// Try to compress a segment that was just completed, by folding together line from
  /// point i to point i+1, with the line from i+1 to i+2, then the line from i+2 to i+3,
  /// until one of the points is more than a half pixel from the folded line. this should
  /// save memory and improve user interface responsiveness
  void removeUnneededLines(int *foldedLines);

  /// Set the segment properties.
  void setDocumentModelSegments (const DocumentModelSegments &modelSegments);

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
  void dumpToGnuplot (QTextStream &strDump,
                      int xInt,
                      int yInt,
                      const SegmentLine *lineOld,
                      const SegmentLine *lineNew) const;

  // Create evenly spaced points along the segment, with extrap points to fill in corners
  QList<QPoint> fillPointsFillingCorners(const DocumentModelSegments &modelSegments);

  // Create evenly spaced points along the segment, without extra points in corners
  QList<QPoint> fillPointsWithoutFillingCorners(const DocumentModelSegments &modelSegments);

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
};

#endif // SEGMENT_H
