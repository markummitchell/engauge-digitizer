#include "CallbackSceneUpdateAfterCommand.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsPoint.h"
#include "GraphicsPointFactory.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include "PointStyle.h"
#include <QApplication>
#include <QGraphicsItem>
#include "QtToString.h"

GraphicsScene::GraphicsScene(MainWindow *mainWindow) :
  QGraphicsScene(mainWindow)
{
}

GraphicsPoint *GraphicsScene::addPoint (const QString &identifier,
                                        const PointStyle &pointStyle,
                                        const QPointF &posScreen)
{
  double ordinal = maxOrdinal () + 1;

  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::addPoint"
                              << " identifier=" << identifier.toLatin1().data()
                              << " ordinal=" << ordinal;

  // Ordinal value is initially computed as one plus the max ordinal seen so far. This initial ordinal value will be overridden if the
  // cordinates determine the ordinal values.
  //
  // This is an N-squared algorithm and may be worth replacing later
  GraphicsPointFactory pointFactory;
  GraphicsPoint *point = pointFactory.createPoint (*this,
                                                   identifier,
                                                   posScreen,
                                                   pointStyle,
                                                   ordinal);

  point->setToolTip (identifier);
  point->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

  // Update the map
  ENGAUGE_ASSERT (!m_pointIdentifierToGraphicsPoint.contains (identifier));
  m_pointIdentifierToGraphicsPoint [identifier] = point;

  return point;
}

MapOrdinalToPointIdentifier GraphicsScene::createMapOrdinalToPointIdentifier ()
{
  // Start with empty map
  MapOrdinalToPointIdentifier map;

  PointIdentifierToGraphicsPoint::const_iterator itr;
  for (itr = m_pointIdentifierToGraphicsPoint.begin (); itr != m_pointIdentifierToGraphicsPoint.end (); itr++) {

    // Get item
    QString pointIdentifier = itr.key();
    GraphicsPoint *point = itr.value();

    double ordinal = point->data (DATA_KEY_ORDINAL).toDouble ();;

    map [ordinal] = pointIdentifier;
  }

  return map;
}

QString GraphicsScene::dumpCursors () const
{
  QString cursorOverride = (QApplication::overrideCursor () != 0) ?
                             QtCursorToString (QApplication::overrideCursor ()->shape ()) :
                             "<null>";
  QString cursorImage = QtCursorToString (image()->cursor().shape ());

  QString dump = QString ("overrideCursor=%1 imageCursor=%2")
      .arg (cursorOverride)
      .arg (cursorImage);

  return dump;
}

const QGraphicsPixmapItem *GraphicsScene::image () const
{
  // Loop through items in scene to find the image
  QList<QGraphicsItem*> items = QGraphicsScene::items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem* item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_IMAGE) {

      return (QGraphicsPixmapItem *) item;
    }
  }

  ENGAUGE_ASSERT (false);
  return 0;
}

double GraphicsScene::maxOrdinal () const
{
  // LOG4CPP_INFO_S is on exit

  double maxOrdinal = 0;

  const QList<QGraphicsItem*> &items = QGraphicsScene::items();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    const QGraphicsItem *item = *itr;

    // Only look at the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    if (isPoint) {

      // Save if max value so far
      double ordinal = item->data (DATA_KEY_ORDINAL).toDouble ();
      maxOrdinal = qMax (maxOrdinal, ordinal);
    }
  }

  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::maxOrdinal maxOrdinal=" << maxOrdinal;

  return maxOrdinal;
}

void GraphicsScene::moveLinesWithDraggedPoints (const CurveStyles &curveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::moveLinesWithDraggedPoints";

  // Ordinals must be updated to reflect reordering that may have resulted from dragging points
  updateOrdinalsAfterDrag (curveStyles);

  // Loop through items in scene and process the selected items. Note that the ordinal values
  // just set by updateOrdinalsAfterDrag in m_graphicsLinesForCurves override the ordinal values
  // in QGraphicsItem::data
  QList<QGraphicsItem*> items = QGraphicsScene::items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem* item = *itr;
    if ((item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT) &&
        item->isSelected()) {

      QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString();

      m_graphicsLinesForCurves.moveLinesWithDraggedPoint (pointIdentifier,
                                                          item->scenePos ());
    }
  }

  // Recompute the lines one time for efficiency
  m_graphicsLinesForCurves.moveLinesWithDraggedPoints (curveStyles);
}

QStringList GraphicsScene::positionHasChangedPointIdentifiers () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::positionHasChangedPointIdentifiers";

  QStringList movedIds;

  const QList<QGraphicsItem*> &items = QGraphicsScene::items();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    const QGraphicsItem *item = *itr;

    // Skip the image and only keep the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    if (isPoint) {

      QString identifier = item->data (DATA_KEY_IDENTIFIER).toString ();
      bool positionHasChanged = item->data (DATA_KEY_POSITION_HAS_CHANGED).toBool ();

      LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsScene::positionHasChangedPointIdentifiers"
                                   << " identifier=" << identifier.toLatin1().data()
                                   << " positionHasChanged=" << (positionHasChanged ? "yes" : "no");

      if (isPoint && positionHasChanged) {

        // Add Point to the list
        movedIds << item->data(DATA_KEY_IDENTIFIER).toString ();

      }
    }
  }

  return  movedIds;
}

void GraphicsScene::removePoint (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::removePoint identifier=" << identifier.toLatin1().data();

  GraphicsPoint *point = m_pointIdentifierToGraphicsPoint [identifier];
  m_pointIdentifierToGraphicsPoint.remove (identifier);
  delete point;
}

QStringList GraphicsScene::selectedPointIdentifiers () const
{
  QStringList selectedIds;

  const QList<QGraphicsItem*> &items = QGraphicsScene::items();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    const QGraphicsItem* item = *itr;

    // Skip the image and only keep the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    bool isSelected = item->isSelected ();
    if (isPoint && isSelected) {

      // Add Point to the list
      selectedIds << item->data(DATA_KEY_IDENTIFIER).toString ();

    }
  }

  return  selectedIds;
}

void GraphicsScene::showPoints (bool show,
                                bool showAll,
                                const QString &curveNameWanted)
{
  const QList<QGraphicsItem*> &items = QGraphicsScene::items();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem* item = *itr;

    // Skip the image and only process the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    if (isPoint) {

      bool showThisPoint = show;
      if (show && !showAll) {
        QString identifier = item->data (DATA_KEY_IDENTIFIER).toString ();
        QString curveNameGot = Point::curveNameFromPointIdentifier (identifier);

        showThisPoint = (curveNameWanted == curveNameGot);
      }

      item->setVisible (showThisPoint);

    }
  }
}

void GraphicsScene::updateAfterCommand (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateAfterCommand";

  // Update the points
  updatePointMembership (cmdMediator);

  // Update the lines between the points
  updateLinesBetweenPoints (cmdMediator);
}

void GraphicsScene::updateCurveStyles (const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateCurveStyles";

  // Loop through the points
  PointIdentifierToGraphicsPoint::iterator itr;
  for (itr = m_pointIdentifierToGraphicsPoint.begin(); itr != m_pointIdentifierToGraphicsPoint.end(); itr++) {

    QString pointIdentifier = itr.key();
    GraphicsPoint *point = itr.value();

    QString curveName = Point::curveNameFromPointIdentifier(pointIdentifier);

    CurveStyle curveStyle = modelCurveStyles.curveStyle(curveName);

    point->updateCurveStyle (curveStyle);
  }
}

void GraphicsScene::updateLinesBetweenPoints (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateLinesBetweenPoints";

  // Create a sorted map of ordinal to point identifier
  MapOrdinalToPointIdentifier mapOrdinalToPointIdentifier = createMapOrdinalToPointIdentifier();

  // Names of axis and graph curves
  QStringList curveNames;
  curveNames << AXIS_CURVE_NAME << cmdMediator.document().curvesGraphsNames();

  // Initialize before saving points
  m_graphicsLinesForCurves.updateStart();

  // Iterate through all points. The order, and grouping by curve, is not important since the
  // ordering and grouping is handled afterwards by updateFinish
  MapOrdinalToPointIdentifier::const_iterator itr;
  for (itr = mapOrdinalToPointIdentifier.begin (); itr != mapOrdinalToPointIdentifier.end (); itr++) {

    // Get point identifier for this ordinal
    QString pointIdentifier = itr.value();

    // Get point
    GraphicsPoint *point = m_pointIdentifierToGraphicsPoint [pointIdentifier];

    // Get parameters for the item
    QString curveNameGot = Point::curveNameFromPointIdentifier (pointIdentifier);
    double ordinal = point->data (DATA_KEY_ORDINAL).toDouble ();

    // Save entry even if entry already exists
    m_graphicsLinesForCurves.savePoint (*this,
                                        curveNameGot,
                                        pointIdentifier,
                                        ordinal,
                                        *point);
  }

  // Draw lines through the points that have been ordered by their ordinals
  m_graphicsLinesForCurves.updateFinish(cmdMediator.document().modelCurveStyles());
}

void GraphicsScene::updateOrdinalsAfterDrag (const CurveStyles &curveStyles)
{
  m_graphicsLinesForCurves.updateOrdinalsAfterDrag (curveStyles);
}

void GraphicsScene::updatePointMembership (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updatePointMembership";

  CallbackSceneUpdateAfterCommand ftor (m_pointIdentifierToGraphicsPoint,
                                        *this,
                                        cmdMediator.document ());
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackSceneUpdateAfterCommand::callback);

  // First pass:
  // 1) Mark all points as Not Wanted (this is done while creating the map)
  PointIdentifierToGraphicsPoint::iterator itr;
  for (itr = m_pointIdentifierToGraphicsPoint.begin (); itr != m_pointIdentifierToGraphicsPoint.end (); itr++) {
    GraphicsPoint *point = *itr;
    point->reset ();
  }

  // Next pass:
  // 1) Existing points that are found in the map are marked as Wanted
  // 2) Add new points that were just created in the Document. The new points are marked as Wanted
  cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);
  cmdMediator.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  // Next pass:
  // 1) Remove points that were just removed from the Document
  PointIdentifierToGraphicsPoint::iterator itrNext;
  for (itr = m_pointIdentifierToGraphicsPoint.begin (); itr != m_pointIdentifierToGraphicsPoint.end (); itr = itrNext) {

    // Save next value of iterator since current iterator may be invalidated
    itrNext = itr;
    ++itrNext;

    GraphicsPoint *point = itr.value();

    if (!point->wanted ()) {

      delete point;

      // Update map
      m_pointIdentifierToGraphicsPoint.erase (itr);
    }
  }
}
