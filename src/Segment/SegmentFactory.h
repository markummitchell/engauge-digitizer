#ifndef SEGMENT_FACTORY_H
#define SEGMENT_FACTORY_H

#include <QList>
#include <QPointF>
#include <vector>

class ColorFilter;
class DocumentModelSegments;
class QGraphicsScene;
class QImage;
class Segment;

typedef std::vector<Segment*> SegmentVector;

/// Factory class for Segment objects. The input is the filtered image.
///
/// The strategy is to fill out the segments output array as each segment finishes. This makes it easy to
/// keep too-short Segments out of the output array, versus adding every new Segment to the output array
/// as soon as it is created
class SegmentFactory
{
public:
  /// Single constructor.
  SegmentFactory(QGraphicsScene &scene,
                 bool isGnuplot);

  /// Remove the segments created by makeSegments
  void clearSegments(QList<Segment*> &segments);

  /// Return segment fill points for all segments, for previewing
  QList<QPoint> fillPoints(const DocumentModelSegments &modelSegments,
                           QList<Segment*> segments);

  /// Main entry point for creating all Segments for the filtered image.
  void makeSegments (const QImage &imageFiltered,
                     const DocumentModelSegments &modelSegments,
                     QList<Segment*> &segments);

private:
  SegmentFactory();

  // Return the number of runs adjacent to the pixels from yStart to yStop (inclusive)
  int adjacentRuns(bool *columnBool,
                   int yStart,
                   int yStop,
                   int height);

  // Find the single segment pointer among the adjacent pixels from yStart-1 to yStop+1
  Segment *adjacentSegment(SegmentVector &lastSegment,
                           int yStart,
                           int yStop,
                           int height);

  // Return the number of segments adjacent to the pixels from yStart to yStop (inclusive)
  int adjacentSegments(SegmentVector &lastSegment,
                       int yStart,
                       int yStop,
                       int height);

  // Process a run of pixels. If there are fewer than two adjacent pixel runs on
  // either side, this run will be added to an existing segment, or the start of
  // a new segment
  void finishRun(bool *lastBool,
                 bool *nextBool,
                 SegmentVector &lastSegment,
                 SegmentVector &currSegment,
                 int x,
                 int yStart,
                 int yStop,
                 int height,
                 const DocumentModelSegments &modelSegments,
                 int* madeLines);

  // Initialize one column of boolean flags using the pixels of the specified column
  void loadBool (const ColorFilter &filter,
                 bool *columnBool,
                 const QImage &image,
                 int x);

  // Initialize one column of segment pointers
  void loadSegment (SegmentVector &columnSegment,
                    int height);

  // Identify the runs in a column, and connect them to segments
  void matchRunsToSegments (int x,
                            int height,
                            bool *lastBool,
                            SegmentVector &lastSegment,
                            bool *currBool,
                            SegmentVector &currSegment,
                            bool *nextBool,
                            const DocumentModelSegments &modelSegments,
                            int *madeLines,
                            int *foldedLines,
                            int *shortLine,
                            QList<Segment*> &segments);

  /// Remove any Segment with no lines. This prevents crashes in Segment::firstPoint which requires at least one line in each Segment
  void removeEmptySegments (QList<Segment*> &segments) const;

  // Remove unneeded lines belonging to segments that just finished in the previous column.
  // The results of this function are displayed in the debug spew of makeSegments
  void removeUnneededLines(SegmentVector &lastSegment,
                           SegmentVector &currSegment,
                           int height,
                           int *foldedLines,
                           int *shortLines,
                           const DocumentModelSegments &modelSegments,
                           QList<Segment*> &segments);

  // Scroll the boolean flags of the right column into the left column
  void scrollBool(bool *left,
                  bool *right,
                  int height);

  // Scroll the segment pointers of the right column into the left column
  void scrollSegment(SegmentVector &left,
                     SegmentVector &right,
                     int height);

  QGraphicsScene &m_scene;

  bool m_isGnuplot;
};

#endif // SEGMENT_FACTORY_H
