/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelSegments.h"
#include "EngaugeAssert.h"
#include "gnuplot.h"
#include <iostream>
#include "Logger.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <QFile>
#include <QGraphicsScene>
#include <qmath.h>
#include <QTextStream>
#include "QtToString.h"
#include "Segment.h"
#include "SegmentLine.h"

Segment::Segment(QGraphicsScene &scene,
                 int y,
                 bool isGnuplot) :
  m_scene (scene),
  m_yLast (y),
  m_length (0),
  m_isGnuplot (isGnuplot)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::Segment"
                              << " address=0x" << hex << (quintptr) this;
}

Segment::~Segment()
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::~Segment"
                              << " address=0x" << hex << (quintptr) this;

  QList<SegmentLine*>::iterator itr;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *segmentLine = *itr;
    m_scene.removeItem (segmentLine);
  }
}

void Segment::appendColumn(int x,
                           int y,
                           const DocumentModelSegments &modelSegments)
{
  int xOld = x - 1;
  int yOld = m_yLast;
  int xNew = x;
  int yNew = y;

  LOG4CPP_DEBUG_S ((*mainCat)) << "Segment::appendColumn"
                               << " segment=0x" << std::hex << (quintptr) this << std::dec
                               << " adding ("
                               << xOld << "," << yOld << ") to ("
                               << xNew << "," << yNew << ")";

  SegmentLine* line = new SegmentLine(m_scene,
                                      modelSegments,
                                      this);
  ENGAUGE_CHECK_PTR(line);
  line->setLine(QLineF (xOld,
                        yOld,
                        xNew,
                        yNew));

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
  // Only show this dump spew when logging is opened up completely
  if (mainCat->getPriority() == log4cpp::Priority::DEBUG) {

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
      ENGAUGE_CHECK_PTR (line);

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

      double xStart = (double) line->line().x1();
      double yStart = (double) line->line().y1();
      if (isCorner (yPrev, yStart, yNext)) {

        // Insert a corner point
        createAcceptablePoint(&firstPoint, &list, &xPrev, &yPrev, xStart, yStart);
        distanceCompleted = 0.0;
      }

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

QPointF Segment::firstPoint () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::firstPoint"
                              << " lineCount=" << m_lines.count();

  // There has to be at least one SegmentLine since this only gets called when a SegmentLine is clicked on
  ENGAUGE_ASSERT (m_lines.count () > 0);

  SegmentLine *line = m_lines.first();
  QPointF pos = line->line().p1();

  LOG4CPP_INFO_S ((*mainCat)) << "Segment::firstPoint"
                              << " pos=" << QPointFToString (pos).toLatin1().data();

  return pos;
}

void Segment::forwardMousePress()
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::forwardMousePress"
                              << " segmentLines=" << m_lines.count();

  emit signalMouseClickOnSegment (firstPoint ());
}

bool Segment::isCorner (double yLast,
                        double yPrev,
                        double yNext) const
{
  // Rather than deal with slopes, and a risk of dividing by zero, we just use the y deltas
  double deltaYBefore = yPrev - yLast;
  double deltaYAfter = yNext - yPrev;
  bool upThenAcrossOrDown = (deltaYBefore > 0) && (deltaYAfter <= 0);
  bool downThenAcrossOrUp = (deltaYBefore < 0) && (deltaYAfter >= 0);

  return upThenAcrossOrDown || downThenAcrossOrUp;
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

void Segment::removeUnneededLines (int *foldedLines)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::removeUnneededLines";

  QFile *fileDump = 0;
  QTextStream *strDump = 0;
  if (m_isGnuplot) {

    QString filename ("segment.gnuplot");

    std::cout << GNUPLOT_FILE_MESSAGE.toLatin1().data() << filename.toLatin1().data() << "\n";

    fileDump = new QFile (filename);
    fileDump->open (QIODevice::WriteOnly | QIODevice::Text);
    strDump = new QTextStream (fileDump);

  }

  // Pathological case is y=0.001*x*x, since the small slope can fool a naive algorithm
  // into optimizing away all but one point at the origin and another point at the far right.
  // From this we see that we cannot simply throw away points that were optimized away since they
  // are needed later to see if we have diverged from the curve
  SegmentLine *linePrevious = 0; // Previous line which corresponds to itrPrevious
  QList<SegmentLine*>::iterator itr, itrPrevious;
  QList<QPoint> removedPoints;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *line = *itr;
    ENGAUGE_CHECK_PTR(line);

    if (linePrevious != 0) {

      double xLeft = linePrevious->line().x1();
      double yLeft = linePrevious->line().y1();
      double xInt = linePrevious->line().x2();
      double yInt = linePrevious->line().y2();

      // If linePrevious is the last line of one Segment and line is the first line of another Segment then
      // it makes no sense to remove any point so we continue the loop
      if (linePrevious->line().p2() == line->line().p1()) {

        double xRight = line->line().x2();
        double yRight = line->line().y2();

        if (pointIsCloseToLine(xLeft, yLeft, xInt, yInt, xRight, yRight) &&
          pointsAreCloseToLine(xLeft, yLeft, removedPoints, xRight, yRight)) {

          if (m_isGnuplot) {

            // Dump
            dumpToGnuplot (*strDump,
                           xInt,
                           yInt,
                           linePrevious,
                           line);
          }

          // Remove intermediate point, by removing older line and stretching new line to first point
          ++(*foldedLines);

          LOG4CPP_DEBUG_S ((*mainCat)) << "Segment::removeUnneededLines"
                                       << " segment=0x" << std::hex << (quintptr) this << std::dec
                                       << " removing ("
                                       << linePrevious->line().x1() << "," << linePrevious->line().y1() << ") to ("
                                       << linePrevious->line().x2() << "," << linePrevious->line().y2() << ") "
                                       << " and modifying ("
                                       << line->line().x1() << "," << line->line().y1() << ") to ("
                                       << line->line().x2() << "," << line->line().y2() << ") into ("
                                       << xLeft << "," << yLeft << ") to ("
                                       << xRight << "," << yRight << ")";

          removedPoints.append(QPoint((int) xInt, (int) yInt));
          m_lines.erase (itrPrevious);
          delete linePrevious;

          // New line
          line->setLine (xLeft, yLeft, xRight, yRight);

        } else {

          // Keeping this intermediate point and clear out the removed points list
          removedPoints.clear();
        }
      }
    }

    linePrevious = line;
    itrPrevious = itr;

    // This theoretically should not be needed, but for some reason modifying the last point triggers a segfault
    if (itr == m_lines.end()) {
      break;
    }
  }

  if (strDump != 0) {

    // Final gnuplot processing
    *strDump << "set terminal x11 persist\n";
    fileDump->close ();
    delete strDump;
    delete fileDump;

  }
}

void Segment::slotHover (bool hover)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::slotHover";

  QList<SegmentLine*>::iterator itr, itrPrevious;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *line = *itr;
    line->setHover(hover);
  }
}

void Segment::updateModelSegment(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Segment::updateModelSegment";

  QList<SegmentLine*>::iterator itr;
  for (itr = m_lines.begin(); itr != m_lines.end(); itr++) {

    SegmentLine *line = *itr;
    line->updateModelSegment (modelSegments);
  }
}
