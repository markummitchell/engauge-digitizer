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
#include "DigitizeStateContext.h"
#include "DigitizeStateGuideline.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCursor>
#include <QGraphicsEllipseItem>
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
}

QString DigitizeStateGuideline::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateGuideline::begin (CmdMediator * /* cmdMediator */,
                                    DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateGuideline::beginn";
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
                                             bool /* atLeastOneSelectedItem */)
{
  if (key == Qt::Key_Escape && m_centipedePair) {
    killCentipede ();
  }
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
  m_centipedePair = new CentipedePair (context().mainWindow().scene(),
                                       context().mainWindow().transformation(),
                                       cmdMediator->document().modelGuideline(),
                                       posScreen);
}

void DigitizeStateGuideline::handleMouseRelease (CmdMediator * /* cmdMediator */,
                                                 QPointF /* posScreen */)
{
}

void DigitizeStateGuideline::killCentipede ()
{
  delete m_centipedePair;
  m_centipedePair = nullptr;
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
