/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPen>
#include "ViewProfileDivider.h"

const double ARROW_WIDTH = 4.0;
const double ARROW_HEIGHT = 5.0;
const double DIVIDER_WIDTH = 0.0; // Zero value gives a concise line that is a single pixel wide
const int PADDLE_HEIGHT = 10;
const int PADDLE_WIDTH = 10;
const double SHADED_AREA_OPACITY = 0.4;
const int X_INITIAL = 0;
const int SLOP = 2; // Pixels of shading added at each boundary to prevent a gap
const QColor ARROW_COLOR (Qt::NoPen);
const QColor SHADED_AREA_COLOR = QColor (220, 220, 220); // Light gray
const QColor DIVIDER_COLOR = QColor (140, 140, 255); // Slightly darker gray

ViewProfileDivider::ViewProfileDivider (QGraphicsScene &scene,
                                        QGraphicsView &view,
                                        int sceneWidth,
                                        int sceneHeight,
                                        int yCenter,
                                        bool isLowerBoundary) :
  QGraphicsRectItem (X_INITIAL,
                     0,
                     PADDLE_WIDTH,
                     PADDLE_HEIGHT),
  m_view (view),
  m_yCenter (yCenter),
  m_divider (0),
  m_shadedArea (0),
  m_sceneWidth (sceneWidth),
  m_sceneHeight (sceneHeight),
  m_isLowerBoundary (isLowerBoundary)
{
  // Initial positions will not appear since they are overridden by setX

  // Paddle
  setVisible (true);
  setPen (QPen (DIVIDER_COLOR));
  setBrush (QBrush (QColor (140, 255, 140)));
  setOpacity (1.0);
  scene.addItem (this);
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
  setCursor (Qt::OpenHandCursor);
  setZValue (2.0);

  // Arrow on paddle
  m_arrow = new QGraphicsPolygonItem (this);

  // Shaded area
  m_shadedArea = new QGraphicsRectItem (X_INITIAL,
                                        0,
                                        0,
                                        sceneHeight - 1);
  m_shadedArea->setOpacity (SHADED_AREA_OPACITY);
  m_shadedArea->setBrush (QBrush (SHADED_AREA_COLOR));
  m_shadedArea->setPen (Qt::NoPen);
  m_shadedArea->setZValue (0.0);
  scene.addItem (m_shadedArea);

  // Vertical divider. This is not made a child of the paddle since that will force the divider
  // to always be drawn above the paddle, rather than underneath the paddle as we want. Even setting
  // the z values will not succeed in drawing the divider under the paddle if they are child-parent.
  m_divider = new QGraphicsLineItem (X_INITIAL,
                                     -SLOP,
                                     X_INITIAL,
                                     2 * SLOP + sceneHeight);
  m_divider->setPen (QPen (QBrush (DIVIDER_COLOR), DIVIDER_WIDTH));
  m_divider->setZValue (1.0);
  scene.addItem (m_divider);
}

QVariant ViewProfileDivider::itemChange (GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionChange && scene ()) {

    // Clip x coordinate, in pixel coordinates. Y coordinate stays the same (by setting delta to zero)
    QPointF newPos = QPointF (value.toPointF().x(), 0.0) + m_startDragPos;
    double newX = newPos.x();
    newX = qMax (newX, 0.0);
    newX = qMin (newX, (double) m_sceneWidth);
    newPos.setX (newX);
    newPos -= m_startDragPos; // Change from absolute coordinates back to relative coordinates

    // Before returning newPos for the paddle, we apply its movement to the divider and shaded area
    m_xScene = newX;
    updateGeometryDivider();
    updateGeometryNonPaddle ();

    sendSignalMoved ();

    return newPos;
  }

  return QGraphicsRectItem::itemChange (change, value);
}

void ViewProfileDivider::mousePressEvent(QGraphicsSceneMouseEvent * /* event */)
{
  // Since the cursor position is probably not in the center of the paddle, we save the paddle center
  m_startDragPos = QPointF (rect().x () + rect().width () / 2.0,
                            rect().y () + rect().height () / 2.0);
}

void ViewProfileDivider::sendSignalMoved ()
{
  if (m_isLowerBoundary) {
    emit signalMovedLow (m_xScene);
  } else {
    emit signalMovedHigh (m_xScene);
  }
}

void ViewProfileDivider::setX (double x,
                               double xLow,
                               double xHigh)
{
  // Convert to screen coordinates
  m_xScene = m_sceneWidth * (x - xLow) / (xHigh - xLow);
  sendSignalMoved ();

  updateGeometryPaddle ();
  updateGeometryDivider ();
  updateGeometryNonPaddle ();

  // Triangle vertices
  double xLeft = rect().left() + rect().width() / 2.0 - ARROW_WIDTH / 2.0;
  double xRight = rect().left() + rect().width() / 2.0 + ARROW_WIDTH / 2.0;
  double yTop = rect().top() + rect().height() / 2.0 - ARROW_HEIGHT / 2.0;
  double yMiddle = rect().top() + rect().height() / 2.0;
  double yBottom = rect().top() + rect().height() / 2.0 + ARROW_HEIGHT / 2.0;

  QPolygonF polygonArrow;
  if (m_isLowerBoundary) {

    // Draw arrow pointing to the right
    polygonArrow.push_front (QPointF (xLeft, yTop));
    polygonArrow.push_front (QPointF (xRight, yMiddle));
    polygonArrow.push_front (QPointF (xLeft, yBottom));

  } else {

    // Draw arrow pointing to the left
    polygonArrow.push_front (QPointF (xRight, yTop));
    polygonArrow.push_front (QPointF (xLeft, yMiddle));
    polygonArrow.push_front (QPointF (xRight, yBottom));
  }
  m_arrow->setPolygon (polygonArrow);
  m_arrow->setPen (QPen (Qt::black));
  m_arrow->setBrush (QBrush (ARROW_COLOR));
}

void ViewProfileDivider::slotOtherMoved(double xSceneOther)
{
  m_xSceneOther = xSceneOther;
  updateGeometryNonPaddle ();
}

void ViewProfileDivider::updateGeometryDivider ()
{
  m_divider->setLine (m_xScene,
                      -SLOP,
                      m_xScene,
                      2 * SLOP + m_sceneHeight);
}

void ViewProfileDivider::updateGeometryNonPaddle()
{
  if (m_isLowerBoundary) {
    if (m_xScene <= m_xSceneOther) {

      // There is one unshaded region in the center
      m_shadedArea->setRect (-SLOP,
                             -SLOP,
                             SLOP + m_xScene,
                             2 * SLOP + m_sceneHeight);

    } else {

      // There are two unshaded regions on the two sides
      m_shadedArea->setRect (m_xSceneOther,
                             -SLOP,
                             m_xScene - m_xSceneOther,
                             2 * SLOP + m_sceneHeight);

    }
  } else {

    if (m_xSceneOther <= m_xScene) {

      // There are two unshaded regions on the two sides
      m_shadedArea->setRect (m_xScene,
                             -SLOP,
                             SLOP + m_sceneWidth - m_xScene,
                             2 * SLOP + m_sceneHeight);

    } else {

      // There is one unshaded region in the center. To prevent extra-dark shading due to having two
      // overlapping shaded areas, this shaded area is given zero extent
      m_shadedArea->setRect (m_xSceneOther,
                             -SLOP,
                             0,
                             2 * SLOP + m_sceneHeight);
    }
  }
}

void ViewProfileDivider::updateGeometryPaddle ()
{
  setRect (m_xScene - PADDLE_WIDTH / 2,
           m_yCenter - PADDLE_HEIGHT / 2,
           PADDLE_WIDTH,
           PADDLE_HEIGHT);
}
