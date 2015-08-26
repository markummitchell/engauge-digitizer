#include "ColorFilter.h"
#include "DocumentModelSegments.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QProgressDialog>
#include "Segment.h"
#include "SegmentFactory.h"

using namespace std;

SegmentFactory::SegmentFactory(QGraphicsScene &scene,
                               bool isGnuplot) :
  m_scene (scene),
  m_isGnuplot (isGnuplot)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentFactory::SegmentFactory";
}

int SegmentFactory::adjacentRuns(bool *columnBool,
                                 int yStart,
                                 int yStop,
                                 int height)
{
  int runs = 0;
  bool inRun = false;
  for (int y = yStart - 1; y <= yStop + 1; y++) {
    if ((0 <= y) && (y < height)) {
      if (!inRun && columnBool [y]) {
        inRun = true;
        ++runs;
      } else if (inRun && !columnBool [y]) {
        inRun = false;
      }
    }
  }

  return runs;
}

Segment *SegmentFactory::adjacentSegment(SegmentVector &lastSegment,
                                         int yStart,
                                         int yStop,
                                         int height)
{
  for (int y = yStart - 1; y <= yStop + 1; y++) {
    if ((0 <= y) && (y < height)) {

      ENGAUGE_ASSERT (y < height);
      if (lastSegment [y]) {
        return lastSegment [y];
      }
    }
  }

  return 0;
}

int SegmentFactory::adjacentSegments(SegmentVector &lastSegment,
                                     int yStart,
                                     int yStop,
                                     int height)
{
  int adjacentSegments = 0;

  bool inSegment = false;
  for (int y = yStart - 1; y <= yStop + 1; y++) {
    if ((0 <= y) && (y < height)) {

      ENGAUGE_ASSERT (y < height);
      if (!inSegment && lastSegment [y]) {

       inSegment = true;
        ++adjacentSegments;
      } else if (inSegment && !lastSegment [y]) {
        inSegment = false;
      }
    }
  }

  return adjacentSegments;
}

QList<QPoint> SegmentFactory::fillPoints(const DocumentModelSegments &modelSegments,
                                         QList<Segment*> segments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentFactory::fillPoints";

  QList<QPoint> list;
  QList<Segment*>::iterator itr;
  for (itr = segments.begin (); itr != segments.end(); itr++) {

    Segment *segment = *itr;
    ENGAUGE_CHECK_PTR(segment);
    list += segment->fillPoints(modelSegments);
  }

  return list;
}

void SegmentFactory::finishRun(bool *lastBool,
                               bool *nextBool,
                               SegmentVector &lastSegment,
                               SegmentVector &currSegment,
                               int x,
                               int yStart,
                               int yStop,
                               int height,
                               const DocumentModelSegments &modelSegments,
                               int* madeLines)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentFactory::finishRun"
                               << " column=" << x
                               << " rows=" << yStart << "-" << yStop
                               << " runsOnLeft=" << adjacentRuns (nextBool, yStart, yStop, height)
                               << " runsOnRight=" << adjacentSegments (lastSegment, yStart, yStop, height);

  // When looking at adjacent columns, include pixels that touch diagonally since
  // those may also diagonally touch nearby runs in the same column (which would indicate
  // a branch)

  // Count runs that touch on the left
  if (adjacentRuns(lastBool, yStart, yStop, height) > 1) {
    return;
  }

  // Count runs that touch on the right
  if (adjacentRuns(nextBool, yStart, yStop, height) > 1) {
    return;
  }

  Segment *seg;
  if (adjacentSegments(lastSegment, yStart, yStop, height) == 0) {

    // This is the start of a new segment
    seg = new Segment(m_scene,
                      (int) (0.5 + (yStart + yStop) / 2.0),
                      m_isGnuplot);
    ENGAUGE_CHECK_PTR (seg);

  } else {

    // This is the continuation of an existing segment
    seg = adjacentSegment(lastSegment, yStart, yStop, height);

    ++(*madeLines);
    ENGAUGE_CHECK_PTR(seg);
    seg->appendColumn(x, (int) (0.5 + (yStart + yStop) / 2.0), modelSegments);
  }

  for (int y = yStart; y <= yStop; y++) {

    ENGAUGE_ASSERT (y < height);
    currSegment [y] = seg;
  }
}

void SegmentFactory::loadBool (const ColorFilter &filter,
                               bool *columnBool,
                               const QImage &image,
                               int x)
{
  for (int y = 0; y < image.height(); y++) {
    if (x < 0) {
      columnBool [y] = false;
    } else {
      columnBool [y] = filter.pixelFilteredIsOn (image, x, y);
    }
  }
}

void SegmentFactory::loadSegment (SegmentVector &columnSegment,
                                  int height)
{
  for (int y = 0; y < height; y++) {
    columnSegment [y] = 0;
  }
}

void SegmentFactory::makeSegments (const QImage &imageFiltered,
                                   const DocumentModelSegments &modelSegments,
                                   QList<Segment*> &segments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentFactory::makeSegments";

  // Statistics that show up in debug spew
  int madeLines = 0;
  int shortLines = 0; // Lines rejected since their segments are too short
  int foldedLines = 0; // Lines rejected since they could be into other lines

  // debugging with modal progress dialog box is problematic so make switchable
  const bool useDlg = true;

  // For each new column of pixels, loop through the runs. a run is defined as
  // one or more colored pixels that are all touching, with one uncolored pixel or the
  // image boundary at each end of the set. for each set in the current column, count
  // the number of runs it touches in the adjacent (left and right) columns. here is
  // the pseudocode:
  //   if ((L > 1) || (R > 1))
  //     "this run is at a branch point so ignore the set"
  //   else
  //     if (L == 0)
  //       "this run is the start of a new segment"
  //     else
  //       "this run is appended to the segment on the left
  int width = imageFiltered.width();
  int height = imageFiltered.height();

  QProgressDialog* dlg;
  if (useDlg)
  {

    dlg = new QProgressDialog("Scanning segments in image", "Cancel", 0, width);
    ENGAUGE_CHECK_PTR (dlg);
    dlg->show();
  }

  bool* lastBool = new bool [height];
  ENGAUGE_CHECK_PTR(lastBool);
  bool* currBool = new bool [height];
  ENGAUGE_CHECK_PTR(currBool);
  bool* nextBool = new bool [height];
  ENGAUGE_CHECK_PTR(nextBool);
  SegmentVector lastSegment (height);
  SegmentVector currSegment (height);

  ColorFilter filter;
  loadBool(filter, lastBool, imageFiltered, -1);
  loadBool(filter, currBool, imageFiltered, 0);
  loadBool(filter, nextBool, imageFiltered, 1);
  loadSegment(lastSegment, height);

  for (int x = 0; x < width; x++) {

    if (useDlg) {

      // Update progress bar
      dlg->setValue(x);
      qApp->processEvents();

      if (dlg->wasCanceled()) {

        // Quit scanning. only existing segments will be available
        break;
      }
    }

    matchRunsToSegments(x,
                        height,
                        lastBool,
                        lastSegment,
                        currBool,
                        currSegment,
                        nextBool,
                        modelSegments,
                        &madeLines,
                        &foldedLines,
                        &shortLines,
                        segments);

    // Get ready for next column
    scrollBool(lastBool, currBool, height);
    scrollBool(currBool, nextBool, height);
    if (x + 1 < width) {
      loadBool(filter, nextBool, imageFiltered, x + 1);
    }
    scrollSegment(lastSegment, currSegment, height);
  }

  if (useDlg) {

    dlg->setValue(width);
    delete dlg;
  }

  removeEmptySegments (segments);

  LOG4CPP_INFO_S ((*mainCat)) << "SegmentFactory::makeSegments"
                                 << " linesCreated=" << madeLines
                                 << " linesTooShortSoRemoved=" << shortLines
                                 << " linesFoldedTogether=" << foldedLines;

  delete[] lastBool;
  delete[] currBool;
  delete[] nextBool;
}

void SegmentFactory::matchRunsToSegments(int x,
                                         int height,
                                         bool *lastBool,
                                         SegmentVector &lastSegment,
                                         bool* currBool,
                                         SegmentVector &currSegment,
                                         bool *nextBool,
                                         const DocumentModelSegments &modelSegments,
                                         int *madeLines,
                                         int *foldedLines,
                                         int *shortLines,
                                         QList<Segment*> &segments)
{
  loadSegment(currSegment,
              height);

  int yStart = 0;
  bool inRun = false;
  for (int y = 0; y < height; y++) {

    ENGAUGE_ASSERT (y < height);
    if (!inRun && currBool [y]) {
      inRun = true;
      yStart = y;
    }

    if ((y + 1 >= height) || !currBool [y + 1]) {
      if (inRun) {
        finishRun(lastBool,
                  nextBool,
                  lastSegment,
                  currSegment,
                  x, yStart,
                  y,
                  height,
                  modelSegments,
                  madeLines);
      }

      inRun = false;
    }
  }

  removeUnneededLines(lastSegment,
                      currSegment,
                      height,
                      foldedLines,
                      shortLines,
                      modelSegments,
                      segments);
}

void SegmentFactory::removeEmptySegments (QList<Segment*> &segments) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentFactory::removeUnneededLines";

  for (int i = segments.count(); i > 0;) {

    --i;
    Segment *segment = segments.at (i);

    if (segment->lineCount () == 0) {

      // Remove this Segment
      delete segment;

      segments.removeAt (i);
    }
  }
}

void SegmentFactory::removeUnneededLines(SegmentVector &lastSegment,
                                         SegmentVector &currSegment,
                                         int height,
                                         int *foldedLines,
                                         int *shortLines,
                                         const DocumentModelSegments &modelSegments,
                                         QList<Segment*> &segments)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentFactory::removeUnneededLines";

  Segment *segLast = 0;
  for (int yLast = 0; yLast < height; yLast++) {

    ENGAUGE_ASSERT (yLast < height);
    if (lastSegment [yLast] && (lastSegment [yLast] != segLast)) {

      segLast = lastSegment [yLast];

      // If the segment is found in the current column then it is still in work so postpone processing
      bool found = false;
      for (int yCur = 0; yCur < height; yCur++) {

        ENGAUGE_ASSERT (yCur < height);
        if (segLast == currSegment [yCur]) {
          found = true;
          break;
        }
      }

      if (!found) {

        ENGAUGE_CHECK_PTR(segLast);
        if (segLast->length() < (modelSegments.minLength() - 1) * modelSegments.pointSeparation()) {

          // Remove whole segment since it is too short. Do NOT set segLast to zero since that
          // would cause this same segment to be deleted again in the next pixel if the segment
          // covers more than one pixel
          *shortLines += segLast->lineCount();
          delete segLast;
          lastSegment [yLast] = 0;

        } else {

          // Keep segment, but try to fold lines
          segLast->removeUnneededLines(foldedLines);

          // Add to the output array since it is done and sufficiently long
          segments.push_back (segLast);

        }
      }
    }
  }
}

void SegmentFactory::scrollBool(bool *left,
                                bool *right,
                                int height)
{
  for (int y = 0; y < height; y++) {
    left [y] = right [y];
  }
}

void SegmentFactory::scrollSegment(SegmentVector &left,
                                   SegmentVector &right,
                                   int height)
{
  for (int y = 0; y < height; y++) {
    left [y] = right [y];
  }
}

void SegmentFactory::clearSegments (QList<Segment*> &segments)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentFactory::clearSegments";

  QList<Segment*>::iterator itr;
  for (itr = segments.begin(); itr != segments.end(); itr++) {

    Segment *segment = *itr;

    delete segment;
  }

  segments.clear ();
}
