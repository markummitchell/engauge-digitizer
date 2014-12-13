#include "DlgDivider.h"
#include <QBrush>
#include <QCursor>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPen>

const double DIVIDER_WIDTH = 0.0; // Zero value gives a concise line that is a single pixel wide
const int PADDLE_HEIGHT = 10;
const int PADDLE_WIDTH = 10;
const double SHADED_AREA_OPACITY = 0.4;
const int X_INITIAL = 0;
const int SLOP = 2; // Pixels of shading added at each boundary to prevent a gap
const QColor SHADED_AREA_COLOR = QColor (200, 240, 200);
const QColor DIVIDER_COLOR = QColor (80, 200, 80);

DlgDivider::DlgDivider (QGraphicsScene &scene,
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

QVariant DlgDivider::itemChange (GraphicsItemChange change, const QVariant &value)
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
    m_divider->setLine (newX,
                        -SLOP,
                        newX,
                        2 * SLOP + m_sceneHeight);
    if (m_isLowerBoundary) {
      m_shadedArea->setRect (-SLOP,
                             -SLOP,
                             SLOP + newX,
                             2 * SLOP + m_sceneHeight);
    } else {
      m_shadedArea->setRect (newX,
                             -SLOP,
                             m_sceneWidth + SLOP - newX,
                             2 * SLOP + m_sceneHeight);
    }

    return newPos;
  }

  return QGraphicsRectItem::itemChange (change, value);
}

void DlgDivider::mousePressEvent(QGraphicsSceneMouseEvent * /* event */)
{
  // Since the cursor position is probably not in the center of the paddle, we save the paddle center
  m_startDragPos = QPointF (rect().x () + rect().width () / 2.0,
                            rect().y () + rect().height () / 2.0);
}

void DlgDivider::setX (int x)
{
  setRect (x - PADDLE_WIDTH / 2,
           m_yCenter - PADDLE_HEIGHT / 2,
           PADDLE_WIDTH,
           PADDLE_HEIGHT);

  m_divider->setLine (x,
                      -SLOP,
                      x,
                      2 * SLOP + m_sceneHeight);
  if (m_isLowerBoundary) {
    m_shadedArea->setRect (-SLOP,
                           -SLOP,
                           SLOP + x,
                           2 * SLOP + m_sceneHeight);
  } else {
    m_shadedArea->setRect (x,
                           -SLOP,
                           m_sceneWidth + SLOP - x,
                           2 * SLOP + m_sceneHeight);
  }
}
