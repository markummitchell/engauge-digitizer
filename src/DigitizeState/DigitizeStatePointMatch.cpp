/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAddPointGraph.h"
#include "CmdMediator.h"
#include "ColorFilter.h"
#include "CurveStyles.h"
#include "DigitizeStateContext.h"
#include "DigitizeStatePointMatch.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsPoint.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "OrdinalGenerator.h"
#include "PointMatchAlgorithm.h"
#include "PointStyle.h"
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

const double Z_VALUE = 200.0;

DigitizeStatePointMatch::DigitizeStatePointMatch (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context),
  m_outline (nullptr),
  m_candidatePoint (nullptr)
{
}

DigitizeStatePointMatch::~DigitizeStatePointMatch ()
{
}

QString DigitizeStatePointMatch::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStatePointMatch::begin (CmdMediator *cmdMediator,
                                     DigitizeState /* previousState */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::begin";

  setCursor(cmdMediator);
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());

  // Add outline that will move with the cursor
  m_outline = new QGraphicsEllipseItem ();
  context().mainWindow().scene().addItem (m_outline);
  m_outline->setPen (QPen (Qt::black));
  m_outline->setVisible (true);
  m_outline->setZValue (Z_VALUE);
}

bool DigitizeStatePointMatch::canPaste (const Transformation &transformation,
                                        const QSize &viewSize) const
{
  return canPasteProtected (transformation,
                            viewSize);
}

void DigitizeStatePointMatch::createPermanentPoint (CmdMediator *cmdMediator,
                                                    const QPointF &posScreen)
{
  // Create command to add point
  OrdinalGenerator ordinalGenerator;
  Document &document = cmdMediator->document ();
  const Transformation &transformation = context ().mainWindow ().transformation();
  QUndoCommand *cmd = new CmdAddPointGraph (context ().mainWindow(),
                                            document,
                                            context ().mainWindow().selectedGraphCurve(),
                                            posScreen,
                                            ordinalGenerator.generateCurvePointOrdinal(document,
                                                                                       transformation,
                                                                                       posScreen,
                                                                                       activeCurve ()));
  context().appendNewCmd(cmdMediator,
                         cmd);

}

void DigitizeStatePointMatch::createTemporaryPoint (CmdMediator *cmdMediator,
                                                    const QPoint &posScreen)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::createTemporaryPoint";

  GeometryWindow *NULL_GEOMETRY_WINDOW = nullptr;

  const DocumentModelPointMatch &modelPointMatch = cmdMediator->document().modelPointMatch();

  // Get point style for current graph, and then override with candidate color
  const CurveStyles &curveStyles = cmdMediator->document().modelCurveStyles();
  PointStyle pointStyle = curveStyles.pointStyle (activeCurve());
  pointStyle.setPaletteColor (modelPointMatch.paletteColorCandidate());

  // Temporary point that user can see while DlgEditPoint is active
  GraphicsPoint *point = context().mainWindow().scene().createPoint(Point::temporaryPointIdentifier (),
                                                                    pointStyle,
                                                                    posScreen,
                                                                    NULL_GEOMETRY_WINDOW);

  context().mainWindow().scene().removeTemporaryPointIfExists(); // Only one temporary point at a time is allowed

  context().mainWindow().scene().addTemporaryPoint (Point::temporaryPointIdentifier(),
                                                    point);
  m_posCandidatePoint = posScreen;
}

QCursor DigitizeStatePointMatch::cursor(CmdMediator * /* cmdMediator */) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::cursor";

  return QCursor (Qt::ArrowCursor);
}

void DigitizeStatePointMatch::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::end";

  // Remove candidate point which may or may not exist at this point
  context().mainWindow().scene().removeTemporaryPointIfExists();

  // Remove outline before leaving state
  ENGAUGE_CHECK_PTR (m_outline);
  context().mainWindow().scene().removeItem (m_outline);
  m_outline = nullptr;
}

QList<PointMatchPixel> DigitizeStatePointMatch::extractSamplePointPixels (const QImage &img,
                                                                          const DocumentModelPointMatch &modelPointMatch,
                                                                          const QPointF &posScreen) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::extractSamplePointPixels";

  // All points inside modelPointMatch.maxPointSize() are collected, whether or not they
  // are on or off. Originally only the on points were collected, but obvious mismatches
  // were happening (example, 3x3 point would appear to be found in several places inside 8x32 rectangle)
  QList<PointMatchPixel> samplePointPixels;

  int radiusMax = qFloor (modelPointMatch.maxPointSize() / 2);

  ColorFilter colorFilter;
  for (int xOffset = -radiusMax; xOffset <= radiusMax; xOffset++) {
    for (int yOffset = -radiusMax; yOffset <= radiusMax; yOffset++) {

      int x = qFloor (posScreen.x() + xOffset);
      int y = qFloor (posScreen.y() + yOffset);
      int radius = qFloor (qSqrt (xOffset * xOffset + yOffset * yOffset));

      if (radius <= radiusMax) {

        bool pixelIsOn = colorFilter.pixelFilteredIsOn (img,
                                                        x,
                                                        y);

        PointMatchPixel point (xOffset,
                               yOffset,
                               pixelIsOn);

        samplePointPixels.push_back (point);
      }
    }
  }

  return samplePointPixels;
}

void DigitizeStatePointMatch::handleContextMenuEventAxis (CmdMediator * /* cmdMediator */,
                                                          const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleContextMenuEventAxis "
                              << " point=" << pointIdentifier.toLatin1 ().data ();
}

void DigitizeStatePointMatch::handleContextMenuEventGraph (CmdMediator * /* cmdMediator */,
                                                           const QStringList &pointIdentifiers)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch ::handleContextMenuEventGraph "
                              << "points=" << pointIdentifiers.join(",").toLatin1 ().data ();
}

void DigitizeStatePointMatch::handleCurveChange(CmdMediator * /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleCurveChange";
}

void DigitizeStatePointMatch::handleKeyPress (CmdMediator *cmdMediator,
                                              Qt::Key key,
                                              bool /* atLeastOneSelectedItem */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleKeyPress"
                              << " key=" << QKeySequence (key).toString ().toLatin1 ().data ();

  // The selected key button has to be compatible with GraphicsView::keyPressEvent
  if (key == Qt::Key_Right) {

    promoteCandidatePointToPermanentPoint (cmdMediator); // This removes the current temporary point

    popCandidatePoint(cmdMediator); // This creates a new temporary point

  }
}

void DigitizeStatePointMatch::handleMouseMove (CmdMediator *cmdMediator,
                                               QPointF posScreen)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseMove";

  const DocumentModelPointMatch &modelPointMatch = cmdMediator->document().modelPointMatch();

  m_outline->setRect (posScreen.x() - modelPointMatch.maxPointSize() / 2.0,
                      posScreen.y() - modelPointMatch.maxPointSize() / 2.0,
                      modelPointMatch.maxPointSize(),
                      modelPointMatch.maxPointSize());

  const QImage &img = context().mainWindow().imageFiltered();
  int radiusLimit = cmdMediator->document().modelGeneral().cursorSize();
  bool pixelShouldBeOn = pixelIsOnInImage (img,
                                           qFloor (posScreen.x()),
                                           qFloor (posScreen.y()),
                                           radiusLimit);

  QColor penColorIs = m_outline->pen().color();
  bool pixelIsOn = (penColorIs.red () != penColorIs.green()); // Considered on if not gray scale
  if (pixelShouldBeOn != pixelIsOn) {
    QColor penColorShouldBe (pixelShouldBeOn ? Qt::green : Qt::black);
    m_outline->setPen (QPen (penColorShouldBe));
  }
}

void DigitizeStatePointMatch::handleMousePress (CmdMediator * /* cmdMediator */,
                                                QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMousePress";  
}

void DigitizeStatePointMatch::handleMouseRelease (CmdMediator *cmdMediator,
                                                  QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::handleMouseRelease";

  createPermanentPoint (cmdMediator,
                        posScreen);

  findPointsAndShowFirstCandidate (cmdMediator,
                                   posScreen);
}

void DigitizeStatePointMatch::findPointsAndShowFirstCandidate (CmdMediator *cmdMediator,
                                                               const QPointF &posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::findPointsAndShowFirstCandidate";

  const DocumentModelPointMatch &modelPointMatch = cmdMediator->document().modelPointMatch();
  const QImage &img = context().mainWindow().imageFiltered();

  QList<PointMatchPixel> samplePointPixels = extractSamplePointPixels (img,
                                                                       modelPointMatch,
                                                                       posScreen);

  QString curveName = activeCurve();
  const Document &doc = cmdMediator->document();
  const Curve *curve = doc.curveForCurveName (curveName);

  // The point match algorithm takes a few seconds, so set the cursor so user knows we are processing
  QApplication::setOverrideCursor(Qt::WaitCursor);

  PointMatchAlgorithm pointMatchAlgorithm (context().isGnuplot());
  m_candidatePoints = pointMatchAlgorithm.findPoints (samplePointPixels,
                                                      img,
                                                      modelPointMatch,
                                                      curve->points());

  QApplication::restoreOverrideCursor(); // Heavy duty processing has finished
  context().mainWindow().showTemporaryMessage ("Right arrow adds next matched point");

  popCandidatePoint (cmdMediator);
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

      int radius = qFloor (qSqrt (xOffset * xOffset + yOffset * yOffset));

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

void DigitizeStatePointMatch::popCandidatePoint (CmdMediator *cmdMediator)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStatePointMatch::popCandidatePoint";

  if (m_candidatePoints.count() > 0) {

    // Pop next point from list onto screen
    QPoint posScreen = m_candidatePoints.first();
    m_candidatePoints.pop_front ();

    createTemporaryPoint(cmdMediator,
                         posScreen);

  } else {

    // No more points. Inform user
    QMessageBox::information (nullptr,
                              QObject::tr ("Point Match"),
                              QObject::tr ("There are no more matching points"));

  }
}

void DigitizeStatePointMatch::promoteCandidatePointToPermanentPoint(CmdMediator *cmdMediator)
{
  createPermanentPoint (cmdMediator,
                        m_posCandidatePoint);
}

QString DigitizeStatePointMatch::state() const
{
  return "DigitizeStatePointMatch";
}

void DigitizeStatePointMatch::updateAfterPointAddition ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::updateAfterPointAddition";
}

void DigitizeStatePointMatch::updateModelDigitizeCurve (CmdMediator * /* cmdMediator */,
                                                        const DocumentModelDigitizeCurve & /*modelDigitizeCurve */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::updateModelDigitizeCurve";
}

void DigitizeStatePointMatch::updateModelSegments(const DocumentModelSegments & /* modelSegments */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStatePointMatch::updateModelSegments";
}
