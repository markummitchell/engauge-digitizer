#ifndef VIEW_PREVIEW_H
#define VIEW_PREVIEW_H

#include <QGraphicsView>
#include <QPointF>

/// Class that modifies QGraphicsView to automatically expand/shrink the view to fit the window, after resize events.
class ViewPreview : public QGraphicsView
{
  Q_OBJECT;

public:

  /// Prevent aspect ratio distortion in certain previews by providing fixed 1:1 aspect ratio option
  enum ViewAspectRatio {
    VIEW_ASPECT_RATIO_VARIABLE,
    VIEW_ASPECT_RATIO_ONE_TO_ONE
  };

  /// Single constructor.
  ViewPreview(QGraphicsScene *scene,
              ViewAspectRatio viewAspectRatio,
              QWidget *parent = 0);

  /// Intercept cursor move events and forward them
  virtual void mouseMoveEvent(QMouseEvent *event);

  /// Intercept resize events so we can rescale to the graphics items just fit into the resized window.
  virtual void resizeEvent(QResizeEvent *event);

signals:
  /// Forward the mouse move events
  void signalMouseMove (QPointF pos);

private:
  ViewPreview();

  ViewAspectRatio m_viewAspectRatio;
};

#endif // VIEW_PREVIEW_H
