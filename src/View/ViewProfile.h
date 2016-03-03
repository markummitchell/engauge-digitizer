/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef VIEW_PROFILE_H
#define VIEW_PROFILE_H

#include <QGraphicsView>

class QGraphicsRectItem;

/// Class that modifies QGraphicsView to present a two-dimensional profile, with movable dividers for selecting a range.
class ViewProfile : public QGraphicsView
{
public:
  /// Single constructor.
  ViewProfile(QGraphicsScene *scene,
              int minimumWidth,
              QWidget *parent = 0);

  /// Intercept resize events so the geometry can be scaled to perfectly fit into the window.
  virtual void resizeEvent(QResizeEvent *event);

private:
  ViewProfile();

  void createFrame();
  void refit();

  QGraphicsRectItem *m_frame;
};

#endif // VIEW_PROFILE_H
