#include "DigitizeStateContext.h"
#include "DigitizeStateSegment.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

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

void DigitizeStateSegment::updateSegments()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::updateSegments";

//  SegmentFactory segmentFactory (*m_scene);
//  QList<Segment*> segments;
//  segmentFactory.makeSegments (m_imageFiltered->pixmap().toImage(),
//                               m_cmdMediator->document().modelSegments(),
//                               segments);
}
