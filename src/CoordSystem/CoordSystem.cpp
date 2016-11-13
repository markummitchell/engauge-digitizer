/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackNextOrdinal.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "CoordSystem.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include <iostream>
#include "Logger.h"
#include "OrdinalGenerator.h"
#include "Point.h"
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QtToString.h>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "SettingsForGraph.h"
#include "Transformation.h"
#include "Version.h"
#include "Xml.h"

const int FOUR_BYTES = 4;

CoordSystem::CoordSystem (DocumentAxesPointsRequired documentAxesPointsRequired) :
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          ColorFilterSettings::defaultFilter (),
                          CurveStyle (LineStyle::defaultAxesCurve(),
                                      PointStyle::defaultAxesCurve ()))),
  m_documentAxesPointsRequired (documentAxesPointsRequired)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::CoordSystem";

  SettingsForGraph settingsForGraph;

  // Create one curve, or as many curve as specified in the configuration file, whichever is greater
  for (int indexOneBased = 1; indexOneBased <= settingsForGraph.numberOfCurvesForImport (); indexOneBased++) {

    QString curveName = settingsForGraph.defaultCurveName (indexOneBased,
                                                           DEFAULT_GRAPH_CURVE_NAME);
    m_curvesGraphs.addGraphCurveAtEnd (Curve (curveName,
                                              ColorFilterSettings::defaultFilter (),
                                              CurveStyle (LineStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()),
                                                          PointStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()))));

    resetSelectedCurveNameIfNecessary ();
  }
}

void CoordSystem::addGraphCurveAtEnd (const QString &curveName)
{
  m_curvesGraphs.addGraphCurveAtEnd  (Curve (curveName,
                                             ColorFilterSettings::defaultFilter (),
                                             CurveStyle (LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                                         PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves()))));

  resetSelectedCurveNameIfNecessary ();
}

void CoordSystem::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                       const QPointF &posGraph,
                                                       QString &identifier,
                                                       double ordinal,
                                                       bool isXOnly)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph,
               ordinal,
               isXOnly);
  m_curveAxes->addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::addPointAxisWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void CoordSystem::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                       const QPointF &posGraph,
                                                       const QString &identifier,
                                                       double ordinal,
                                                       bool isXOnly)
{
  Point point (AXIS_CURVE_NAME,
               identifier,
               posScreen,
               posGraph,
               ordinal,
               isXOnly);
  m_curveAxes->addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::addPointAxisWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void CoordSystem::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                        const QPointF &posScreen,
                                                        QString &identifier,
                                                        double ordinal)
{
  Point point (curveName,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::addPointGraphWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void CoordSystem::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                        const QPointF &posScreen,
                                                        const QString &identifier,
                                                        double ordinal)
{
  Point point (curveName,
               identifier,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::addPointGraphWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void CoordSystem::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackAddPointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackAddPointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

bool CoordSystem::bytesIndicatePreVersion6 (const QByteArray &bytes) const
{
  QByteArray preVersion6MagicNumber;
  preVersion6MagicNumber.resize (FOUR_BYTES);

  // Windows compiler gives warning if 0x## is used instead of '\x##' below
  preVersion6MagicNumber[0] = '\x00';
  preVersion6MagicNumber[1] = '\x00';
  preVersion6MagicNumber[2] = '\xCA';
  preVersion6MagicNumber[3] = '\xFE';

  return (bytes == preVersion6MagicNumber);
}

void CoordSystem::checkAddPointAxis (const QPointF &posScreen,
                                     const QPointF &posGraph,
                                     bool &isError,
                                     QString &errorMessage,
                                     bool isXOnly)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::checkAddPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckAddPointAxis ftor (m_modelCoords,
                                  posScreen,
                                  posGraph,
                                  m_documentAxesPointsRequired,
                                  isXOnly);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckAddPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

void CoordSystem::checkEditPointAxis (const QString &pointIdentifier,
                                      const QPointF &posScreen,
                                      const QPointF &posGraph,
                                      bool &isError,
                                      QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::checkEditPointAxis"
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckEditPointAxis ftor (m_modelCoords,
                                   pointIdentifier,
                                   posScreen,
                                   posGraph,
                                   m_documentAxesPointsRequired);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckEditPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

const Curve &CoordSystem::curveAxes () const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  return *m_curveAxes;
}

Curve *CoordSystem::curveForCurveName (const QString &curveName)
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const Curve *CoordSystem::curveForCurveName (const QString &curveName) const
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const CurvesGraphs &CoordSystem::curvesGraphs () const
{
  return m_curvesGraphs;
}

QStringList CoordSystem::curvesGraphsNames() const
{
  return m_curvesGraphs.curvesGraphsNames();
}

int CoordSystem::curvesGraphsNumPoints(const QString &curveName) const
{
  return m_curvesGraphs.curvesGraphsNumPoints(curveName);
}

void CoordSystem::editPointAxis (const QPointF &posGraph,
                                 const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::editPointAxis"
                              << " posGraph=(" << posGraph.x () << ", " << posGraph.y () << ") identifier="
                              << " identifier=" << identifier.toLatin1 ().data ();

  m_curveAxes->editPointAxis (posGraph,
                              identifier);
}

void CoordSystem::editPointGraph (bool isX,
                                  bool isY,
                                  double x,
                                  double y,
                                  const QStringList &identifiers,
                                  const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::editPointGraph posGraph=("
                              << " x=" << (isX ? QString::number (x).toLatin1().data() : "")
                              << " y=" << (isY ? QString::number (y).toLatin1().data() : "")
                              << ") identifiers=" << identifiers.join(" ").toLatin1 ().data ();

  m_curvesGraphs.editPointGraph (isX,
                                 isY,
                                 x,
                                 y,
                                 identifiers,
                                 transformation);
}

bool CoordSystem::isXOnly (const QString &pointIdentifier) const
{
  return m_curveAxes->isXOnly (pointIdentifier);
}

void CoordSystem::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void CoordSystem::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void CoordSystem::iterateThroughCurveSegments (const QString &curveName,
                                               const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  if (curveName == AXIS_CURVE_NAME) {
    m_curveAxes->iterateThroughCurveSegments(ftorWithCallback);
  } else {
    m_curvesGraphs.iterateThroughCurveSegments(curveName,
                                               ftorWithCallback);
  }
}

void CoordSystem::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void CoordSystem::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

bool CoordSystem::loadCurvesFile(const QString & /* curvesFile */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::loadCurvesFile";

  return true;
}

void CoordSystem::loadPreVersion6 (QDataStream &str,
                                   double version)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::loadPreVersion6";

  qint32 int32;
  double dbl, radius = 0.0;
  QString st;

  m_documentAxesPointsRequired = DOCUMENT_AXES_POINTS_REQUIRED_3;

  str >> st; // CurveCmbText selection
  str >> st; // MeasureCmbText selection
  str >> int32;
  m_modelCoords.setCoordsType((CoordsType) int32);
  if (version >= 3) {
    str >> (double &) radius;
  }
  m_modelCoords.setOriginRadius(radius);
  str >> int32;
  m_modelCoords.setCoordUnitsRadius(COORD_UNITS_NON_POLAR_THETA_NUMBER);
  m_modelCoords.setCoordUnitsTheta((CoordUnitsPolarTheta) int32);
  str >> int32;
  m_modelCoords.setCoordScaleXTheta((CoordScale) int32);
  str >> int32;
  m_modelCoords.setCoordScaleYRadius((CoordScale) int32);

  str >> int32;
  m_modelExport.setDelimiter((ExportDelimiter) int32);
  str >> int32;
  m_modelExport.setLayoutFunctions((ExportLayoutFunctions) int32);
  str >> int32;
  m_modelExport.setPointsSelectionFunctions((ExportPointsSelectionFunctions) int32);
  m_modelExport.setPointsIntervalUnitsRelations((ExportPointsIntervalUnits) int32);
  str >> int32;
  m_modelExport.setHeader((ExportHeader) int32);
  if (version >= 5.1) {
    str >> st; // X label
    if (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {
      m_modelExport.setXLabel(st);
    }
    str >> st; // Theta label
    if (m_modelCoords.coordsType() == COORDS_TYPE_POLAR) {
      m_modelExport.setXLabel(st);
    }
  }

  // Stable flag in m_modelGridRemoval is set below after points are read in
  str >> int32; // Remove thin lines parallel to axes
  str >> dbl; // Thin thickness
  str >> int32;
  m_modelGridRemoval.setRemoveDefinedGridLines(int32);
  str >> int32; // Initialized
  str >> int32;
  m_modelGridRemoval.setCountX(int32);
  str >> int32;
  m_modelGridRemoval.setCountY(int32);
  str >> int32;
  m_modelGridRemoval.setGridCoordDisableX((GridCoordDisable) int32);
  str >> int32;
  m_modelGridRemoval.setGridCoordDisableY((GridCoordDisable) int32);
  str >> dbl;
  m_modelGridRemoval.setStartX(dbl);
  str >> dbl;
  m_modelGridRemoval.setStartY(dbl);
  str >> dbl;
  m_modelGridRemoval.setStepX(dbl);
  str >> dbl;
  m_modelGridRemoval.setStepY(dbl);
  str >> dbl;
  m_modelGridRemoval.setStopX(dbl);
  str >> dbl;
  m_modelGridRemoval.setStopY(dbl);
  str >> dbl;
  m_modelGridRemoval.setCloseDistance(dbl);
  str >> int32; // Boolean remove color flag
  if (version >= 5) {
    QColor color;
    str >> color;
  } else {
    str >> int32; // Rgb color
  }
  str >> int32; // Foreground threshold low
  str >> int32; // Foreground threshold high
  str >> dbl; // Gap separation

  str >> int32;
  m_modelGridDisplay.setStable(int32);
  str >> int32;
  m_modelGridDisplay.setCountX(int32);
  str >> int32;
  m_modelGridDisplay.setCountY(int32);
  str >> int32;
  m_modelGridDisplay.setDisableX((GridCoordDisable) int32);
  str >> int32;
  m_modelGridDisplay.setDisableY((GridCoordDisable) int32);
  str >> dbl;
  m_modelGridDisplay.setStartX (dbl);
  str >> dbl;
  m_modelGridDisplay.setStartY (dbl);
  str >> dbl;
  m_modelGridDisplay.setStepX (dbl);
  str >> dbl;
  m_modelGridDisplay.setStepY (dbl);
  str >> dbl;
  m_modelGridDisplay.setStopX (dbl);
  str >> dbl;
  m_modelGridDisplay.setStopY (dbl);

  str >> int32;
  m_modelSegments.setMinLength(int32);
  str >> int32;
  m_modelSegments.setPointSeparation(int32);
  str >> int32;
  m_modelSegments.setLineWidth(int32);
  str >> int32;
  m_modelSegments.setLineColor((ColorPalette) int32);

  str >> int32; // Point separation
  str >> int32;
  m_modelPointMatch.setMaxPointSize(int32);
  str >> int32;
  m_modelPointMatch.setPaletteColorAccepted((ColorPalette) int32);
  str >> int32;
  m_modelPointMatch.setPaletteColorRejected((ColorPalette) int32);
  if (version < 4) {
    m_modelPointMatch.setPaletteColorCandidate(COLOR_PALETTE_BLUE);
  } else {
    str >> int32;
    m_modelPointMatch.setPaletteColorCandidate((ColorPalette) int32);
  }

  str >> int32; // Discretize method
  str >> int32; // Intensity threshold low
  str >> int32; // Intensity threshold high
  str >> int32; // Foreground threshold low
  str >> int32; // Foreground threshold high
  str >> int32; // Hue threshold low
  str >> int32; // Hue threshold high
  str >> int32; // Saturation threshold low
  str >> int32; // Saturation threshold high
  str >> int32; // Value threshold low
  str >> int32; // Value threshold high

  m_curveAxes = new Curve (str);
  Curve curveScale (str); // Scales are dropped on the floor
  m_curvesGraphs.loadPreVersion6 (str);

  // Information from curves and points can affect some data structures that were (mostly) set earlier
  if (m_curveAxes->numPoints () > 2) {
    m_modelGridRemoval.setStable();
  }

  resetSelectedCurveNameIfNecessary ();
}

void CoordSystem::loadVersion6 (QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::loadVersion6";

  m_documentAxesPointsRequired = DOCUMENT_AXES_POINTS_REQUIRED_3;

  // Import from xml. Loop to end of data or error condition occurs, whichever is first
  while (!reader.atEnd() &&
         !reader.hasError()) {
    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    if ((reader.name() == DOCUMENT_SERIALIZE_DOCUMENT) &&
               (tokenType == QXmlStreamReader::EndElement)) {

      // Exit out of loop immediately
      break;
    }

    // Iterate to next StartElement
    if (tokenType == QXmlStreamReader::StartElement) {

      // This is a StartElement, so process it
      QString tag = reader.name().toString();
      if (tag == DOCUMENT_SERIALIZE_AXES_CHECKER){
        m_modelAxesChecker.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_COORDS) {
        m_modelCoords.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_CURVE) {
        m_curveAxes = new Curve (reader);
      } else if (tag == DOCUMENT_SERIALIZE_CURVES_GRAPHS) {
        m_curvesGraphs.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_DIGITIZE_CURVE) {
        m_modelDigitizeCurve.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
        m_modelExport.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_GENERAL || tag == DOCUMENT_SERIALIZE_COMMON) {
        m_modelGeneral.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
        m_modelGridRemoval.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
        ENGAUGE_ASSERT (false); // The image should have been read before this method was called
      } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
        m_modelPointMatch.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
        m_modelSegments.loadXml (reader);
      } else {
        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = QString ("%1 '%2' %3")
                                      .arg (QObject::tr ("Unexpected xml token"))
                                      .arg (tag)
                                      .arg ("encountered");
        break;
      }
    }
  }

  resetSelectedCurveNameIfNecessary ();
}

void CoordSystem::loadVersions7AndUp (QXmlStreamReader &reader,
                                      DocumentAxesPointsRequired documentAxesPointsRequired)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::loadVersions7AndUp";

  m_documentAxesPointsRequired = documentAxesPointsRequired;

  // Import from xml. Loop to end of data or error condition occurs, whichever is first
  while (!reader.atEnd() &&
         !reader.hasError()) {
    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    if ((reader.name() == DOCUMENT_SERIALIZE_COORD_SYSTEM) &&
               (tokenType == QXmlStreamReader::EndElement)) {

      // Exit out of loop immediately
      break;
    }

    // Iterate to next StartElement
    if (tokenType == QXmlStreamReader::StartElement) {

      // This is a StartElement, so process it
      QString tag = reader.name().toString();
      if (tag == DOCUMENT_SERIALIZE_AXES_CHECKER){
        m_modelAxesChecker.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_COORDS) {
        m_modelCoords.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_CURVE) {
        m_curveAxes = new Curve (reader);
      } else if (tag == DOCUMENT_SERIALIZE_CURVES_GRAPHS) {
        m_curvesGraphs.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_DIGITIZE_CURVE) {
        m_modelDigitizeCurve.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
        m_modelExport.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_GENERAL || tag == DOCUMENT_SERIALIZE_COMMON) {
        m_modelGeneral.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_GRID_DISPLAY) {
        m_modelGridDisplay.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
        m_modelGridRemoval.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
        ENGAUGE_ASSERT (false); // The image should have been read before this method was called
      } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
        m_modelPointMatch.loadXml (reader);
      } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
        m_modelSegments.loadXml (reader);
      } else {
        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = QString ("Unexpected xml token '%1' encountered").arg (tag);
        break;
      }
    }
  }

  resetSelectedCurveNameIfNecessary ();
}

DocumentModelAxesChecker CoordSystem::modelAxesChecker() const
{
  return m_modelAxesChecker;
}

DocumentModelColorFilter CoordSystem::modelColorFilter() const
{
  // Construct a curve-specific model
  DocumentModelColorFilter modelColorFilter(*this);

  return modelColorFilter;
}

DocumentModelCoords CoordSystem::modelCoords() const
{
  return m_modelCoords;
}

CurveStyles CoordSystem::modelCurveStyles() const
{
  // Construct a curve-specific model
  CurveStyles modelCurveStyles(*this);

  return modelCurveStyles;
}

DocumentModelDigitizeCurve CoordSystem::modelDigitizeCurve() const
{
  return m_modelDigitizeCurve;
}

DocumentModelExportFormat CoordSystem::modelExport() const
{
  return m_modelExport;
}

DocumentModelGeneral CoordSystem::modelGeneral() const
{
  return m_modelGeneral;
}

DocumentModelGridDisplay CoordSystem::modelGridDisplay() const
{
  return m_modelGridDisplay;
}

DocumentModelGridRemoval CoordSystem::modelGridRemoval() const
{
  return m_modelGridRemoval;
}

DocumentModelPointMatch CoordSystem::modelPointMatch() const
{
  return m_modelPointMatch;
}

DocumentModelSegments CoordSystem::modelSegments() const
{
  return m_modelSegments;
}

void CoordSystem::movePoint (const QString &pointIdentifier,
                             const QPointF &deltaScreen)
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  ENGAUGE_ASSERT (curve != 0);
  curve->movePoint (pointIdentifier,
                    deltaScreen);
}

int CoordSystem::nextOrdinalForCurve (const QString &curveName) const
{
  CallbackNextOrdinal ftor (curveName);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackNextOrdinal::callback);

  if (curveName == AXIS_CURVE_NAME) {
    m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
  } else {
    m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
  }

  return ftor.nextOrdinal ();
}

QPointF CoordSystem::positionGraph (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionGraph (pointIdentifier);
}

QPointF CoordSystem::positionScreen (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionScreen (pointIdentifier);
}

void CoordSystem::print () const
{
  QString text;
  QTextStream str (&text);

  printStream ("",
               str);
  std::cerr << text.toLatin1().data();
}

void CoordSystem::printStream (QString indentation,
                               QTextStream &str) const
{
  str << indentation << "Graph\n";

  indentation += INDENTATION_DELTA;

  //  str << indentation << "name=" << m_name << "\n";
  //  str << indentation << "pixmap=" << m_pixmap.width() << "x" <<  m_pixmap.height() << "\n";

  m_curveAxes->printStream (indentation,
                            str);
  m_curvesGraphs.printStream (indentation,
                              str);

  m_modelAxesChecker.printStream (indentation,
                                  str);
  m_modelCoords.printStream (indentation,
                             str);
  m_modelDigitizeCurve.printStream (indentation,
                                    str);
  m_modelExport.printStream (indentation,
                             str);
  m_modelGeneral.printStream (indentation,
                              str);
  m_modelGridDisplay.printStream (indentation,
                                  str);
  m_modelGridRemoval.printStream (indentation,
                                  str);
  m_modelPointMatch.printStream (indentation,
                                 str);
  m_modelSegments.printStream (indentation,
                               str);
}

QString CoordSystem::reasonForUnsuccessfulRead () const
{
  ENGAUGE_ASSERT (!m_successfulRead);

  return m_reasonForUnsuccessfulRead;
}

void CoordSystem::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::removePointAxis identifier=" << identifier.toLatin1 ().data ();

  m_curveAxes->removePoint (identifier);
}

void CoordSystem::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::removePointGraph identifier=" << identifier.toLatin1 ().data ();

  m_curvesGraphs.removePoint (identifier);
}

void CoordSystem::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackRemovePointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackRemovePointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void CoordSystem::resetSelectedCurveNameIfNecessary ()
{
  if (m_selectedCurveName.isEmpty () ||
      curveForCurveName (m_selectedCurveName) == 0) {

    // Selected curve name is empty, or the curve has been removed so we pick another. The first is arbitrarily picked
    m_selectedCurveName = m_curvesGraphs.curvesGraphsNames().first();
  }

}

void CoordSystem::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_COORD_SYSTEM);

  // Serialize the Document variables
  m_modelGeneral.saveXml (writer);
  m_modelCoords.saveXml (writer);
  m_modelDigitizeCurve.saveXml (writer);
  m_modelExport.saveXml (writer);
  m_modelAxesChecker.saveXml (writer);
  m_modelGridDisplay.saveXml (writer);
  m_modelGridRemoval.saveXml (writer);
  m_modelPointMatch.saveXml (writer);
  m_modelSegments.saveXml (writer);
  m_curveAxes->saveXml (writer);
  m_curvesGraphs.saveXml (writer);
  writer.writeEndElement();
}

QString CoordSystem::selectedCurveName () const
{
  return m_selectedCurveName;
}

void CoordSystem::setCurveAxes (const Curve &curveAxes)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::setCurveAxes";

  if (m_curveAxes != 0) {
    delete m_curveAxes;
    m_curveAxes = 0;
  }

  m_curveAxes = new Curve (curveAxes);
}

void CoordSystem::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::setCurvesGraphs";

  m_curvesGraphs = curvesGraphs;

  resetSelectedCurveNameIfNecessary ();
}

void CoordSystem::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  m_modelAxesChecker = modelAxesChecker;
}

void CoordSystem::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
{
  // Save the CurveFilter for each Curve
  ColorFilterSettingsList::const_iterator itr;
  for (itr = modelColorFilter.colorFilterSettingsList().constBegin ();
       itr != modelColorFilter.colorFilterSettingsList().constEnd();
       itr++) {

    QString curveName = itr.key();
    const ColorFilterSettings &colorFilterSettings = itr.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setColorFilterSettings (colorFilterSettings);
  }
}

void CoordSystem::setModelCoords (const DocumentModelCoords &modelCoords)
{
  m_modelCoords = modelCoords;
}

void CoordSystem::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  // Save the LineStyle and PointStyle for each Curve
  QStringList curveNames = modelCurveStyles.curveNames();
  QStringList::iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;
    const CurveStyle &curveStyle = modelCurveStyles.curveStyle (curveName);

    Curve *curve = curveForCurveName (curveName);
    curve->setCurveStyle (curveStyle);
  }
}

void CoordSystem::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  m_modelDigitizeCurve = modelDigitizeCurve;
}

void CoordSystem::setModelExport(const DocumentModelExportFormat &modelExport)
{
  m_modelExport = modelExport;
}

void CoordSystem::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  m_modelGeneral = modelGeneral;
}

void CoordSystem::setModelGridDisplay(const DocumentModelGridDisplay &modelGridDisplay)
{
  m_modelGridDisplay = modelGridDisplay;
}

void CoordSystem::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  m_modelGridRemoval = modelGridRemoval;
}

void CoordSystem::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  m_modelPointMatch = modelPointMatch;
}

void CoordSystem::setModelSegments(const DocumentModelSegments &modelSegments)
{
  m_modelSegments = modelSegments;
}

void CoordSystem::setSelectedCurveName(const QString &selectedCurveName)
{
  m_selectedCurveName = selectedCurveName;
}

bool CoordSystem::successfulRead () const
{
  return m_successfulRead;
}

void CoordSystem::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CoordSystem::updatePointOrdinals";

  // The graph coordinates of all points in m_curvesGraphs must have already been updated at this point. See applyTransformation
  m_curvesGraphs.updatePointOrdinals (transformation);
}
