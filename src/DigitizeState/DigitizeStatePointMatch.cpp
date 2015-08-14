#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "DigitizeStateContext.h"
#include "DigitizeStatePointMatch.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "OrdinalGenerator.h"
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QImage>
#include <QPen>

DigitizeStatePointMatch::DigitizeStatePointMatch (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context),
  m_outline (0)
{
}

DigitizeStatePointMatch::~DigitizeStatePointMatch ()
{
}

QString DigitizeStatePointMatch::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStatePointMatch::begin (DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::begin";

  const double Z_VALUE = 200.0;

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());

  const DocumentModelPointMatch &modelPointMatch = context().cmdMediator().document().modelPointMatch();

  // Add outline that will move with the cursor
  m_outline = new QGraphicsEllipseItem ();
  context().mainWindow().scene().addItem (m_outline);
  m_outline->setPen (QPen (ColorPaletteToQColor (modelPointMatch.paletteColorCandidate())));
  m_outline->setVisible (false);
  m_outline->setZValue (Z_VALUE);
}

QCursor DigitizeStatePointMatch::cursor() const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStatePointMatch::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::end";

  // Remove outline before leaving state
  ENGAUGE_CHECK_PTR (m_outline);
  context().mainWindow().scene().removeItem (m_outline);
  m_outline = 0;
}

void DigitizeStatePointMatch::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleCurveChange";
}

void DigitizeStatePointMatch::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStatePointMatch::handleMouseMove (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseMove";

  const int SIZE = 20;

  bool pixelIsOn = true; // TODO fix this to use filtered image
  if (pixelIsOn) {
    m_outline->setRect (posScreen.x() - SIZE / 2.0,
                        posScreen.y() - SIZE / 2.0,
                        SIZE,
                        SIZE);
    if (!m_outline->isVisible ()) {
      m_outline->setVisible (true);
    }
  } else {
    m_outline->setVisible (false);
  }
}

void DigitizeStatePointMatch::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMousePress";
}

void DigitizeStatePointMatch::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseRelease";

//  // Create command to add point
//  OrdinalGenerator ordinalGenerator;
//  Document &document = context ().cmdMediator ().document ();
//  const Transformation &transformation = context ().mainWindow ().transformation();
//  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
//                                            document,
//                                            context ().mainWindow().selectedGraphCurve(),
//                                            posScreen,
//                                            ordinalGenerator.generateCurvePointOrdinal(document,
//                                                                                       transformation,
//                                                                                       posScreen,
//                                                                                       activeCurve ()));
//  context().appendNewCmd(cmd);
}

QString DigitizeStatePointMatch::state() const
{
  return "DigitizeStatePointMatch";
}
