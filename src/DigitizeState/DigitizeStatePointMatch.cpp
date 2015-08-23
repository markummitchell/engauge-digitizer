#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "ColorFilter.h"
#include "DigitizeStateContext.h"
#include "DigitizeStatePointMatch.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "OrdinalGenerator.h"
#include "PointMatchAlgorithm.h"
#include "PointStyle.h"
#include <QCursor>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QImage>
#include <qmath.h>
#include <QPen>

const double Z_VALUE = 200.0;

DigitizeStatePointMatch::DigitizeStatePointMatch (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context),
  m_outline (0),
  m_candidatePoint (0)
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

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());

  // Add outline that will move with the cursor
  m_outline = new QGraphicsEllipseItem ();
  context().mainWindow().scene().addItem (m_outline);
  m_outline->setPen (QPen (Qt::black));
  m_outline->setVisible (true);
  m_outline->setZValue (Z_VALUE);
}

void DigitizeStatePointMatch::createPermanentPoint (const QPointF &posScreen)
{
  // Create command to add point
  OrdinalGenerator ordinalGenerator;
  Document &document = context ().cmdMediator ().document ();
  const Transformation &transformation = context ().mainWindow ().transformation();
  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
                                            document,
                                            context ().mainWindow().selectedGraphCurve(),
                                            posScreen,
                                            ordinalGenerator.generateCurvePointOrdinal(document,
                                                                                       transformation,
                                                                                       posScreen,
                                                                                       activeCurve ()));
  context().appendNewCmd(cmd);

}

void DigitizeStatePointMatch::createTemporaryPoint (const QPoint &posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::createTemporaryPoint";

  // Temporary point that user can see while DlgEditPoint is active
  const Curve &curveAxes = context().cmdMediator().curveAxes();
  PointStyle pointStyleAxes = curveAxes.curveStyle().pointStyle();
  GraphicsPoint *point = context().mainWindow().scene().createPoint(Point::temporaryPointIdentifier (),
                                                                    pointStyleAxes,
                                                                    posScreen);

  context().mainWindow().scene().addTemporaryPoint (Point::temporaryPointIdentifier(),
                                                    point);
  m_posCandidatePoint = posScreen;
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

QList<QPoint> DigitizeStatePointMatch::extractSamplePointPixels (const QImage &img,
                                                                 const DocumentModelPointMatch &modelPointMatch,
                                                                 const QPointF &posScreen) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::extractSamplePointPixels";

  QList<QPoint> samplePointPixels;

  ColorFilter colorFilter;
  for (int xOffset = 0; xOffset < modelPointMatch.maxPointSize(); xOffset++) {
    for (int yOffset = 0; yOffset < modelPointMatch.maxPointSize(); yOffset++) {

      int x = posScreen.x() + xOffset;
      int y = posScreen.y() + yOffset;
      bool pixelIsOn = colorFilter.pixelFilteredIsOn (img,
                                                      x,
                                                      y);

      if (pixelIsOn) {

        samplePointPixels.push_back (QPoint (xOffset,
                                             yOffset));
      }
    }
  }

  return samplePointPixels;
}

void DigitizeStatePointMatch::handleCurveChange()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleCurveChange";
}

void DigitizeStatePointMatch::handleKeyPress (Qt::Key key,
                                              bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();

  // The selected key button has to be compatible with GraphicsView::keyPressEvent
  if (key == Qt::Key_Right) {

    promoteCandidatePointToPermanentPoint (); // This removes the current temporary point

    popCandidatePoint(); // This creates a new temporary point

  }
}

void DigitizeStatePointMatch::handleMouseMove (QPointF posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseMove";

  const DocumentModelPointMatch &modelPointMatch = context().cmdMediator().document().modelPointMatch();

  m_outline->setRect (posScreen.x() - modelPointMatch.maxPointSize() / 2.0,
                      posScreen.y() - modelPointMatch.maxPointSize() / 2.0,
                      modelPointMatch.maxPointSize(),
                      modelPointMatch.maxPointSize());

  const QImage &img = context().mainWindow().imageFiltered();
  int radiusLimit = context().cmdMediator().document().modelCommon().cursorSize();
  bool pixelShouldBeOn = pixelIsOnInImage (img,
                                           posScreen.x(),
                                           posScreen.y(),
                                           radiusLimit);

  QColor penColorIs = m_outline->pen().color();
  bool pixelIsOn = (penColorIs.red () != penColorIs.green()); // Considered on if not gray scale
  if (pixelShouldBeOn != pixelIsOn) {
    QColor penColorShouldBe (pixelShouldBeOn ? Qt::green : Qt::black);
    m_outline->setPen (QPen (penColorShouldBe));
  }
}

void DigitizeStatePointMatch::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMousePress";  
}

void DigitizeStatePointMatch::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseRelease";

  createPermanentPoint (posScreen);

  findPointsAndShowFirstCandidate (posScreen);
}

void DigitizeStatePointMatch::findPointsAndShowFirstCandidate (const QPointF &posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::findPointsAndShowFirstCandidate";

  const DocumentModelPointMatch &modelPointMatch = context().cmdMediator().document().modelPointMatch();
  const QImage &img = context().mainWindow().imageFiltered();

  QList<QPoint> samplePointPixels = extractSamplePointPixels (img,
                                                              modelPointMatch,
                                                              posScreen);

  QString curveName = activeCurve();
  const Document &doc = context().cmdMediator().document();
  const Curve *curve = doc.curveForCurveName (curveName);

  PointMatchAlgorithm pointMatchAlgorithm;
  m_candidatePoints = pointMatchAlgorithm.findPoints (samplePointPixels,
                                                      img,
                                                      modelPointMatch,
                                                      curve->points());

  popCandidatePoint ();
}

bool DigitizeStatePointMatch::pixelIsOnInImage (const QImage &img,
                                                int x,
                                                int y,
                                                int radiusLimit) const
{
  ColorFilter filter;

  // Examine all nearby pixels
  bool pixelShouldBeOn = false;
  for (int xOffset = -radiusLimit; xOffset <= radiusLimit; xOffset++) {
    for (int yOffset = -radiusLimit; yOffset <= radiusLimit; yOffset++) {

      int radius = qSqrt (xOffset * xOffset + yOffset * yOffset);

      if (radius <= radiusLimit) {

        int xNearby = x + xOffset;
        int yNearby = y + yOffset;

        if ((0 <= xNearby) &&
            (0 <= yNearby) &&
            (xNearby < img.width()) &&
            (yNearby < img.height())) {

          if (filter.pixelFilteredIsOn (img,
                                        xNearby,
                                        yNearby)) {

            pixelShouldBeOn = true;
            break;
          }
        }
      }
    }
  }

  return pixelShouldBeOn;
}

void DigitizeStatePointMatch::popCandidatePoint ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::popCandidatePoint";

  // Pop next point from list onto screen
  QPoint posScreen = m_candidatePoints.first();
  m_candidatePoints.pop_front ();

  createTemporaryPoint(posScreen);
}

void DigitizeStatePointMatch::promoteCandidatePointToPermanentPoint()
{
  createPermanentPoint (m_posCandidatePoint);

  // Remove temporary point. This is required if there already is a temporary point, before creating a new temporary point
//  context().mainWindow().scene().removePoint (Point::temporaryPointIdentifier ());
}

QString DigitizeStatePointMatch::state() const
{
  return "DigitizeStatePointMatch";
}
