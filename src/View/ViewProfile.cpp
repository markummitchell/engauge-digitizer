/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <QGraphicsRectItem>
#include "ViewProfile.h"
#include "ViewProfileParameters.h"

const int FRAME_WIDTH = 2;

// Insert a little space on the left and right so first and last points are visible. Although the
// ViewProfile will no longer be exactly aligned with the ViewScale underneath, the difference is insignificant
const double SLOP_ON_SIDES = 0.5;

ViewProfile::ViewProfile(QGraphicsScene *scene,
                         int minimumWidth,
                         QWidget *parent) :
  QGraphicsView (scene, parent)
{
  setRenderHint (QPainter::Antialiasing);
  setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

  setMinimumHeight (160);
  setMaximumHeight (160);
  setMinimumWidth (minimumWidth);

  createFrame ();
  refit ();
}

void ViewProfile::createFrame ()
{
  m_frame = new QGraphicsRectItem (0, 0, 100, 100);
  m_frame->setPen (QPen (QBrush (qRgb (0.0, 0.0, 0.0)), FRAME_WIDTH));

  scene()->addItem (m_frame);
}

void ViewProfile::refit ()
{
  // Force the scene boundaries to be the same, even after resizing
  QRectF bounds = QRectF (VIEW_PROFILE_X_MIN - SLOP_ON_SIDES,
                          VIEW_PROFILE_Y_MIN,
                          VIEW_PROFILE_X_MAX + 2 * SLOP_ON_SIDES,
                          VIEW_PROFILE_Y_MAX);
  fitInView (bounds);
  setSceneRect (bounds);
}

void ViewProfile::resizeEvent(QResizeEvent *event)
{
  refit ();

  QGraphicsView::resizeEvent (event);
}
