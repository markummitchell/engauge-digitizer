#include "DlgBoundary.h"
#include <QBrush>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>

const int PADDLE_HEIGHT = 10;
const int PADDLE_WIDTH = 10;

DlgBoundary::DlgBoundary (QGraphicsScene &scene,
                          int sceneHeight,
                          int xAnchor,
                          int yCenter) :
  QGraphicsRectItem (xAnchor - PADDLE_WIDTH / 2,
                     yCenter - PADDLE_HEIGHT / 2,
                     PADDLE_WIDTH,
                     PADDLE_HEIGHT),
  m_xAnchor (xAnchor),
  m_yCenter (yCenter),
  m_boundary (0),
  m_shadedArea (0)
{
  setVisible (true);
  setPen (QPen (Qt::black));
  setBrush (QBrush (Qt::blue));
  scene.addItem (this);

  m_boundary = new QGraphicsLineItem (xAnchor,
                                      0,
                                      xAnchor,
                                      sceneHeight - 1);
  scene.addItem (m_boundary);

  m_shadedArea = new QGraphicsRectItem (xAnchor,
                                        0,
                                        0,
                                        sceneHeight - 1);
  scene.addItem (m_shadedArea);
}

void DlgBoundary::setX (int x)
{
  setRect (x - PADDLE_WIDTH / 2,
           m_yCenter - PADDLE_HEIGHT / 2,
           PADDLE_WIDTH,
           PADDLE_HEIGHT);
}
