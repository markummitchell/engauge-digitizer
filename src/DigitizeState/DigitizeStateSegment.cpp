#include "DigitizeStateContext.h"
#include "DigitizeStateSegment.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include "Segment.h"
#include "SegmentFactory.h"

DigitizeStateSegment::DigitizeStateSegment (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateSegment::~DigitizeStateSegment ()
{
}

QString DigitizeStateSegment::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateSegment::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());

  handleCurveChange();
}

void DigitizeStateSegment::clearSegments ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSegment::clearSegments";

  QList<Segment*>::iterator itr;
  for (itr = m_segments.begin(); itr != m_segments.end(); itr++) {

    Segment *segment = *itr;

    delete segment;
  }

  m_segments.clear ();
}

QCursor DigitizeStateSegment::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSegment::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateSegment::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::end";
}

void DigitizeStateSegment::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleCurveChange";

  QImage img = context().mainWindow().imageFiltered();

  GraphicsScene &scene = context().mainWindow().scene();
  SegmentFactory segmentFactory ((QGraphicsScene &) scene);

  clearSegments ();

  // Create new segments
  segmentFactory.makeSegments (img,
                               context().cmdMediator().document().modelSegments(),
                               m_segments);
}

void DigitizeStateSegment::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateSegment::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMousePress";
}

void DigitizeStateSegment::handleMouseRelease (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMouseRelease";
}

QString DigitizeStateSegment::state() const
{
  return "DigitizeStateSegment";
}
