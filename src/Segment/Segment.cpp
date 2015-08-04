#include "DocumentModelSegments.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "mmsubs.h"
#include <QFile>
#include <QGraphicsScene>
#include <qmath.h>
#include <QTextStream>
#include "Segment.h"
#include "SegmentLine.h"

#define ENABLE_GNUPLOT_DEBUGGING

Segment::Segment(QGraphicsScene &scene,
                 int y) :
  m_scene (scene),
  m_yLast (y)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::Segment";
}

void Segment::appendColumn(int x, int y, const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::appendColumn";

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

void Segment::dumpToGnuplot (QTextStream &strDump,
                             int xInt,
                             int yInt,
                             const SegmentLine *lineOld,
                             const SegmentLine *lineNew) const
{
  // Show "before" and "after" line info. Note that the merged line starts with lineOld->line().p1()
  // and ends with lineNew->line().p2()
  QString label = QString ("Old: (%1,%2) to (%3,%4), New: (%5,%6) to (%7,%8)")
                  .arg (lineOld->line().x1())
                  .arg (lineOld->line().y1())
                  .arg (lineOld->line().x2())
                  .arg (lineOld->line().y2())
                  .arg (lineNew->line().x1())
                  .arg (lineNew->line().y1())
                  .arg (lineNew->line().x2())
                  .arg (lineNew->line().y2());

  strDump << "unset label\n";
  strDump << "set label \"" << label << "\" at graph 0, graph 0.02\n";
  strDump << "set grid xtics\n";
  strDump << "set grid ytics\n";

  // Get the bounds
  int rows = 0, cols = 0;
  QList<SegmentLine*>::const_iterator itr;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *line = *itr;
    int x1 = line->line().x1();
    int y1 = line->line().y1();
    int x2 = line->line().x2();
    int y2 = line->line().y2();

    rows = qMax (rows, y1 + 1);
    rows = qMax (rows, y2 + 1);
    cols = qMax (cols, x1 + 1);
    cols = qMax (cols, x2 + 1);
  }

  // Horizontal and vertical width is computed so merged line mostly fills the plot window,
  // and (xInt,yInt) is at the center
  int halfWidthX = 1.5 * qMax (qAbs (lineOld->line().dx()),
                               qAbs (lineNew->line().dx()));
  int halfWidthY = 1.5 * qMax (qAbs (lineOld->line().dy()),
                               qAbs (lineNew->line().dy()));

  // Zoom in so changes are easier to see
  strDump << "set xrange [" << (xInt - halfWidthX - 1) << ":" << (xInt + halfWidthX + 1) << "]\n";
  strDump << "set yrange [" << (yInt - halfWidthY - 1) << ":" << (yInt + halfWidthY + 1) << "]\n";

  // One small curve shows xInt as horizontal line, and another shows yInt as vertical line.
  // A small curve shows the replacement line
  // Then two hhuge piecewise-defined curve show the pre-merge Segment pixels as two alternating colors
  strDump << "plot \\\n"
          << "\"-\" title \"\" with lines, \\\n"
          << "\"-\" title \"\" with lines, \\\n"
          << "\"-\" title \"Replacement\" with lines, \\\n"
          << "\"-\" title \"Segment pixels Even\" with linespoints, \\\n"
          << "\"-\" title \"Segment pixels Odd\"  with linespoints\n"
          << xInt << " " << (yInt - halfWidthY) << "\n"
          << xInt << " " << (yInt + halfWidthY) << "\n"
          << "end\n"
          << (xInt - halfWidthX) << " " << yInt << "\n"
          << (xInt + halfWidthY) << " " << yInt << "\n"
          << "end\n"
          << lineOld->line().x1() << " " << lineOld->line().y1() << "\n"
          << lineNew->line().x2() << " " << lineNew->line().y2() << "\n"
          << "end\n";

  // Fill the array from the list
  QString even, odd;
  QTextStream strEven (&even), strOdd (&odd);
  for (int index = 0; index < m_lines.count(); index++) {

    SegmentLine *line = m_lines.at (index);
    int x1 = line->line().x1();
    int y1 = line->line().y1();
    int x2 = line->line().x2();
    int y2 = line->line().y2();

    if (index % 2 == 0) {
      strEven << x1 << " " << y1 << "\n";
      strEven << x2 << " " << y2 << "\n";
      strEven << "\n";
    } else {
      strOdd << x1 << " " << y1 << "\n";
      strOdd << x2 << " " << y2 << "\n";
      strOdd << "\n";
    }
  }
  strDump << even << "\n";
  strDump << "end\n";
  strDump << odd << "\n";
  strDump << "end\n";
  strDump << "pause -1 \"Hit Enter to continue\"\n";
  strDump << flush;
}

QList<QPoint> Segment::fillPoints(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::fillPoints";

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

bool Segment::pointIsCloseToLine(double xLeft,
                                 double yLeft,
                                 double xInt,
                                 double yInt,
                                 double xRight,
                                 double yRight)
{
  double xProj, yProj, projectedDistanceOutsideLine, distanceToLine;
  projectPointOntoLine(xInt, yInt, xLeft, yLeft, xRight, yRight, &xProj, &yProj, &projectedDistanceOutsideLine, &distanceToLine);

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

void Segment::removeUnneededLines(int *foldedLines)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::removeUnneededLines";

  QFile fileDump ("Segment.out");
  fileDump.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strDump (&fileDump);

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

      // If lineOlder is the last line of one Segment and line is the first line of another Segment then
      // it makes no sense to remove any point so we continue the loop
      if (lineOlder->line().p2() == line->line().p1()) {

        double xRight = line->line().x2();
        double yRight = line->line().y2();

        if (pointIsCloseToLine(xLeft, yLeft, xInt, yInt, xRight, yRight) &&
          pointsAreCloseToLine(xLeft, yLeft, removedPoints, xRight, yRight)) {

#ifdef ENABLE_GNUPLOT_DEBUGGING
          // Dump
          dumpToGnuplot (strDump,
                         xInt,
                         yInt,
                         lineOlder,
                         line);
#endif

          // Remove intermediate point, by removing older line and stretching new line to first point
          ++(*foldedLines);
          removedPoints.append(QPoint((int) xInt, (int) yInt));
          m_lines.removeOne(lineOlder);
          delete lineOlder;

          // New line
          line->setLine (xLeft, yLeft, xRight, yRight);

        } else {

          // Keeping this intermediate point and clear out the removed points list
          removedPoints.clear();
        }
      }
    }

    lineOlder = line;
  }

  strDump << "set terminal x11 persist\n";
}

void Segment::setDocumentModelSegments (const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::setDocumentModelSegments";
}
