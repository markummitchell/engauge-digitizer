#ifndef SEGMENT_LINE_H
#define SEGMENT_LINE_H

#include "DocumentModelSegments.h"
#include <QGraphicsLineItem>

class QGraphicsScene;
class Segment;

/// This class is a special case of the standard QGraphicsLineItem for segments.
class SegmentLine : public QObject, public QGraphicsLineItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  SegmentLine(QGraphicsScene &scene,
              const DocumentModelSegments &modelSegments,
              Segment *segment);
  ~SegmentLine();

  /// Highlight this and all other SegmentLines belonging to the same Segment upon hover enter
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unset highlighting triggered by hover enter
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /// Create points along this curve
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /// Segment that owns this line
  Segment *segment() const;

  /// Apply/remove highlighting triggered by hover enter/leave
  void setHover (bool hover);

  /// Update this segment line with new settings
  void updateModelSegment(const DocumentModelSegments &modelSegments);

signals:
  /// Pass hover enter/leave events to Segment that owns this
  void signalHover (bool);

private:
  SegmentLine();

  DocumentModelSegments m_modelSegments;
  Segment *m_segment;
};

#endif // SEGMENT_LINE_H
