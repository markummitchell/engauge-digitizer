/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackScaleBar.h"
#include "CmdEditPointAxis.h"
#include "CmdEditPointGraph.h"
#include "CmdMediator.h"
#include "CmdMoveBy.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateSelect.h"
#include "DlgEditPointAxis.h"
#include "DlgEditPointGraph.h"
#include "DlgEditScale.h"
#include "EngaugeAssert.h"
#include "GraphicsItemsExtractor.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCursor>
#include <QGraphicsItem>
#include <QImage>
#include <QMessageBox>
#include <QObject>
#include <QSize>
#include <QtToString.h>
#include "Transformation.h"
#include "Version.h"

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

void DigitizeStateSelect::addHoverHighlighting()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::addHoverHighlighting";

  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT ||
        item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_GUIDELINE) {
       item->setAcceptHoverEvents(true);
    }
  }
}

void DigitizeStateSelect::begin (CmdMediator *cmdMediator,
                                 DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::RubberBandDrag);

  addHoverHighlighting();
  context().mainWindow().handleGuidelinesActiveChange (true);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

bool DigitizeStateSelect::canPaste (const Transformation & /* transformation */,
                                    const QSize & /* viewSize */) const
{
  return false;
}

QCursor DigitizeStateSelect::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateSelect::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::end";

  removeHoverHighlighting();
}

void DigitizeStateSelect::handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                                      const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();

  if (cmdMediator->document().documentAxesPointsRequired() == DOCUMENT_AXES_POINTS_REQUIRED_2) {
    handleContextMenuEventAxis2 (cmdMediator);
  } else {
    handleContextMenuEventAxis34 (cmdMediator,
                                  pointIdentifier);
  }
}

void DigitizeStateSelect::handleContextMenuEventAxis2 (CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::handleContextMenuEventAxis2";

  const bool IS_NOT_X_ONLY = false;

  // The point identifier we want is not necessarily the one edited but is the one with the
  // nonzero x or y (but not both) coordinate
  QString pointIdentifier = scaleBarPointIdentifier (cmdMediator);

  QPointF posScreen = cmdMediator->document().positionScreen (pointIdentifier);
  QPointF posGraphBefore = cmdMediator->document().positionGraph (pointIdentifier);

  // Ask user for scale length
  double scaleLength = scaleBarLength (cmdMediator);
  DlgEditScale *dlg = new DlgEditScale (context().mainWindow(),
                                        cmdMediator->document().modelCoords(),
                                        cmdMediator->document().modelGeneral(),
                                        context().mainWindow().modelMainWindow(),
                                        &scaleLength);
  int rtn = dlg->exec ();

  scaleLength = dlg->scaleLength (); // This call returns new value for scale length
  delete dlg;

  if (rtn == QDialog::Accepted) {

    // User wants to edit the scale length, which is effectively editing this axis point, but let's perform sanity checks first

    bool isError;
    QString errorMessage;

    bool isXNonzero = (qAbs (posGraphBefore.x()) > 0); // Identify which coordinate is to be edited
    QPointF posGraphAfter (isXNonzero ? scaleLength : 0,
                           isXNonzero ? 0 : scaleLength);
    context().mainWindow().cmdMediator()->document().checkEditPointAxis(pointIdentifier,
                                                                        posScreen,
                                                                        posGraphAfter,
                                                                        isError,
                                                                        errorMessage);

    if (isError) {

      QMessageBox::warning (nullptr,
                            engaugeWindowTitle(),
                            errorMessage);

    } else {

      // Create a command to change the scale length
      CmdEditPointAxis *cmd = new CmdEditPointAxis (context().mainWindow(),
                                                    cmdMediator->document(),
                                                    pointIdentifier,
                                                    posGraphBefore,
                                                    posGraphAfter,
                                                    IS_NOT_X_ONLY);
      context().appendNewCmd(cmdMediator,
                             cmd);
    }
  }
}

void DigitizeStateSelect::handleContextMenuEventAxis34 (CmdMediator *cmdMediator,
                                                        const QString &pointIdentifier)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateSelect::handleContextMenuEventAxis34";

  QPointF posScreen = cmdMediator->document().positionScreen (pointIdentifier);
  QPointF posGraphBefore = cmdMediator->document().positionGraph (pointIdentifier);
  bool isXOnly = cmdMediator->document().isXOnly (pointIdentifier);

  // Ask user for coordinates
  double x = posGraphBefore.x();
  double y = posGraphBefore.y();

  DlgEditPointAxis *dlg = new DlgEditPointAxis (context().mainWindow(),
                                                cmdMediator->document().modelCoords(),
                                                cmdMediator->document().modelGeneral(),
                                                context().mainWindow().modelMainWindow(),
                                                context().mainWindow().transformation(),
                                                cmdMediator->document().documentAxesPointsRequired(),
                                                isXOnly,
                                                &x,
                                                &y);
  int rtn = dlg->exec ();

  QPointF posGraphAfter = dlg->posGraph (isXOnly); // This call returns new values for isXOnly and the graph position
  delete dlg;

  if (rtn == QDialog::Accepted) {

    // User wants to edit this axis point, but let's perform sanity checks first

    bool isError;
    QString errorMessage;

    context().mainWindow().cmdMediator()->document().checkEditPointAxis(pointIdentifier,
                                                                        posScreen,
                                                                        posGraphAfter,
                                                                        isError,
                                                                        errorMessage);

    if (isError) {

      QMessageBox::warning (nullptr,
                            engaugeWindowTitle(),
                            errorMessage);

    } else {

      // Create a command to edit the point
      CmdEditPointAxis *cmd = new CmdEditPointAxis (context().mainWindow(),
                                                    cmdMediator->document(),
                                                    pointIdentifier,
                                                    posGraphBefore,
                                                    posGraphAfter,
                                                    isXOnly);
      context().appendNewCmd(cmdMediator,
                             cmd);
    }
  }
}

void DigitizeStateSelect::handleContextMenuEventGraph (CmdMediator *cmdMediator,
                                                       const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();

  // Editing graph coordinates before the axes are defined is not useful because:
  // 1) That functionality is for fine tuning point placement based on defined axes
  // 2) The transformation from screen to graph coordinates below will crash
  if (context().mainWindow().transformation().transformIsDefined()) {

    double *x = nullptr, *y = nullptr;

    if (pointIdentifiers.count() == 1) {

      // There is exactly one point so pass its coordinates to the dialog
      x = new double;
      y = new double;

      QPointF posScreenBefore = cmdMediator->document().positionScreen (pointIdentifiers.first());
      QPointF posGraphBefore;
      context().mainWindow().transformation().transformScreenToRawGraph (posScreenBefore,
                                                                         posGraphBefore);

      // Ask user for coordinates
      *x = posGraphBefore.x();
      *y = posGraphBefore.y();
    }

    DlgEditPointGraph *dlg = new DlgEditPointGraph (context().mainWindow(),
                                                    cmdMediator->document().modelCoords(),
                                                    cmdMediator->document().modelGeneral(),
                                                    context().mainWindow().modelMainWindow(),
                                                    context().mainWindow().transformation(),
                                                    x,
                                                    y);
    delete x;
    delete y;

    x = nullptr;
    y = nullptr;

    int rtn = dlg->exec ();

    bool isXGiven, isYGiven;
    double xGiven, yGiven;
    dlg->posGraph (isXGiven, xGiven, isYGiven, yGiven); // One or both coordinates are returned
    delete dlg;

    if (rtn == QDialog::Accepted) {

      // Create a command to edit the point
      CmdEditPointGraph *cmd = new CmdEditPointGraph (context().mainWindow(),
                                                      cmdMediator->document(),
                                                      pointIdentifiers,
                                                      isXGiven,
                                                      isYGiven,
                                                      xGiven,
                                                      yGiven);
      context().appendNewCmd(cmdMediator,
                             cmd);
    }
  }
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
        qAbs (deltaScreen.x ()) > 0 ||
        qAbs (deltaScreen.y ()) > 0)) {

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

    showCoordinatesIfSinglePointIsSelected ();
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
  GraphicsItemsExtractor graphicsItemsExtractor;
  const QList<QGraphicsItem*> &items  = context().mainWindow().scene ().selectedItems();
  CmdMoveBy *cmd = new CmdMoveBy (context().mainWindow(),
                                  cmdMediator->document(),
                                  deltaScreen,
                                  moveText,
                                  graphicsItemsExtractor.selectedPointIdentifiers (items));
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

void DigitizeStateSelect::removeHoverHighlighting()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::removeHoverHighlighting";

  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT ||
        item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_GUIDELINE) {
       item->setAcceptHoverEvents(false);
    }
  }
}

double DigitizeStateSelect::scaleBarLength (CmdMediator *cmdMediator) const
{
  CallbackScaleBar ftor;

  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackScaleBar::callback);
  cmdMediator->iterateThroughCurvePointsAxes (ftorWithCallback);

  return ftor.scaleBarLength ();
}

QString DigitizeStateSelect::scaleBarPointIdentifier (CmdMediator *cmdMediator) const
{
  CallbackScaleBar ftor;

  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackScaleBar::callback);
  cmdMediator->iterateThroughCurvePointsAxes (ftorWithCallback);

  return ftor.scaleBarPointIdentifier();
}

void DigitizeStateSelect::setHoverHighlighting(const MainWindowModel &modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::addHoverHighlighting";

  // Set the opacity for all points. It should be already set for pre-existing points
  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT) {
       item->setOpacity (modelMainWindow.highlightOpacity());
    }
  }
}

void DigitizeStateSelect::showCoordinatesIfSinglePointIsSelected ()
{
  // See if there is a single point selected
  QList<QGraphicsItem*> items = context().mainWindow().scene().selectedItems();
  if (items.size () == 1) {

    // There is a single item selected but we must see if it is a point
    QGraphicsItem *item = * (items.begin ());

    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_POINT) {

      // Show the coordinates of the point in the status bar
      QString coordsScreen, coordsGraph, resolutionGraph;
      context().mainWindow().transformation().coordTextForStatusBar (item->pos(),
                                              coordsScreen,
                                              coordsGraph,
                                              resolutionGraph,
                                              context().mainWindow().modeMap());

      context().mainWindow().showTemporaryMessage(coordsGraph);
    }
  }
}

QString DigitizeStateSelect::state() const
{
  return "DigitizeStateSelect";
}

void DigitizeStateSelect::updateAfterPointAddition ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateSelect::updateAfterPointAddition";

  addHoverHighlighting ();
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
