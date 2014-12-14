#include <QGraphicsRectItem>
#include "ViewProfile.h"
#include "ViewProfileParameters.h"

const int FRAME_WIDTH = 2;

ViewProfile::ViewProfile(QGraphicsScene *scene,
                         QWidget *parent) :
  QGraphicsView (scene, parent)
{
  setRenderHint (QPainter::Antialiasing);
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

  setMinimumHeight (160);
  setMaximumHeight (160);
  setMinimumWidth (240);
  setMaximumWidth (240);

  createFrame ();
  refit ();
}

void ViewProfile::createFrame ()
{
  m_frame = new QGraphicsRectItem (-1, -1, 102, 102);
  m_frame->setPen (QPen (QBrush (qRgb (0.0, 0.0, 0.0)), FRAME_WIDTH));

  scene()->addItem (m_frame);
}

void ViewProfile::refit ()
{
  // Force the scene boundaries to be the same, even after resizing
  QRectF bounds = QRectF (VIEW_PROFILE_X_MIN,
                          VIEW_PROFILE_Y_MIN,
                          VIEW_PROFILE_X_MAX,
                          VIEW_PROFILE_Y_MAX);
  fitInView (bounds);
  setSceneRect (bounds);
}

void ViewProfile::resizeEvent(QResizeEvent *event)
{
  refit ();

  QGraphicsView::resizeEvent (event);
}
