#include <QGraphicsRectItem>
#include "ViewProfile.h"
#include "ViewProfileDivider.h"
#include "ViewProfileParameters.h"
#include "ViewProfileShades.h"

const int FRAME_WIDTH = 2;
const double Z_VALUE_FRAME = 3.0; // Other z values are in ViewProfileDivider

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
  createDividers ();
  createShades ();
  refit ();
}

void ViewProfile::createDividers ()
{
  // For now just leave them at the edges
  double lowerX = VIEW_PROFILE_X_MIN;
  double upperX = VIEW_PROFILE_X_MAX;

  double lowerY = VIEW_PROFILE_Y_MIN + 0.66 * (VIEW_PROFILE_Y_MAX - VIEW_PROFILE_Y_MIN);
  double upperY = VIEW_PROFILE_Y_MIN + 0.33 * (VIEW_PROFILE_Y_MAX - VIEW_PROFILE_Y_MIN);

  m_dividerLower = new ViewProfileDivider (scene(), *this, lowerX, lowerY, true);
  m_dividerUpper = new ViewProfileDivider (scene(), *this, upperX, upperY, false);
}

void ViewProfile::createFrame ()
{
  m_frame = new QGraphicsRectItem (-1, -1, 102, 102);
  m_frame->setPen (QPen (QBrush (qRgb (0.0, 0.0, 0.0)), FRAME_WIDTH));
  m_frame->setZValue (Z_VALUE_FRAME);

  scene()->addItem (m_frame);
}

void ViewProfile::createShades ()\
{
  m_shades = new ViewProfileShades(scene());

  connect (m_dividerLower, SIGNAL (signalDividerMoved (bool, QPointF)), m_shades, SLOT (slotDividerMoved (bool, QPointF)));
  connect (m_dividerUpper, SIGNAL (signalDividerMoved (bool, QPointF)), m_shades, SLOT (slotDividerMoved (bool, QPointF)));
}

void ViewProfile::refit ()
{
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
