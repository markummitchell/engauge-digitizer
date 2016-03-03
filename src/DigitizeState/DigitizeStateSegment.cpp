/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointsGraph.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateSegment.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "OrdinalGenerator.h"
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

void DigitizeStateSegment::begin (CmdMediator *cmdMediator,
                                  DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::begin";

  m_cmdMediator = cmdMediator; // Save for slotMouseClickOnSegment

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());

  handleCurveChange(cmdMediator);
}

QCursor DigitizeStateSegment::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSegment::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateSegment::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::end";

  GraphicsScene &scene = context().mainWindow().scene();
  SegmentFactory segmentFactory ((QGraphicsScene &) scene,
                                 context().isGnuplot());

  segmentFactory.clearSegments(m_segments);
}

void DigitizeStateSegment::handleCurveChange(CmdMediator *cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleCurveChange";

  QImage img = context().mainWindow().imageFiltered();

  GraphicsScene &scene = context().mainWindow().scene();
  SegmentFactory segmentFactory ((QGraphicsScene &) scene,
                                 context().isGnuplot());

  segmentFactory.clearSegments (m_segments);

  // Create new segments
  segmentFactory.makeSegments (img,
                               cmdMediator->document().modelSegments(),
                               m_segments);

  // Connect signals of the new segments
  QList<Segment*>::iterator itr;
  for (itr = m_segments.begin(); itr != m_segments.end(); itr++) {
    Segment *segment = *itr;

    LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleCurveChange"
                                << " lines=" << segment->lineCount();

    connect (segment, SIGNAL (signalMouseClickOnSegment (QPointF)), this, SLOT (slotMouseClickOnSegment (QPointF)));
  }
}

void DigitizeStateSegment::handleKeyPress (CmdMediator * /* cmdMediator */,
                                           Qt::Key key,
                                           bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateSegment::handleMouseMove (CmdMediator * /* cmdMediator */,
                                            QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSegment::handleMouseMove";
}

void DigitizeStateSegment::handleMousePress (CmdMediator * /* cmdMediator */,
                                             QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMousePress";
}

void DigitizeStateSegment::handleMouseRelease (CmdMediator * /* cmdMediator */,
                                               QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::handleMouseRelease";
}

Segment *DigitizeStateSegment::segmentFromSegmentStart (const QPointF &posSegmentStart) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::segmentFromSegmentStart"
                              << " segments=" << m_segments.count();

  QList<Segment*>::const_iterator itr;
  for (itr = m_segments.begin(); itr != m_segments.end(); itr++) {
    Segment *segment = *itr;

    if (segment->firstPoint() == posSegmentStart) {

      return segment;
    }
  }

  LOG4CPP_ERROR_S ((*mainCat)) << "DigitizeStateSegment::segmentFromSegmentStart";
  ENGAUGE_ASSERT (false);
  return 0;
}

void DigitizeStateSegment::slotMouseClickOnSegment(QPointF posSegmentStart)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::slotMouseClickOnSegment";

  Segment *segment = segmentFromSegmentStart (posSegmentStart);

  // Create single-entry list that is expected by SegmentFactory
  QList<Segment*> segments;
  segments.push_back (segment);

  // Generate point coordinates. Nothing is created in the GraphicsScene at this point
  GraphicsScene &scene = context().mainWindow().scene();
  SegmentFactory segmentFactory ((QGraphicsScene &) scene,
                                 context().isGnuplot());

  QList<QPoint> points = segmentFactory.fillPoints (m_cmdMediator->document().modelSegments(),
                                                    segments);

  // Create one ordinal for each point
  OrdinalGenerator ordinalGenerator;
  Document &document = m_cmdMediator->document ();
  const Transformation &transformation = context ().mainWindow ().transformation();
  QList<double> ordinals;
  QList<QPoint>::iterator itr;
  for (itr = points.begin(); itr != points.end(); itr++) {

    QPoint point = *itr;
    ordinals << ordinalGenerator.generateCurvePointOrdinal(document,
                                                           transformation,
                                                           point,
                                                           activeCurve ());
  }

  // Create command to add points
  QUndoCommand *cmd = new CmdAddPointsGraph (context ().mainWindow(),
                                             document,
                                             context ().mainWindow().selectedGraphCurve(),
                                             points,
                                             ordinals);
  context().appendNewCmd(m_cmdMediator,
                         cmd);
}

QString DigitizeStateSegment::state() const
{
  return "DigitizeStateSegment";
}

void DigitizeStateSegment::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                     const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::updateModelDigitizeCurve";
}

void DigitizeStateSegment::updateModelSegments(const DocumentModelSegments &modelSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSegment::updateModelSegments";

  QList<Segment*>::const_iterator itr;
  for (itr = m_segments.begin(); itr != m_segments.end(); itr++) {
    Segment *segment = *itr;

    segment->updateModelSegment (modelSegments);
  }
}
