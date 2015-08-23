#include "DataKey.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QMimeData>
#include <QMouseEvent>
#include <QScrollBar>
#include "QtToString.h"

extern const QString AXIS_CURVE_NAME;

GraphicsView::GraphicsView(QGraphicsScene *scene,
                           MainWindow &mainWindow) :
  QGraphicsView (scene)
{
  connect (this, SIGNAL (signalContextMenuEvent (QString)), &mainWindow, SLOT (slotContextMenuEvent (QString)));
  connect (this, SIGNAL (signalDraggedImage (QImage)), &mainWindow, SLOT (slotFileImportDraggedImage (QImage)));
  connect (this, SIGNAL (signalDraggedImageUrl (QUrl)), &mainWindow, SLOT (slotFileImportDraggedImageUrl (QUrl)));
  connect (this, SIGNAL (signalKeyPress (Qt::Key, bool)), &mainWindow, SLOT (slotKeyPress (Qt::Key, bool)));
  connect (this, SIGNAL (signalLeave ()), &mainWindow, SLOT (slotLeave ()));
  connect (this, SIGNAL (signalMouseMove(QPointF)), &mainWindow, SLOT (slotMouseMove (QPointF)));
  connect (this, SIGNAL (signalMousePress (QPointF)), &mainWindow, SLOT (slotMousePress (QPointF)));
  connect (this, SIGNAL (signalMouseRelease (QPointF)), &mainWindow, SLOT (slotMouseRelease (QPointF)));

  setMouseTracking (true);
  setAcceptDrops (true);
  setEnabled (true);
  setRenderHints(QPainter::Antialiasing);
  setBackgroundBrush (QBrush (QColor (Qt::gray)));
  verticalScrollBar()->setCursor (QCursor (Qt::ArrowCursor));
  horizontalScrollBar()->setCursor (QCursor (Qt::ArrowCursor));

  // Skip setStatusTip here since that will overwrite much more important messages, and trigger gratuitous showing of status bar
  setWhatsThis (tr ("Document\n\n"
                    "After an image file is imported, or an Engauge Document opened, an image appears in this area. "
                    "Points are added to the image.\n\n"
                    "If the image is a graph with two axes and one or more curves, then three axis points must be "
                    "created along those axes. Just put two axis points on one axis and a third axis point on the other "
                    "axis, as far apart as possible for higher accuracy. Then curve points can be added along the curves.\n\n"
                    "If the image is a map with a scale to define length, then two axis points must be "
                    "created at either end of the scale. Then curve points can be added."));
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::contextMenuEvent (QContextMenuEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::contextMenuEvent";

  QList<QGraphicsItem*> items = scene()->selectedItems ();

  if (items.count () == 1) {

    QGraphicsItem *item = items.first ();
    QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString ();
    GraphicsItemType type = (GraphicsItemType) item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt ();
    QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

    if ((type == GRAPHICS_ITEM_TYPE_POINT) &&
        (curveName == AXIS_CURVE_NAME)) {

      // A single axis point is selected so edit it
      emit signalContextMenuEvent (pointIdentifier);
      event->accept ();

      return;
    }
  }

  QGraphicsView::contextMenuEvent (event);
}

void GraphicsView::dragEnterEvent (QDragEnterEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dragEnterEvent " << (event->mimeData ()->hasUrls () ? "urls" : "non-urls");

  if (event->mimeData ()->hasImage () ||
      event->mimeData ()->hasUrls ()) {
    event->acceptProposedAction();
  }
}

void GraphicsView::dragMoveEvent (QDragMoveEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dragMoveEvent";

  if (event->mimeData ()->hasImage () ||
      event->mimeData ()->hasUrls ()) {
    event->acceptProposedAction();
  }
}

void GraphicsView::dropEvent (QDropEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dropEvent";

  // This code is not specific to a digitizing state so it is implemented here

  // Urls from text/uri-list
  QList<QUrl> urlList = event->mimeData ()->urls ();
  QString urls;
  QTextStream str (&urls);
  QList<QUrl>::const_iterator itr;
  for (itr = urlList.begin (); itr != urlList.end (); itr++) {
    QUrl url = *itr;
    str << " url=" << url.toString () << " ";
  }

  if (event->mimeData ()->hasImage ()) {

    // This branch never seems to get executed, but will be kept in case it ever applies (since hasUrls branch is messier and less reliable)
    QImage image = qvariant_cast<QImage> (event->mimeData ()->imageData ());
    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dropEvent image";
    emit signalDraggedImage (image);

  } else if (event->mimeData ()->hasUrls ()) {

    // Sometimes images can be dragged in, but sometimes the url points to an html page that
    // contains just the image, in which case importing will fail
    QUrl url = urlList.at(0);
    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dropEvent url=" << url.toString ().toLatin1 ().data ();
    emit signalDraggedImageUrl (url);
    event->acceptProposedAction();

  } else {

    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dropEvent dropped";
    QGraphicsView::dropEvent (event);

  }
}

bool GraphicsView::inBounds (const QPointF &posScreen)
{
  QRectF boundingRect = scene()->sceneRect();

  return 0 <= posScreen.x () &&
         0 <= posScreen.y () &&
         posScreen.x () < boundingRect.width() &&
         posScreen.y () < boundingRect.height();
}

void GraphicsView::keyPressEvent (QKeyEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::keyPressEvent";

  // Intercept up/down/left/right if any items are selected
  Qt::Key key = (Qt::Key) event->key();

  bool atLeastOneSelectedItem = (scene ()->selectedItems ().count () > 0);

  if (key == Qt::Key_Down ||
      key == Qt::Key_Left ||
      key == Qt::Key_Right ||
      key == Qt::Key_Up) {

    emit signalKeyPress (key, atLeastOneSelectedItem);
    event->accept();

  } else {

    QGraphicsView::keyPressEvent (event);

  }
}

void GraphicsView::leaveEvent (QEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::leaveEvent";

  emit signalLeave ();

  QGraphicsView::leaveEvent (event);
}

void GraphicsView::mouseMoveEvent (QMouseEvent *event)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::mouseMoveEvent cursor="
//                               << QtCursorToString (cursor().shape()).toLatin1 ().data ();

  QPointF posScreen = mapToScene (event->pos ());

  if (!inBounds (posScreen)) {

    // Set to out-of-bounds value
    posScreen = QPointF (-1.0, -1.0);
  }

  emit signalMouseMove (posScreen);

  QGraphicsView::mouseMoveEvent (event);
}

void GraphicsView::mousePressEvent (QMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::mousePressEvent";

  QPointF posScreen = mapToScene (event->pos ());

  if (inBounds (posScreen)) {

    emit signalMousePress (posScreen);

  }

  QGraphicsView::mousePressEvent (event);
}

void GraphicsView::mouseReleaseEvent (QMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::mouseReleaseEvent";

  QPointF posScreen = mapToScene (event->pos ());

  // Skip if any of the following is true:
  // 1) Out of bounds
  // 2) Right click
  int bitFlag = (event->buttons () & Qt::RightButton);
  bool isRightClick = (bitFlag != 0);

  if (inBounds (posScreen) &&
      !isRightClick) {

    emit signalMouseRelease (posScreen);

  }

  QGraphicsView::mouseReleaseEvent (event);
}
