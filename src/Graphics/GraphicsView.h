#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QImage>
#include <QUrl>

class MainWindow;
class QByteArray;
class QGraphicsPixmapItem;
class QGraphicsScene;

/// QGraphicsView class with event handling added. Typically the events are sent to the active digitizing state.
class GraphicsView : public QGraphicsView
{
  Q_OBJECT;

public:
  /// Single constructor.
  GraphicsView(QGraphicsScene *scene,
               MainWindow &mainWindow);
  virtual ~GraphicsView();

  /// Intercept right click to support point editing.
  void contextMenuEvent (QContextMenuEvent *event);

  /// Intercept mouse drag event to support drag-and-drop.
  virtual void dragEnterEvent (QDragEnterEvent *event);

  /// Intercept mouse move event to support drag-and-drop.
  virtual void dragMoveEvent (QDragMoveEvent *event);

  /// Intercept mouse drop event to support drag-and-drop. This initiates asynchronous loading of the dragged image
  virtual void dropEvent (QDropEvent *event);

  /// Intercept key press events to handle left/right/up/down moving.
  virtual void keyPressEvent (QKeyEvent *event);

  /// Intercept leave events to manage override cursor.
  virtual void leaveEvent (QEvent *event);

  /// Intercept mouse move events to populate the current cursor position in StatusBar.
  virtual void mouseMoveEvent (QMouseEvent *event);

  /// Intercept mouse press events to create one or more Points.
  virtual void mousePressEvent (QMouseEvent *event);

  /// Intercept mouse release events to move one or more Points.
  virtual void mouseReleaseEvent (QMouseEvent *event);

signals:
  /// Send right click on axis point to MainWindow for editing.
  void signalContextMenuEvent (QString pointIdentifier);

  /// Send dragged dig file to MainWindow for import. This comes from dragging an engauge dig file
  void signalDraggedDigFile (QString);

  /// Send dragged image to MainWindow for import. This typically comes from dragging a file
  void signalDraggedImage (QImage);

  /// Send dragged url to MainWindow for import. This typically comes from dragging an image from a browser
  void signalDraggedImageUrl (QUrl);

  /// Send keypress to MainWindow for eventual processing by DigitizeStateAbstractBase subclasses.
  void signalKeyPress (Qt::Key, bool atLeastOneSelectedItem);

  /// Send leave to MainWindow for managing the override cursor.
  void signalLeave ();

  /// Send mouse move to MainWindow for eventual display of cursor coordinates in StatusBar
  void signalMouseMove (QPointF);

  /// Send mouse press to MainWindow for creating one or more Points
  void signalMousePress (QPointF);

  /// Send mouse release to MainWindow for moving Points.
  void signalMouseRelease (QPointF);

private:
  GraphicsView();

  bool inBounds (const QPointF &posScreen);
  bool loadsAsDigFile (const QString &urlString) const;
};

#endif // GRAPHICSVIEW_H
