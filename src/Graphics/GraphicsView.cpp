/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "GraphicsItemsExtractor.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "LoadFileInfo.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QApplication>
#include <QContextMenuEvent>
#include <QDebug>
#include <QDropEvent>
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
  connect (this, SIGNAL (signalContextMenuEventAxis (QString)), &mainWindow, SLOT (slotContextMenuEventAxis (QString)));
  connect (this, SIGNAL (signalContextMenuEventGraph (QStringList)), &mainWindow, SLOT (slotContextMenuEventGraph (QStringList)));
  connect (this, SIGNAL (signalDraggedDigFile (QString)), &mainWindow, SLOT (slotFileOpenDraggedDigFile (QString)));
  connect (this, SIGNAL (signalDraggedImage (QImage)), &mainWindow, SLOT (slotFileImportDraggedImage (QImage)));
  connect (this, SIGNAL (signalDraggedImageUrl (QUrl)), &mainWindow, SLOT (slotFileImportDraggedImageUrl (QUrl)));
  connect (this, SIGNAL (signalKeyPress (Qt::Key, bool)), &mainWindow, SLOT (slotKeyPress (Qt::Key, bool)));
  connect (this, SIGNAL (signalMouseMove(QPointF)), &mainWindow, SLOT (slotMouseMove (QPointF)));
  connect (this, SIGNAL (signalMousePress (QPointF)), &mainWindow, SLOT (slotMousePress (QPointF)));
  connect (this, SIGNAL (signalMouseRelease (QPointF)), &mainWindow, SLOT (slotMouseRelease (QPointF)));
  connect (this, SIGNAL (signalViewZoomIn ()), &mainWindow, SLOT (slotViewZoomInFromWheelEvent ()));
  connect (this, SIGNAL (signalViewZoomOut ()), &mainWindow, SLOT (slotViewZoomOutFromWheelEvent ()));

  setMouseTracking (true);
  setAcceptDrops (true);
  setEnabled (true);
  setRenderHints(QPainter::Antialiasing);
  setBackgroundBrush (QBrush (QColor (Qt::gray)));
  verticalScrollBar()->setCursor (QCursor (Qt::ArrowCursor));
  horizontalScrollBar()->setCursor (QCursor (Qt::ArrowCursor));

  // Skip setStatusTip here since that will overwrite much more important messages, and trigger gratuitous showing of status bar
  setWhatsThis (tr ("Main Window\n\n"
                    "After an image file is imported, or an Engauge Document opened, an image appears in this area. "
                    "Points are added to the image.\n\n"
                    "If the image is a graph with two axes and one or more curves, then three axis points must be "
                    "created along those axes. Just put two axis points on one axis and a third axis point on the other "
                    "axis, as far apart as possible for higher accuracy. Then curve points can be added along the curves.\n\n"
                    "If the image is a map with a scale to define length, then two axis points must be "
                    "created at either end of the scale. Then curve points can be added.\n\n"
                    "Zooming the image in or out is performed using any of several methods:\n"
                    "1) rotating the mouse wheel when the cursor is outside of the image\n"
                    "2) pressing the minus or plus keys\n"
                    "3) selecting a new zoom setting from the View/Zoom menu"));
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::contextMenuEvent"
                              << " selectedCount=" << scene()->selectedItems().count();

  GraphicsItemsExtractor graphicsItemsExtractor;
  const QList<QGraphicsItem*> &items = scene()->selectedItems();
  QStringList pointIdentifiers = graphicsItemsExtractor.selectedPointIdentifiers(items);

  if (pointIdentifiers.count() > 0) {

    if (graphicsItemsExtractor.allSelectedItemsAreEitherAxisOrGraph (items,
                                                                     GRAPH_POINTS)) {

      // One or more graph points are selected so edit their coordinates
      emit signalContextMenuEventGraph (pointIdentifiers);

    } else if (graphicsItemsExtractor.allSelectedItemsAreEitherAxisOrGraph (items,
                                                                            AXIS_POINTS) && pointIdentifiers.count() == 1) {

      // A single axis point is selected so edit it
      emit signalContextMenuEventAxis (pointIdentifiers.first());

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

  // Urls from text/uri-list
  QList<QUrl> urlList = event->mimeData ()->urls ();

  const QString MIME_FORMAT_TEXT_PLAIN ("text/plain");
  QString textPlain (event->mimeData()->data (MIME_FORMAT_TEXT_PLAIN));

  QUrl urlFirst;
  if (event->mimeData ()->hasUrls () &&
      urlList.count () > 0) {
    urlFirst = urlList.at (0);
  }

  QImage image;
  if (event->mimeData()->hasImage()) {
    image = qvariant_cast<QImage> (event->mimeData ()->imageData ());
  }

  if (handleDropEvent (textPlain,
                       event->mimeData ()->hasUrls (),
                       urlFirst,
                       event->mimeData ()->hasImage (),
                       image)) {

    event->acceptProposedAction();

  } else {

    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::dropEvent dropped";
    QGraphicsView::dropEvent (event);
  }
}

bool GraphicsView::handleDropEvent (const QString &possibleDigFileName,
                                    bool hasUrl,
                                    const QUrl &urlFirst,
                                    bool hasImage,
                                    const QImage &image)
{
  bool willAccept = false;

  LoadFileInfo loadFileInfo;
  if (loadFileInfo.loadsAsDigFile (possibleDigFileName)) {

    // Branch that applies when a dig file name has been dropped
    LOG4CPP_INFO_S ((*mainCat)) << "QGraphicsView::handleDropEvent dig file";
    QUrl url (possibleDigFileName);
    emit signalDraggedDigFile (url.toLocalFile());
    willAccept = true;

  } else if (hasImage) {

    // Branch that applies when an image selected within another application (e.g. LibreOffice Draw) has been dropped
    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::handleDropEvent image";
    emit signalDraggedImage (image);
    willAccept = true;

  } else if (hasUrl) {

    // Branch that applies when a local file name or internet url has been dropped
    LOG4CPP_INFO_S ((*mainCat)) << "GraphicsView::handleDropEvent url=" << urlFirst.toString ().toLatin1 ().data ();
    emit signalDraggedImageUrl (urlFirst);
    willAccept = true;
  }

  return willAccept;
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
  Qt::Key key = static_cast<Qt::Key> (event->key());

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

  if (!inBounds (posScreen)) {

    // Set to out-of-bounds value
    posScreen = QPointF (-1.0, -1.0);
  }

  emit signalMousePress (posScreen);

  QGraphicsView::mousePressEvent (event);
}

void GraphicsView::mouseReleaseEvent (QMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsView::mouseReleaseEvent signalMouseRelease";

  QPointF posScreen = mapToScene (event->pos ());

  if (!inBounds (posScreen)) {

    // Set to out-of-bounds value
    posScreen = QPointF (-1.0, -1.0);
  }

  // Send a signal, unless this is a right click. We still send if out of bounds since
  // a click-and-drag often ends out of bounds (and user is unlikely to expect different
  // behavior when endpoint is outside, versus inside, the image boundary)
  int bitFlag = (unsigned (event->buttons ()) & Qt::RightButton);
  bool isRightClick = (bitFlag != 0);

  if (!isRightClick) {

    emit signalMouseRelease (posScreen);

  }

  QGraphicsView::mouseReleaseEvent (event);
}

QStringList GraphicsView::pointIdentifiersFromSelection (const QList<QGraphicsItem*> &items) const
{
  // This method assumes that all specified items are points

  QStringList pointIdentifiers;

  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem *item = *itr;
    GraphicsItemType type = static_cast<GraphicsItemType> (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt ());
    ENGAUGE_ASSERT (type == GRAPHICS_ITEM_TYPE_POINT);

    QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString ();
    pointIdentifiers << pointIdentifier;
  }

  return pointIdentifiers;
}

void GraphicsView::slotDropRegression (QString urlText)
{
  // Regression test with local file or internet url specified
  QString emptyDigFileName;
  bool hasUrl = true;
  QUrl url (urlText); // Works as is for internet url
  if (!urlText.contains ("http")) {
    url = QUrl::fromLocalFile (urlText);
  }
  bool hasImage = false;
  QImage emptyImage;

  handleDropEvent (emptyDigFileName,
                   hasUrl,
                   url,
                   hasImage,
                   emptyImage);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
  const int ANGLE_THRESHOLD = 15; // From QWheelEvent documentation
  const int DELTAS_PER_DEGREE = 8; // From QWheelEvent documentation

  QPoint numDegrees = event->angleDelta() / DELTAS_PER_DEGREE;

  LOG4CPP_INFO_S ((*mainCat)) << "MainWindow::wheelEvent"
                              << " degrees=" << numDegrees.y()
                              << " phase=" << event->phase();

  // Criteria:
  // 1) User has enabled wheel zoom control (but that is not known here so MainWindow will handle that part)
  //    in slotViewZoomInFromWheelEvent and slotViewZoomOutFromWheelEvent
  // 2) Angle is over a threshold to eliminate false events from just touching wheel
  if ((event->modifiers() & Qt::ControlModifier) != 0) {

    if (numDegrees.y() >= ANGLE_THRESHOLD) {

      // Rotated backwards towards the user, which means zoom in
      emit signalViewZoomIn();

    } else if (numDegrees.y() <= -ANGLE_THRESHOLD) {

      // Rotated forwards away from the user, which means zoom out
      emit signalViewZoomOut();

    }

    // Accept the event as long as Control key was used and we are capturing wheel event
    event->accept();

  } else {

    // Let non-Control events manage scrolling
    QGraphicsView::wheelEvent (event);

  }
}
