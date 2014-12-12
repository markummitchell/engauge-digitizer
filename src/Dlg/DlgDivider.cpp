#include "DlgDivider.h"
#include <QBrush>
#include <QCursor>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>

const int PADDLE_HEIGHT = 10;
const int PADDLE_WIDTH = 10;

DlgDivider::DlgDivider (QGraphicsScene &scene,
                        int sceneHeight,
                        int xAnchor,
                        int yCenter) :
  QGraphicsRectItem (xAnchor - PADDLE_WIDTH / 2,
                     yCenter - PADDLE_HEIGHT / 2,
                     PADDLE_WIDTH,
                     PADDLE_HEIGHT),
  m_xAnchor (xAnchor),
  m_yCenter (yCenter),
  m_divider (0),
  m_shadedArea (0)
{
  setVisible (true);
  setPen (QPen (Qt::black));
  setBrush (QBrush (Qt::blue));
  scene.addItem (this);
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
  setCursor (Qt::OpenHandCursor);

  m_divider = new QGraphicsLineItem (xAnchor,
                                     0,
                                     xAnchor,
                                     sceneHeight - 1);
  scene.addItem (m_divider);

  m_shadedArea = new QGraphicsRectItem (xAnchor,
                                        0,
                                        0,
                                        sceneHeight - 1);
  scene.addItem (m_shadedArea);
}

QVariant DlgDivider::itemChange (GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionChange && scene ()) {

    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();

    if (!rect.contains (newPos)) {

      newPos.setX (qMin (rect.right (),
                         qMax (newPos.x(), rect.left ())));
    }

    newPos.setY (m_yCenter - PADDLE_HEIGHT / 2.0);

    return newPos;
  }

  return QGraphicsRectItem::itemChange (change, value);
}

void DlgDivider::setX (int x)
{
  setRect (x - PADDLE_WIDTH / 2,
           m_yCenter - PADDLE_HEIGHT / 2,
           PADDLE_WIDTH,
           PADDLE_HEIGHT);
}
