#include "DocumentModelSegments.h"
#include "EngaugeAssert.h"
#include "mmsubs.h"
#include <QGraphicsScene>
#include <qmath.h>
#include "Segment.h"
#include "SegmentLine.h"

Segment::Segment(QGraphicsScene &scene,
                 int y) :
  m_scene (scene),
  m_yLast (y)
{
}

bool Segment::pointIsCloseToLine(double xLeft,
                                 double yLeft,
                                 double xInt,
                                 double yInt,
                                 double xRight,
                                 double yRight)
{
  double xProj, yProj;
  projectPointOntoLine(xInt, yInt, xLeft, yLeft, xRight, yRight, &xProj, &yProj);

  return (
    (xInt - xProj) * (xInt - xProj) +
    (yInt - yProj) * (yInt - yProj) < 0.5 * 0.5);
}

bool Segment::pointsAreCloseToLine(double xLeft,
                                   double yLeft,
                                   QList<QPoint> removedPoints,
                                   double xRight,
                                   double yRight)
{
  QList<QPoint>::iterator itr;
  for (itr = removedPoints.begin(); itr != removedPoints.end(); ++itr) {
    if (!pointIsCloseToLine(xLeft, yLeft, (double) (*itr).x(), (double) (*itr).y(), xRight, yRight)) {
      return false;
    }
  }

  return true;
}

void Segment::appendColumn(int x, int y, const DocumentModelSegments &modelSegments)
{
  SegmentLine* line = new SegmentLine(m_scene, this);
  ENGAUGE_CHECK_PTR(line);
  line->setLine(QLineF (x - 1,
                        m_yLast,
                        x,
                        y));

  // Do not show this line or its segment. this is handled later

  m_lines.append(line);

  // Update total length using distance formula
  m_length += qSqrt((1.0) * (1.0) + (y - m_yLast) * (y - m_yLast));

  m_yLast = y;
}

void Segment::createAcceptablePoint(bool *pFirst,
                                    QList<QPoint> *pList,
                                    double *xPrev,
                                    double *yPrev,
                                    double x,
                                    double y)
{
  int iOld = (int) (*xPrev + 0.5);
  int jOld = (int) (*yPrev + 0.5);
  int i = (int) (x + 0.5);
  int j = (int) (y + 0.5);

  if (*pFirst || (iOld != i) || (jOld != j)) {
    *xPrev = x;
    *yPrev = y;

    ENGAUGE_CHECK_PTR(pList);
    pList->append(QPoint(i, j));
  }

  *pFirst = false;
}

QList<QPoint> Segment::fillPoints(const DocumentModelSegments &modelSegments)
{
  if (modelSegments.fillCorners()) {
    return fillPointsFillingCorners(modelSegments);
  } else {
    return fillPointsWithoutFillingCorners(modelSegments);
  }
}

QList<QPoint> Segment::fillPointsFillingCorners(const DocumentModelSegments &modelSegments)
{
  QList<QPoint> list;

  if (m_lines.count() > 0)
  {
    double xLast = (double) m_lines.first()->line().x1();
    double yLast = (double) m_lines.first()->line().y1();
    double x, y;

    // Variables for createAcceptablePoint
    double xPrev = m_lines.first()->line().x1();
    double yPrev = m_lines.first()->line().y1();

    QList<SegmentLine*>::iterator itr;
    for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

      SegmentLine *line = *itr;
      bool firstPointOfLineSegment = true;

      ENGAUGE_CHECK_PTR(line);
      double xNext = (double) line->line().x2();
      double yNext = (double) line->line().y2();

      // distance formula
      double segmentLength = sqrt((xNext - xLast) * (xNext - xLast) + (yNext - yLast) * (yNext - yLast));

      // loop since we might need to insert multiple points within a single line. this
      // is the case when removeUnneededLines has consolidated many segment lines
      double distanceLeft = segmentLength;
      double s = 0.0;
      do
      {
        // coordinates of new point
        x = (1.0 - s) * xLast + s * xNext;
        y = (1.0 - s) * yLast + s * yNext;

        createAcceptablePoint(&firstPointOfLineSegment, &list, &xPrev, &yPrev, x, y);

        distanceLeft -= modelSegments.pointSeparation();

        s += modelSegments.pointSeparation() / segmentLength;
      } while (distanceLeft >= modelSegments.pointSeparation());

      xLast = xNext;
      yLast = yNext;
    }

    // create one more point at end of last segment, if a point was not already created there
    bool firstPointOfLineSegment = true;
    createAcceptablePoint(&firstPointOfLineSegment, &list, &xPrev, &yPrev, xLast, yLast);
  }

  return list;
}

QList<QPoint> Segment::fillPointsWithoutFillingCorners(const DocumentModelSegments &modelSegments)
{
  QList<QPoint> list;

  if (m_lines.count() > 0) {

    double xLast = m_lines.first()->line().x1();
    double yLast = m_lines.first()->line().y1();
    double x, xNext;
    double y, yNext;
    double distanceCompleted = 0.0;

    // Variables for createAcceptablePoint
    bool firstPoint = true;
    double xPrev = m_lines.first()->line().x1();
    double yPrev = m_lines.first()->line().y1();

    QList<SegmentLine*>::iterator itr;
    for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

      SegmentLine *line = *itr;

      ENGAUGE_CHECK_PTR(line);
      xNext = (double) line->line().x2();
      yNext = (double) line->line().y2();

      // Distance formula
      double segmentLength = sqrt((xNext - xLast) * (xNext - xLast) + (yNext - yLast) * (yNext - yLast));
      if (segmentLength > 0.0) {

        // Loop since we might need to insert multiple points within a single line. This
        // is the case when removeUnneededLines has consolidated many segment lines
        while (distanceCompleted <= segmentLength) {

          double s = distanceCompleted / segmentLength;

          // Coordinates of new point
          x = (1.0 - s) * xLast + s * xNext;
          y = (1.0 - s) * yLast + s * yNext;

          createAcceptablePoint(&firstPoint, &list, &xPrev, &yPrev, x, y);

          distanceCompleted += modelSegments.pointSeparation();
        }

        distanceCompleted -= segmentLength;
      }

      xLast = xNext;
      yLast = yNext;
    }
  }

  return list;
}

double Segment::length() const
{
  return m_length;
}

int Segment::lineCount() const
{
  return m_lines.count();
}

void Segment::removeUnneededLines(int *foldedLines)
{
  // Pathological case is y=0.001*x*x, since the small slope can fool a naive algorithm
  // into optimizing away all but one point at the origin and another point at the far right.
  // From this we see that we cannot simply throw away points that were optimized away since they
  // are needed later to see if we have diverged from the curve
  SegmentLine *lineOlder = 0;
  QList<SegmentLine*>::iterator itr;
  QList<QPoint> removedPoints;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *line = *itr;
    if (lineOlder != 0) {

      double xLeft = lineOlder->line().x1();
      double yLeft = lineOlder->line().y1();
      double xInt = lineOlder->line().x2();
      double yInt = lineOlder->line().y2();
      ENGAUGE_CHECK_PTR(line);
      double xRight = line->line().x2();
      double yRight = line->line().y2();

      if (pointIsCloseToLine(xLeft, yLeft, xInt, yInt, xRight, yRight) &&
        pointsAreCloseToLine(xLeft, yLeft, removedPoints, xRight, yRight)) {

        // Remove intermediate point, by removing older line and stretching new line to first point
        ++(*foldedLines);
        removedPoints.append(QPoint((int) xInt, (int) yInt));
        m_lines.removeOne(lineOlder);
        delete lineOlder;
        line->setLine(xLeft, yLeft, xRight, yRight);

      } else {

        // Keeping this intermediate point and clear out the removed points list
        removedPoints.clear();
      }
    }

    lineOlder = line;
  }
}

void Segment::setDocumentModelSegments (const DocumentModelSegments &modelSegments)
{

}
