#ifndef VIEW_PROFILE_H
#define VIEW_PROFILE_H

#include <QGraphicsView>

class QGraphicsRectItem;
class ViewProfileDivider;
class ViewProfileShades;

/// Class that modifies QGraphicsView to present a two-dimensional profile, with movable dividers for selecting a range.
class ViewProfile : public QGraphicsView
{
public:
  /// Single constructor.
  ViewProfile(QGraphicsScene *scene,
              QWidget *parent = 0);

  /// Intercept resize events so the geometry can be scaled to perfectly fit into the window.
  virtual void resizeEvent(QResizeEvent *event);

private:
  ViewProfile();

  void createDividers();
  void createFrame();
  void createShades ();
  void refit();

  QGraphicsRectItem *m_frame;
  ViewProfileDivider *m_dividerLower;
  ViewProfileDivider *m_dividerUpper;
  ViewProfileShades *m_shades;
};

#endif // VIEW_PROFILE_H
