#include "CmdMediator.h"
#include "CmdMoveBy.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateSelect.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QImage>
#include <QtToString.h>

const QString MOVE_TEXT_DOWN ("Move down");
const QString MOVE_TEXT_LEFT ("Move left");
const QString MOVE_TEXT_RIGHT ("Move right");
const QString MOVE_TEXT_UP ("Move up");

DigitizeStateSelect::DigitizeStateSelect (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateSelect::~DigitizeStateSelect ()
{
}

void DigitizeStateSelect::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::begin";

  setCursor();
  context().setDragMode(QGraphicsView::RubberBandDrag);

  setCursorForPoints ();
}

QCursor DigitizeStateSelect::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateSelect::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::end";

  unsetCursorForPoints ();
}

void DigitizeStateSelect::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();

  if (key == Qt::Key_Down ||
      key == Qt::Key_Up ||
      key == Qt::Key_Left ||
      key == Qt::Key_Right) {

    keyPressArrow (key);

  }
}

void DigitizeStateSelect::handleMousePress (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleMousePress"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ();

  // Note that GraphicsView has already called GraphicsPointAbstract::resetPositionHasChanged on all items

  m_movingStart = posScreen;
}

void DigitizeStateSelect::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleMouseRelease"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ();

  QPointF deltaScreen = posScreen - m_movingStart;
  QStringList positionHasChangedIdentifers = context().mainWindow().scene().positionHasChangedPointIdentifiers();

  bool positionHasChanged = (positionHasChangedIdentifers.count () > 0);

  if (positionHasChanged && (
        deltaScreen.x () != 0 ||
        deltaScreen.y () != 0)) {

    QString moveText = moveTextFromDeltaScreen (deltaScreen);

    CmdMoveBy *cmd = new CmdMoveBy (context().mainWindow(),
                                    context().cmdMediator().document(),
                                    deltaScreen,
                                    moveText,
                                    positionHasChangedIdentifers);
    context().appendNewCmd (cmd);

   } else {

    // Selection probably changed so update the MainWindow controls (especially Cut)
    context().mainWindow().updateAfterMouseRelease();

  }
}

void DigitizeStateSelect::keyPressArrow (Qt::Key key)
{
  QPointF deltaScreen;
  QString moveText;
  switch (key) {
    case Qt::Key_Down:
      deltaScreen = QPointF (0, zoomedToUnzoomedScreenY ());
      moveText = MOVE_TEXT_DOWN;
      break;

    case Qt::Key_Left:
      deltaScreen = QPointF (-1 * zoomedToUnzoomedScreenX (), 0);
      moveText = MOVE_TEXT_LEFT;
      break;

    case Qt::Key_Right:
      deltaScreen = QPointF (zoomedToUnzoomedScreenX (), 0);
      moveText = MOVE_TEXT_RIGHT;
      break;

    case Qt::Key_Up:
      deltaScreen = QPointF (0, -1 * zoomedToUnzoomedScreenY ());
      moveText = MOVE_TEXT_UP;
      break;

    default:
      Q_ASSERT (false);
  }

  CmdMoveBy *cmd = new CmdMoveBy (context().mainWindow(),
                                  context().cmdMediator ().document(),
                                  deltaScreen,
                                  moveText,
                                  context().mainWindow().scene ().selectedPointIdentifiers ());
  context().appendNewCmd (cmd);
}

QString DigitizeStateSelect::moveTextFromDeltaScreen (const QPointF &deltaScreen)
{
  QString moveText;

  //     x  UP   x        -----> +x
  //       x   x          |
  // LEFT    x   RIGHT    |
  //       x   x          v
  //     x  DOWN x       +y
  bool downOrRight  = (deltaScreen.y () > -1.0 * deltaScreen.x ());
  bool upOrRight = (deltaScreen.y () < deltaScreen.x ());
  if (downOrRight && upOrRight) {
    moveText = MOVE_TEXT_RIGHT;
  } else if (downOrRight && !upOrRight) {
    moveText = MOVE_TEXT_DOWN;
  } else if (!downOrRight && upOrRight) {
    moveText = MOVE_TEXT_UP;
  } else {
    moveText = MOVE_TEXT_LEFT;
  }

  return moveText;
}

void DigitizeStateSelect::setCursorForPoints()
{
  QCursor cursor (Qt::OpenHandCursor);

  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT) {
      item->setCursor (cursor);
    }
  }
}

void DigitizeStateSelect::unsetCursorForPoints()
{
  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT) {
      item->unsetCursor ();
    }
  }
}

double DigitizeStateSelect::zoomedToUnzoomedScreenX () const
{
  double m11 = context().mainWindow ().view ().transform().m11 ();
  return 1.0 / m11;
}

double DigitizeStateSelect::zoomedToUnzoomedScreenY () const
{
  double m22 = context().mainWindow ().view ().transform().m22 ();
  return 1.0 / m22;
}
