/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedePair.h"
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
  m_centipedePair (nullptr)
{
}

DigitizeStateGuideline::~DigitizeStateGuideline ()
{
  delete m_centipedePair;  
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
  lockNonGuidelines (true);
}

bool DigitizeStateGuideline::canPaste (const Transformation & /* transformation */,
                                       const QSize & /* viewSize */) const
{
  return false;
}

QCursor DigitizeStateGuideline::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateGuideline::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStateGuideline::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::end";

  killCentipede();
  lockNonGuidelines (false);
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
                                             Qt::Key /* key */,
                                             bool /* atLeastOneSelectedItem */)
{
  // Only keys forwarded by GraphicsView::keyPressEvent  will get here. Originally this only
  // killed the centipedes when Qt::Key_Escape was encountered, but other cases like Control-Z
  // which requires the key AND the modifier) justified stopping for any keypress. Too confusing
  // to undo the last CmdAbstract while leaving the partially completed guideline
  killCentipede ();
}

void DigitizeStateGuideline::handleMouseMove (CmdMediator *cmdMediator,
                                              QPointF posScreen)
{
  if (m_centipedePair) {
    if (m_centipedePair->done (posScreen)) {

      // Done so make a command and remove CentipedePair
      bool selectedXT = m_centipedePair->selectedXTFinal ();
      double selectedValue = m_centipedePair->valueFinal ();
      killCentipede ();

      // Create command
      CmdAbstract *cmd = nullptr;
      if (selectedXT) {
        cmd = new CmdGuidelineAddXT (context().mainWindow(),
                                     cmdMediator->document(),
                                     selectedValue);
      } else {
        cmd = new CmdGuidelineAddYR (context().mainWindow(),
                                     cmdMediator->document(),
                                     selectedValue);
      }

      context().appendNewCmd (cmdMediator,
                              cmd);

    } else {

      m_centipedePair->move (posScreen);
    }
  }
}

void DigitizeStateGuideline::handleMousePress (CmdMediator *cmdMediator,
                                               QPointF posScreen)
{
  killCentipede(); // Remove previous instance if there is one so it does not get orphaned

  m_centipedePair = new CentipedePair (context().mainWindow().scene(),
                                       context().mainWindow().transformation(),
                                       cmdMediator->document().modelGuideline(),
                                       cmdMediator->document().modelCoords(),
                                       posScreen);
}

void DigitizeStateGuideline::handleMouseRelease (CmdMediator * /* cmdMediator */,
                                                 QPointF /* posScreen */)
{
}

void DigitizeStateGuideline::killCentipede ()
{
  if (m_centipedePair) {
    delete m_centipedePair;
    m_centipedePair = nullptr;
  }
}

void DigitizeStateGuideline::lockNonGuidelines (bool lockdown)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::lockNonGuidelines";

  QList<QGraphicsItem*> items = context().mainWindow().scene().items();
  QList<QGraphicsItem*>::iterator itr;
  for (itr = items.begin (); itr != items.end (); itr++) {

    QGraphicsItem *item = *itr;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE) != GRAPHICS_ITEM_TYPE_GUIDELINE) {
       item->setFlag (QGraphicsItem::ItemIsSelectable, !lockdown);
       item->setFlag (QGraphicsItem::ItemIsMovable, !lockdown);
    }
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
