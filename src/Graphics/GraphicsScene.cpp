#include "CallbackSceneUpdateAfterCommand.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "DataKey.h"
#include "DocumentModelCurveProperties.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsLine.h"
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
  Q_ASSERT (!m_mapPointIdentifierToGraphicsPoint.contains (identifier));
  m_mapPointIdentifierToGraphicsPoint [identifier] = point;

  return point;
}

MapOrdinalToPointIdentifier GraphicsScene::createMapOrdinalToPointIdentifier ()
{
  // Start with empty map
  MapOrdinalToPointIdentifier map;

  PointIdentifierToGraphicsPoint::const_iterator itr;
  for (itr = m_mapPointIdentifierToGraphicsPoint.begin (); itr != m_mapPointIdentifierToGraphicsPoint.end (); itr++) {

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
  QList<QGraphicsItem*> items = QGraphicsScene::items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem* item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_IMAGE) {

      return (QGraphicsPixmapItem *) item;
    }
  }

  Q_ASSERT (false);
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

  GraphicsPoint *point = m_mapPointIdentifierToGraphicsPoint [identifier];
  m_mapPointIdentifierToGraphicsPoint.remove (identifier);
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

  updatePoints (cmdMediator);
  updateLines (cmdMediator);
}

void GraphicsScene::updateCurveProperties (const DocumentModelCurveProperties &modelCurveProperties)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateCurveProperties";
}

void GraphicsScene::updateLines (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateLines";

  // Remove all old entries
  m_graphicsLinesForCurves.resetPoints ();

  // Create a sorted map of ordinal to point identifier
  MapOrdinalToPointIdentifier mapOrdinalToPointIdentifier = createMapOrdinalToPointIdentifier();

  // Names of axis and graph curves
  QStringList curveNames;
  curveNames << AXIS_CURVE_NAME << cmdMediator.document().curvesGraphsNames();

  // Loop through the curves. Processing one curve at a time is simpler than trying to process all in parallel
  QStringList::iterator itrC;
  for (itrC = curveNames.begin (); itrC != curveNames.end (); itrC++) {

    QString curveNameWanted = *itrC;

    // Last values
    double ordinalLast = -1;
    GraphicsPoint *pointLast = 0;

    // We use the automatic sorting by key of QMap, to sort by ordinal
    MapOrdinalToPointIdentifier::const_iterator itr;
    for (itr = mapOrdinalToPointIdentifier.begin (); itr != mapOrdinalToPointIdentifier.end (); itr++) {

      // Get point identifier for this ordinal
      QString pointIdentifier = itr.value();

      // Get point
      GraphicsPoint *point = m_mapPointIdentifierToGraphicsPoint [pointIdentifier];

      // Get parameters for the item
      QString curveNameGot = Point::curveNameFromPointIdentifier (pointIdentifier);
      double ordinal = point->data (DATA_KEY_ORDINAL).toDouble ();

      // Skip this point if it is not in the desired curve
      if (curveNameWanted == curveNameGot) {

        if (pointLast != 0) {

          // Each line is associated only with the lower ordinal value, to prevent ambiguity
          double ordinalAssociated = qMin (ordinalLast, ordinal);
          double ordinalOther = qMax (ordinalLast, ordinal);

          // Save entry even if entry already exists
          m_graphicsLinesForCurves.saveLine (*this,
                                             curveNameGot,
                                             ordinalAssociated,
                                             ordinalOther,
                                             *pointLast,
                                             *point,
                                             cmdMediator.document().modelCurveProperties().lineStyle(curveNameGot));
        }

        ordinalLast = ordinal;
        pointLast = point;
      }
    }
  }

  m_graphicsLinesForCurves.updateLines (*this);
}

void GraphicsScene::updatePoints (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updatePoints";

  CallbackSceneUpdateAfterCommand ftor (m_mapPointIdentifierToGraphicsPoint,
                                        *this,
                                        cmdMediator.document ());
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackSceneUpdateAfterCommand::callback);

  // First pass:
  // 1) Mark all points as Not Wanted (this is done while creating the map)
  PointIdentifierToGraphicsPoint::iterator itr;
  for (itr = m_mapPointIdentifierToGraphicsPoint.begin (); itr != m_mapPointIdentifierToGraphicsPoint.end (); itr++) {
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
  for (itr = m_mapPointIdentifierToGraphicsPoint.begin (); itr != m_mapPointIdentifierToGraphicsPoint.end (); itr = itrNext) {

    // Save next value of iterator since current iterator may be invalidated
    itrNext = itr;
    ++itrNext;

    GraphicsPoint *point = itr.value();

    if (!point->wanted ()) {

      delete point;

      // Update map
      m_mapPointIdentifierToGraphicsPoint.erase (itr);
    }
  }
}
