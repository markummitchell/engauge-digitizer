/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeStateContext.h"
#include "CmdGuidelineAddXT.h"
#include "CmdGuidelineAddYR.h"
#include "CmdGuidelineMoveXT.h"
#include "CmdGuidelineMoveYR.h"
#include "CmdMediator.h"
#include "ColorFilter.h"
#include "CurveStyles.h"
#include "DataKey.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateGuideline.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QImage>
#include <qmath.h>
#include <QMessageBox>
#include <QPen>
#include <QSize>
#include "Transformation.h"

DigitizeStateGuideline::DigitizeStateGuideline (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context),
  m_context (new CentipedeStateContext (*this))
{
}

DigitizeStateGuideline::~DigitizeStateGuideline ()
{
  delete m_context;
}

QString DigitizeStateGuideline::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateGuideline::begin (CmdMediator *cmdMediator,
                                    DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::beginn";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  setGraphicsItemsFlags ();
}

bool DigitizeStateGuideline::canPaste (const Transformation & /* transformation */,
                                       const QSize & /* viewSize */) const
{
  return false;
}

void DigitizeStateGuideline::createGuidelineCommand (bool selectedXT,
                                                     double valueSelected)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateGuideline::createGuidelineCommand";

  CmdAbstract *cmd = nullptr;
  if (selectedXT) {
    cmd = new CmdGuidelineAddXT (context().mainWindow(),
                                 context().mainWindow().cmdMediator()->document(),
                                 valueSelected);
  } else {
    cmd = new CmdGuidelineAddYR (context().mainWindow(),
                                 context().mainWindow().cmdMediator()->document(),
                                 valueSelected);
  }

  context().appendNewCmd (context().mainWindow().cmdMediator(),
                          cmd);
}

QCursor DigitizeStateGuideline::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateGuideline::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateGuideline::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::end";
}

bool DigitizeStateGuideline::guidelinesAreSelectable () const
{
  return false;
}

void DigitizeStateGuideline::handleContextMenuEventAxis (CmdMediator * /* cmdMediator */,
                                                          const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();
}

void DigitizeStateGuideline::handleContextMenuEventGraph (CmdMediator * /* cmdMediator */,
                                                           const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline ::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();
}

void DigitizeStateGuideline::handleCurveChange(CmdMediator * /* cmdMediator */)
{
}

void DigitizeStateGuideline::handleKeyPress (CmdMediator * /* cmdMediator */,
                                             Qt::Key key,
                                             bool atLeastOneSelectedItem)
{
  m_context->handleKeyPress (key,
                             atLeastOneSelectedItem);
}

void DigitizeStateGuideline::handleMouseMove (CmdMediator * /* cmdMediator */,
                                              QPointF posScreen)
{
  m_context->handleMouseMove (posScreen);
}

void DigitizeStateGuideline::handleMousePress (CmdMediator *cmdMediator,
                                               QPointF posScreen)
{
  m_context->handleMousePress (&context().mainWindow ().scene (),
                               context().mainWindow ().transformation (),
                               cmdMediator->document ().modelGuideline (),
                               cmdMediator->document ().modelCoords (),
                               posScreen,
                               hitTestForGraphics (posScreen));
}

void DigitizeStateGuideline::handleMouseRelease (CmdMediator * /* cmdMediator */,
                                                 QPointF posScreen)
{
  m_context->handleMouseRelease (posScreen);
}

bool DigitizeStateGuideline::hitTestForGraphics (const QPointF &posScreen)
{
  // Create temporary graphics item representing click
  QGraphicsItem *itemClick = new QGraphicsRectItem (QRectF (posScreen - QPointF (2, 2),
                                                            posScreen + QPointF (2, 2)));
  itemClick->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);
  context().mainWindow().scene().addItem (itemClick);

  // Iterate through existing graphics items

  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;

  bool gotHit = false;

  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;

    // Object has to be a Guideline, visible, selectable and overlapping with itemClick to be applicable
    bool isGuideline = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) == GRAPHICS_ITEM_TYPE_GUIDELINE);
    bool isVisible = item->isVisible();
    bool isCollision = item->collidesWithItem (itemClick);
    if (isGuideline && isVisible && isCollision) {
      gotHit = true;
      break;
    }
  }

  // Remove temporary graphics item
  context().mainWindow().scene().removeItem (itemClick);
  delete itemClick;

  return gotHit;
}

void DigitizeStateGuideline::setGraphicsItemFlags (QGraphicsItem *item) const
{
  GraphicsItemType type = static_cast<GraphicsItemType> (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt());
  if (type == GRAPHICS_ITEM_TYPE_GUIDELINE) {
    item->setEnabled (true);
    item->setFlag (QGraphicsItem::ItemIsMovable, true);
    item->setVisible (true); // Overrides View menu setting so user can see the guidelines
  } else {
    item->setEnabled (false);
    item->setFlag (QGraphicsItem::ItemIsMovable, false);
    // Visibility of non-Guidelines is left unchanged
  }
}

QString DigitizeStateGuideline::state() const
{
  return "DigitizeStateGuideline";
}

void DigitizeStateGuideline::updateAfterPointAddition()
{
}

void DigitizeStateGuideline::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                       const DocumentModelDigitizeCurve & /* curve */)
{
}

void DigitizeStateGuideline::updateModelSegments (const DocumentModelSegments & /* modelSegments */)
{
}
