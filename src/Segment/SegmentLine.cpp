#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPen>
#include "Segment.h"
#include "SegmentLine.h"

const double ZVALUE_SEGMENT = 50; // Less than z value for GraphicsPoint

SegmentLine::SegmentLine(QGraphicsScene  &scene,
                         const DocumentModelSegments &modelSegments,
                         Segment *segment) :
  m_modelSegments (modelSegments),
  m_segment (segment)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentLine::SegmentLine"
                               << " address=0x" << std::hex << (unsigned long) this;

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SEGMENT));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (Qt::transparent));
  setZValue (ZVALUE_SEGMENT);
  setVisible (true);
  setAcceptHoverEvents (true);
  setHover (false); // Initially the cursor is not hovering over this object. Later a hover event will change this state
  setFlags (QGraphicsItem::ItemIsFocusable);

  connect (this, SIGNAL (signalHover (bool)), segment, SLOT (slotHover (bool)));
}

SegmentLine::~SegmentLine ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "SegmentLine::~SegmentLine"
                               << " address=0x" << std::hex << (unsigned long) this;
}

void SegmentLine::hoverEnterEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::hoverEnterEvent";

  emit (signalHover (true));
}

void SegmentLine::hoverLeaveEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::hoverLeaveEvent";

  emit (signalHover (false));
}

void SegmentLine::mousePressEvent(QGraphicsSceneMouseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::mousePressEvent";

  m_segment->forwardMousePress();
}

Segment *SegmentLine::segment() const
{
  return m_segment;
}

void SegmentLine::setHover (bool hover)
{
  if (hover) {

    QColor color (ColorPaletteToQColor (m_modelSegments.lineColor()));

    setPen (QPen (QBrush (color),
                  m_modelSegments.lineWidth()));

  } else {

    setPen (QPen (Qt::transparent));

  }
}

void SegmentLine::updateModelSegment(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::updateModelSegment";

  m_modelSegments = modelSegments;
}
