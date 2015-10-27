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
#include "Transformation.h"

GraphicsScene::GraphicsScene(MainWindow *mainWindow) :
  QGraphicsScene(mainWindow)
{
}

void GraphicsScene::addTemporaryPoint (const QString &identifier,
                                       GraphicsPoint *point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::addTemporaryPoint"
                              << " identifer=" << identifier.toLatin1().data();

  m_graphicsLinesForCurves.addPoint (AXIS_CURVE_NAME,
                                     identifier,
                                     Point::UNDEFINED_ORDINAL (),
                                     *point);
}

GraphicsPoint *GraphicsScene::createPoint (const QString &identifier,
                                           const PointStyle &pointStyle,
                                           const QPointF &posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::createPoint"
                              << " identifier=" << identifier.toLatin1().data();

  // Ordinal value is initially computed as one plus the max ordinal seen so far. This initial ordinal value will be overridden if the
  // cordinates determine the ordinal values.
  //
  // This is an N-squared algorithm and may be worth replacing later
  GraphicsPointFactory pointFactory;
  GraphicsPoint *point = pointFactory.createPoint (*this,
                                                   identifier,
                                                   posScreen,
                                                   pointStyle);

  point->setToolTip (identifier);
  point->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

  return point;
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

  return 0;
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

void GraphicsScene::printStream (QString indentation,
                                 QTextStream &str)
{
  m_graphicsLinesForCurves.printStream (indentation,
                                        str);
}

void GraphicsScene::removePoint (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::removePoint identifier=" << identifier.toLatin1().data();

  m_graphicsLinesForCurves.removePoint (identifier);
}

void GraphicsScene::removeTemporaryPointIfExists ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::removeTemporaryPointIfExists";

  m_graphicsLinesForCurves.removeTemporaryPointIfExists ();
}

void GraphicsScene::resetOnLoad()
{
  // LOG4CPP_INFO_S is below

  int itemsBefore = items().count();

  m_graphicsLinesForCurves.resetOnLoad();

  int itemsAfter = items().count();

  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::resetOnLoad"
                              << " itemsBefore=" << itemsBefore
                              << " itemsAfter=" << itemsAfter;
}

void GraphicsScene::resetPositionHasChangedFlags()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::resetPositionHasChangedFlags";

  QList<QGraphicsItem*> itms = items ();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = itms.begin (); itr != itms.end (); itr++) {

    QGraphicsItem *item = *itr;
    item->setData (DATA_KEY_POSITION_HAS_CHANGED, false);
  }
}

QStringList GraphicsScene::selectedPointIdentifiers () const
{
  const QList<QGraphicsItem*> &items = QGraphicsScene::selectedItems();

  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::selectedPointIdentifiers"
                              << " selectedItems=" << items.count();

  QStringList selectedIds;
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    const QGraphicsItem* item = *itr;

    // Skip the image and only keep the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    if (isPoint) {

      // Add Point to the list
      selectedIds << item->data(DATA_KEY_IDENTIFIER).toString ();

    }
  }

  return  selectedIds;
}

void GraphicsScene::showCurves (bool show,
                                bool showAll,
                                const QString &curveNameWanted)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::showCurves"
                              << " show=" << (show ? "true" : "false")
                              << " showAll=" << (showAll ? "true" : "false")
                              << " curve=" << curveNameWanted.toLatin1().data();

  const QList<QGraphicsItem*> &items = QGraphicsScene::items();
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem* item = *itr;

    // Skip the image and only process the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    bool isCurve = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_LINE);

    if (isPoint || isCurve) {

      bool showThis = show;
      if (show && !showAll) {
        QString identifier = item->data (DATA_KEY_IDENTIFIER).toString ();

        if (isPoint) {

          QString curveNameGot = Point::curveNameFromPointIdentifier (identifier);
          showThis = (curveNameWanted == curveNameGot);

        } else {

          showThis = (curveNameWanted == identifier);

        }
      }

      item->setVisible (showThis);

    }
  }
}

void GraphicsScene::updateAfterCommand (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateAfterCommand";

  updateCurves (cmdMediator);

  // Update the points
  updatePointMembership (cmdMediator);
}

void GraphicsScene::updateCurves (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateCurves";

  // Desired curve names include both axes and graph curve names
  QStringList curveNames;
  curveNames << AXIS_CURVE_NAME;
  curveNames << cmdMediator.document().curvesGraphsNames();

  m_graphicsLinesForCurves.addRemoveCurves (*this,
                                            curveNames);
}

void GraphicsScene::updateCurveStyles (const CurveStyles &modelCurveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateCurveStyles";

  m_graphicsLinesForCurves.updateCurveStyles (modelCurveStyles);
}

void GraphicsScene::updateGraphicsLinesToMatchGraphicsPoints (const CurveStyles &curveStyles,
                                                              const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updateGraphicsLinesToMatchGraphicsPoints";

  if (transformation.transformIsDefined()) {

    // Ordinals must be updated to reflect reordering that may have resulted from dragging points
    m_graphicsLinesForCurves.updatePointOrdinalsAfterDrag (curveStyles,
                                                           transformation);

    // Recompute the lines one time for efficiency
    m_graphicsLinesForCurves.updateGraphicsLinesToMatchGraphicsPoints (curveStyles);
  }
}

void GraphicsScene::updatePointMembership (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::updatePointMembership";

  CallbackSceneUpdateAfterCommand ftor (m_graphicsLinesForCurves,
                                        *this,
                                        cmdMediator.document ());
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackSceneUpdateAfterCommand::callback);

  // First pass:
  // 1) Mark all points as Not Wanted (this is done while creating the map)
  m_graphicsLinesForCurves.lineMembershipReset ();

  // Next pass:
  // 1) Existing points that are found in the map are marked as Wanted
  // 2) Add new points that were just created in the Document. The new points are marked as Wanted
  cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);
  cmdMediator.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  // Next pass:
  // 1) Remove points that were just removed from the Document
  m_graphicsLinesForCurves.lineMembershipPurge (cmdMediator.document().modelCurveStyles());
}
