/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdMoveBy.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateSelect.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QGraphicsItem>
#include <QImage>
#include <QObject>
#include <QtToString.h>

const QString MOVE_TEXT_DOWN (QObject::tr ("Move down"));
const QString MOVE_TEXT_LEFT (QObject::tr ("Move left"));
const QString MOVE_TEXT_RIGHT (QObject::tr ("Move right"));
const QString MOVE_TEXT_UP (QObject::tr ("Move up"));

DigitizeStateSelect::DigitizeStateSelect (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateSelect::~DigitizeStateSelect ()
{
}

QString DigitizeStateSelect::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateSelect::begin (CmdMediator *cmdMediator,
                                 DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::RubberBandDrag);

  setCursorForPoints ();
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateSelect::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateSelect::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::end";

  unsetCursorForPoints ();
}

void DigitizeStateSelect::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleCurveChange";
}

void DigitizeStateSelect::handleKeyPress (CmdMediator *cmdMediator,
                                          Qt::Key key,
                                          bool atLeastOneSelectedItem)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();

  if (atLeastOneSelectedItem) {

    if (key == Qt::Key_Down ||
      key == Qt::Key_Up ||
      key == Qt::Key_Left ||
      key == Qt::Key_Right) {

      keyPressArrow (cmdMediator,
                     key);

    }
  }
}

void DigitizeStateSelect::handleMouseMove (CmdMediator * /* cmdMediator */,
                                           QPointF /* posScreen */)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::handleMouseMove";
}

void DigitizeStateSelect::handleMousePress (CmdMediator * /* cmdMediator */,
                                            QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleMousePress"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ();

  // Note that GraphicsView has already called GraphicsPointAbstract::resetPositionHasChanged on all items

  m_movingStart = posScreen;
}

void DigitizeStateSelect::handleMouseRelease (CmdMediator *cmdMediator,
                                              QPointF posScreen)
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

    // Create command to move points
    CmdMoveBy *cmd = new CmdMoveBy (context().mainWindow(),
                                    cmdMediator->document(),
                                    deltaScreen,
                                    moveText,
                                    positionHasChangedIdentifers);
    context().appendNewCmd (cmdMediator,
                            cmd);

   } else {

    // Selection probably changed so update the MainWindow controls (especially Cut)
    context().mainWindow().updateAfterMouseRelease();

  }
}

void DigitizeStateSelect::keyPressArrow (CmdMediator *cmdMediator,
                                         Qt::Key key)
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
      ENGAUGE_ASSERT (false);
  }

  // Create command to move points
  CmdMoveBy *cmd = new CmdMoveBy (context().mainWindow(),
                                  cmdMediator->document(),
                                  deltaScreen,
                                  moveText,
                                  context().mainWindow().scene ().selectedPointIdentifiers ());
  context().appendNewCmd (cmdMediator,
                          cmd);
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

QString DigitizeStateSelect::state() const
{
  return "DigitizeStateSelect";
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

void DigitizeStateSelect::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                    const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::updateModelDigitizeCurve";
}

void DigitizeStateSelect::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::updateModelSegments";
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
