/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeDebugPolar.h"
#include "DocumentModelCoords.h"
#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <qmath.h>
#include "QtToString.h"
#include "Transformation.h"

CentipedeDebugPolar::CentipedeDebugPolar() :
  m_posScreenParallelogramTL (0, 0),
  m_posScreenParallelogramTR (0, 0),
  m_posScreenParallelogramBL (0, 0),
  m_posScreenParallelogramBR (0, 0),
  m_angleGraphAxisFromScreenAxis (0),
  m_angleEllipseFromMajorAxis (0),
  m_aAligned (0),
  m_bAligned (0)
{
}

CentipedeDebugPolar::CentipedeDebugPolar(const QPointF &posScreenParallelogramTL,
                                         const QPointF &posScreenParallelogramTR,
                                         const QPointF &posScreenParallelogramBL,
                                         const QPointF &posScreenParallelogramBR,
                                         double angleGraphAxisFromScreenAxis,
                                         double angleEllipseFromMajorAxis,
                                         double aAligned,
                                         double bAligned) :
  m_posScreenParallelogramTL (posScreenParallelogramTL),
  m_posScreenParallelogramTR (posScreenParallelogramTR),
  m_posScreenParallelogramBL (posScreenParallelogramBL),
  m_posScreenParallelogramBR (posScreenParallelogramBR),
  m_angleGraphAxisFromScreenAxis (angleGraphAxisFromScreenAxis),
  m_angleEllipseFromMajorAxis (angleEllipseFromMajorAxis),
  m_aAligned (aAligned),
  m_bAligned (bAligned)
{
}

CentipedeDebugPolar::CentipedeDebugPolar (const CentipedeDebugPolar &other) :
  m_posScreenParallelogramTL (other.posScreenParallelogramTL ()),
  m_posScreenParallelogramTR (other.posScreenParallelogramTR ()),
  m_posScreenParallelogramBL (other.posScreenParallelogramBL ()),
  m_posScreenParallelogramBR (other.posScreenParallelogramBR ()),
  m_angleGraphAxisFromScreenAxis (other.angleGraphAxisFromScreenAxis ()),
  m_angleEllipseFromMajorAxis (other.angleEllipseFromMajorAxis ()),
  m_aAligned (other.aAligned ()),
  m_bAligned (other.bAligned ())
{
}

CentipedeDebugPolar &CentipedeDebugPolar::operator= (const CentipedeDebugPolar &other)
{
  m_posScreenParallelogramTL = other.posScreenParallelogramTL ();
  m_posScreenParallelogramTR = other.posScreenParallelogramTR ();
  m_posScreenParallelogramBL = other.posScreenParallelogramBL ();
  m_posScreenParallelogramBR = other.posScreenParallelogramBR ();
  m_angleGraphAxisFromScreenAxis = other.angleGraphAxisFromScreenAxis ();
  m_angleEllipseFromMajorAxis = other.angleEllipseFromMajorAxis ();
  m_aAligned = other.aAligned ();
  m_bAligned = other.bAligned ();

  return *this;
}
CentipedeDebugPolar::~CentipedeDebugPolar()
{
}

double CentipedeDebugPolar::aAligned () const
{
  return m_aAligned;
}

double CentipedeDebugPolar::angleEllipseFromMajorAxis () const
{
  return m_angleEllipseFromMajorAxis;
}

double CentipedeDebugPolar::angleGraphAxisFromScreenAxis () const
{
  return m_angleGraphAxisFromScreenAxis;
}

double CentipedeDebugPolar::bAligned () const
{
  return m_bAligned;
}

void CentipedeDebugPolar::display (QGraphicsScene &scene,
                                   const DocumentModelCoords &modelCoords,
                                   const Transformation &transformation) const
{
  if (mainCat->getPriority() == log4cpp::Priority::DEBUG) {

    // Center
    QPointF posCenterGraph (0, 0), posCenterScene;
    if (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      posCenterGraph = QPointF (0,
                                modelCoords.originRadius());
    }
    transformation.transformRawGraphToScreen (posCenterGraph,
                                              posCenterScene);

    // Circumscribing parallelogram
    QVector<QPointF> points;
    points << m_posScreenParallelogramBL;
    points << m_posScreenParallelogramTL;
    points << m_posScreenParallelogramTR;
    points << m_posScreenParallelogramBR;
    points << m_posScreenParallelogramBL;
    QGraphicsPolygonItem *parallelogram = new QGraphicsPolygonItem (points);
    parallelogram->setPen (QPen (Qt::red));
    scene.addItem (parallelogram);

    // Right-angled rectangle
    QRectF rect (posCenterScene.x() - m_aAligned,
                 posCenterScene.y() - m_bAligned,
                 2 * m_aAligned,
                 2 * m_bAligned);
    rect.setLeft (posCenterScene.x() - m_aAligned);
    rect.setTop (posCenterScene.y() - m_bAligned);

    // Circumscribing rectangle
    QGraphicsRectItem *rectItem = new QGraphicsRectItem (rect);
    rectItem->setTransformOriginPoint(posCenterScene);
    rectItem->setRotation (qRadiansToDegrees (m_angleEllipseFromMajorAxis));
    rectItem->setPen (QPen (Qt::red));
    scene.addItem (rectItem);

    // Put an ellipse in the circumscribing rectangle to see if they line up
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem (rect);
    ellipse->setTransformOriginPoint (posCenterScene);
    ellipse->setRotation (qRadiansToDegrees (m_angleEllipseFromMajorAxis));
    ellipse->setPen (QPen (Qt::red));
    scene.addItem (ellipse);

    // Show regularly spaced (in graph coordinates) radial lines. In graph coordinates
    // the ellipse is a circle. We get a rough radius by pretending the semimajor axis is
    // along the +x screen direction. This is good enough for an axis that is always big enough to see
    QPointF posHorizontalScene = posCenterScene + QPointF (0, m_aAligned);
    QPointF posHorizontalGraph;
    transformation.transformScreenToRawGraph (posHorizontalScene,
                                              posHorizontalGraph);

    // the ellipse is x^2/a^2+y^2/b^2=1 and x=r*cos(theta) and y=r*sin(theta) we can solve
    // to get r=sqrt(1/(cos(theta)^2/a^2+sin(theta)^2/b^2)
    for (int degrees = 0; degrees < 360; degrees += 10) {

      QPointF posEllipseGraph (degrees,
                               posHorizontalGraph.y());
      QPointF posEllipseScene;
      transformation.transformRawGraphToScreen (posEllipseGraph,
                                                posEllipseScene);
      QGraphicsLineItem *radial = new QGraphicsLineItem (QLineF (posCenterScene,
                                                                 posEllipseScene));
      radial->setPen (QPen (Qt::red));
      scene.addItem (radial);
    }
  }
}

void CentipedeDebugPolar::dumpEllipseGraphicsItem (const QString &callerMethod,
                                                   const QGraphicsEllipseItem *ellipse) const
{
  if (mainCat->getPriority () == log4cpp::Priority::DEBUG) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeDebugPolar::dumpEllipseGraphicsItem dump from "
                                 << callerMethod.toLatin1().data();
    LOG4CPP_DEBUG_S ((*mainCat)) << "    rect=" << QRectFToString (ellipse->rect()).toLatin1().data();
    LOG4CPP_DEBUG_S ((*mainCat)) << "    rotation=" << ellipse->rotation();
    LOG4CPP_DEBUG_S ((*mainCat)) << "    start=" << (ellipse->startAngle() / 16.0);
    LOG4CPP_DEBUG_S ((*mainCat)) << "    span=" << (ellipse->spanAngle() / 16.0);
    LOG4CPP_DEBUG_S ((*mainCat)) << "    transformOrigin=" << QPointFToString (ellipse->transformOriginPoint()).toLatin1().data();
    LOG4CPP_DEBUG_S ((*mainCat)) << "    pos=" << QPointFToString (ellipse->pos ()).toLatin1().data();
  }
}

QPointF CentipedeDebugPolar::posScreenParallelogramBL () const
{
  return m_posScreenParallelogramBL;
}

QPointF CentipedeDebugPolar::posScreenParallelogramBR () const
{
  return m_posScreenParallelogramBR;
}

QPointF CentipedeDebugPolar::posScreenParallelogramTL () const
{
  return m_posScreenParallelogramTL;
}

QPointF CentipedeDebugPolar::posScreenParallelogramTR () const
{
  return m_posScreenParallelogramTR;
}
