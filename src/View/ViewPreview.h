#ifndef VIEW_PREVIEW_H
#define VIEW_PREVIEW_H

#include <QGraphicsView>

/// Class that modifies QGraphicsView to automatically expand/shrink the view to fit the window, after resize events.
class ViewPreview : public QGraphicsView
{
public:
  /// Single constructor.
  ViewPreview(QGraphicsScene *scene,
              QWidget *parent = 0);

  /// Intercept resize events so we can rescale to the graphics items just fit into the resized window.
  virtual void resizeEvent(QResizeEvent *event);

private:
};

#endif // VIEW_PREVIEW_H
