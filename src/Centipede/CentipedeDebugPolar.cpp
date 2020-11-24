/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeDebugPolar.h"
#include "DocumentModelCoords.h"
#include "Logger.h"
#include "mmsubs.h"
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
  m_bAligned (0),
  m_radius (0)
{
}

CentipedeDebugPolar::CentipedeDebugPolar(const QPointF &posScreenParallelogramTL,
                                         const QPointF &posScreenParallelogramTR,
                                         const QPointF &posScreenParallelogramBL,
                                         const QPointF &posScreenParallelogramBR,
                                         double angleGraphAxisFromScreenAxis,
                                         double angleEllipseFromMajorAxis,
                                         double aAligned,
                                         double bAligned,
                                         double radius) :
  m_posScreenParallelogramTL (posScreenParallelogramTL),
  m_posScreenParallelogramTR (posScreenParallelogramTR),
  m_posScreenParallelogramBL (posScreenParallelogramBL),
  m_posScreenParallelogramBR (posScreenParallelogramBR),
  m_angleGraphAxisFromScreenAxis (angleGraphAxisFromScreenAxis),
  m_angleEllipseFromMajorAxis (angleEllipseFromMajorAxis),
  m_aAligned (aAligned),
  m_bAligned (bAligned),
  m_radius (radius)
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
  m_bAligned (other.bAligned ()),
  m_radius (other.radius ())
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
  m_radius = other.radius ();

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
  // LOG4CPP is below

  if (mainCat->getPriority() == log4cpp::Priority::DEBUG) {

    // Center
    QPointF posCenterGraph (0, 0), posCenterScreen;
    if (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      posCenterGraph = QPointF (0,
                                modelCoords.originRadius());
    }
    transformation.transformRawGraphToScreen (posCenterGraph,
                                              posCenterScreen);

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
    QRectF rect (posCenterScreen.x() - m_aAligned,
                 posCenterScreen.y() - m_bAligned,
                 2 * m_aAligned,
                 2 * m_bAligned);
    rect.setLeft (posCenterScreen.x() - m_aAligned);
    rect.setTop (posCenterScreen.y() - m_bAligned);

    // Circumscribing rectangle
    QGraphicsRectItem *rectItem = new QGraphicsRectItem (rect);
    rectItem->setTransformOriginPoint(posCenterScreen);
    rectItem->setRotation (qRadiansToDegrees (m_angleEllipseFromMajorAxis));
    rectItem->setPen (QPen (Qt::red));
    scene.addItem (rectItem);

    // Put an ellipse in the circumscribing rectangle to see if they line up
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem (rect);
    ellipse->setTransformOriginPoint (posCenterScreen);
    ellipse->setRotation (qRadiansToDegrees (m_angleEllipseFromMajorAxis));
    ellipse->setPen (QPen (Qt::red));
    scene.addItem (ellipse);

    // A and B axes
    QPointF posAAxisGraph (0, m_radius), posBAxisGraph (90, m_radius);
    QPointF posAAxisScreen, posBAxisScreen;
    transformation.transformRawGraphToScreen (posAAxisGraph,
                                              posAAxisScreen);
    transformation.transformRawGraphToScreen (posBAxisGraph,
                                              posBAxisScreen);

    // Show one inner set of radial tic lines and one outer set of radial tic lines
    double cosOffset = qCos (m_angleEllipseFromMajorAxis);
    double sinOffset = qSin (m_angleEllipseFromMajorAxis);
    for (int degrees = 0; degrees < 360; degrees++) {

      // Inner set of radial tic lines is regularly spaced in screen coordinates. We solve x=r*cosT, y=r*sinT,
      // x^2/a^2 + y^2/b^2 = 1. Ellipse points are then rotated
      double radians = qDegreesToRadians ((double) degrees);
      double cosLoop = qCos(radians);
      double sinLoop = qSin(radians);
      double denominator = cosLoop * cosLoop / m_aAligned / m_aAligned  + sinLoop * sinLoop / m_bAligned / m_bAligned;
      double radius = qSqrt (1.0 / denominator);
      double x = radius * cosLoop;
      double y = radius * sinLoop;
      double xRotated = cosOffset * x - sinOffset * y;
      double yRotated = sinOffset * x + cosOffset * y;
      QPointF posRadial (xRotated,
                         yRotated);

      QGraphicsLineItem *radialFirst = new QGraphicsLineItem (portionOfLineLast (QLineF (posCenterScreen,
                                                                                         posCenterScreen + posRadial),
                                                                                 degrees));
      radialFirst->setPen (QPen (Qt::black));
      scene.addItem (radialFirst);

      // Second set of radial tic lines is regularly spaced in graph coordinates
      transformation.transformRawGraphToScreen (QPointF (degrees,
                                                         m_radius),
                                                posRadial);
      QGraphicsLineItem *radialSecond = new QGraphicsLineItem (portionOfLineNext (QLineF (posCenterScreen,
                                                                                          posRadial),
                                                                                  degrees));
      radialSecond->setPen (QPen (Qt::red));
      scene.addItem (radialSecond);
    }

    // Finish up with details in log stream
    LOG4CPP_DEBUG_S ((*mainCat)) << "CentipedeDebugPolar::displa"
                                 << " angleFromAxis=" << qDegreesToRadians (m_angleEllipseFromMajorAxis)
                                 << " angleFromScreen=" << qDegreesToRadians (m_angleGraphAxisFromScreenAxis)
                                 << " lambdaX=" << lambdaX (posAAxisScreen,
                                                            posBAxisScreen);
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
    LOG4CPP_DEBUG_S ((*mainCat)) << "    radius=" << m_radius;
  }
}

double CentipedeDebugPolar::lambdaX (const QPointF &posAAxisScreen,
                                     const QPointF &posBAxisScreen) const
{
  // If there waS no shear then these vectors would be 90 degrees apart. From this diagram we have
  // tan (theta) = -lambdaX * y / (-y) = lambdaX
  //
  //           -lambdaX * y
  //          |-------------*
  //          |            *
  //          |           *
  //          |          *
  //          |         *
  //      -y  |        *
  //          |       *
  //          |      *
  //          |     *
  //          |--- *  theta
  //          |   *
  //          |  *
  //          | *
  //          ============================ +x
  double thetaComplement = angleBetweenVectors(posAAxisScreen,
                                               posBAxisScreen);
  double theta = M_PI / 2.0 - thetaComplement;
  return qTan (theta);
}

QLineF CentipedeDebugPolar::portionOfLineLast (const QLineF &line,
                                               int degrees) const
{
  double s = (degrees % 10 ? 0.975 : 0.9);
  QPointF posNewStart = (1.0 - s) * line.p1() + s * line.p2 ();
  return QLineF(posNewStart,
                line.p2());
}

QLineF CentipedeDebugPolar::portionOfLineNext (const QLineF &line,
                                               int degrees) const
{
  double s = (degrees % 10 ? 1.025 : 1.1);
  QPointF posNewStart = (1.0 - s) * line.p1() + s * line.p2 ();
  return QLineF(posNewStart,
                line.p2());
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

double CentipedeDebugPolar::radius () const
{
  return m_radius;
}
