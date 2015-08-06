#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPen>
#include "Segment.h"
#include "SegmentLine.h"

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
  setZValue (100.0);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable);
  setHover (false);

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

  emit (signalMouse ());
}

Segment *SegmentLine::segment() const
{
  return m_segment;
}

void SegmentLine::setHover (bool hover)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::setHover"
                              << " hover=" << (hover ? "true" : "false");

  if (hover) {

    QColor color (ColorPaletteToQColor (m_modelSegments.lineColor()));

    setPen (QPen (QBrush (color),
                  m_modelSegments.lineWidth()));

  } else {

    setPen (QPen (Qt::transparent));

  }
}
