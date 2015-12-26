#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackNextOrdinal.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "Graph.h"
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

Graph::Graph () :
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          ColorFilterSettings::defaultFilter (),
                          CurveStyle (LineStyle::defaultAxesCurve(),
                                      PointStyle::defaultAxesCurve ())))
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::Graph";

  SettingsForGraph settingsForGraph;
  QString curveName = settingsForGraph.defaultCurveName (1,
                                                         DEFAULT_GRAPH_CURVE_NAME);
  m_curvesGraphs.addGraphCurveAtEnd (Curve (curveName,
                                            ColorFilterSettings::defaultFilter (),
                                            CurveStyle (LineStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()),
                                                        PointStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()))));
}

void Graph::addGraphCurveAtEnd (const QString &curveName)
{
  m_curvesGraphs.addGraphCurveAtEnd  (Curve (curveName,
                                             ColorFilterSettings::defaultFilter (),
                                             CurveStyle (LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                                         PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves()))));
}

void Graph::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    QString &identifier,
                                                    double ordinal)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph,
               ordinal);
  m_curveAxes->addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Graph::addPointAxisWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Graph::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    const QString &identifier,
                                                    double ordinal)
{
  Point point (AXIS_CURVE_NAME,
               identifier,
               posScreen,
               posGraph,
               ordinal);
  m_curveAxes->addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Graph::addPointAxisWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Graph::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     QString &identifier,
                                                     double ordinal)
{
  Point point (curveName,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Graph::addPointGraphWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Graph::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                  const QPointF &posScreen,
                                                  const QString &identifier,
                                                  double ordinal)
{
  Point point (curveName,
               identifier,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Graph::addPointGraphWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Graph::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackAddPointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackAddPointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

bool Graph::bytesIndicatePreVersion6 (const QByteArray &bytes) const
{
  QByteArray preVersion6MagicNumber;
  preVersion6MagicNumber.resize (FOUR_BYTES);
  preVersion6MagicNumber[0] = 0x00;
  preVersion6MagicNumber[1] = 0x00;
  preVersion6MagicNumber[2] = 0xCA;
  preVersion6MagicNumber[3] = 0xFE;

  return (bytes == preVersion6MagicNumber);
}

void Graph::checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::checkAddPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckAddPointAxis ftor (m_modelCoords,
                                  posScreen,
                                  posGraph);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckAddPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

void Graph::checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::checkEditPointAxis"
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ();

  CallbackCheckEditPointAxis ftor (m_modelCoords,
                                   pointIdentifier,
                                   posScreen,
                                   posGraph);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackCheckEditPointAxis::callback);
  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);

  isError = ftor.isError ();
  errorMessage = ftor.errorMessage ();
}

const Curve &Graph::curveAxes () const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  return *m_curveAxes;
}

Curve *Graph::curveForCurveName (const QString &curveName)
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const Curve *Graph::curveForCurveName (const QString &curveName) const
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const CurvesGraphs &Graph::curvesGraphs () const
{
  return m_curvesGraphs;
}

QStringList Graph::curvesGraphsNames() const
{
  return m_curvesGraphs.curvesGraphsNames();
}

int Graph::curvesGraphsNumPoints(const QString &curveName) const
{
  return m_curvesGraphs.curvesGraphsNumPoints(curveName);
}

void Graph::editPointAxis (const QPointF &posGraph,
                              const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::editPointAxis posGraph=("
                              << posGraph.x () << ", " << posGraph.y () << ") identifier="
                              << identifier.toLatin1 ().data ();

  m_curveAxes->editPoint (posGraph,
                          identifier);
}

void Graph::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Graph::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Graph::iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  if (curveName == AXIS_CURVE_NAME) {
    m_curveAxes->iterateThroughCurveSegments(ftorWithCallback);
  } else {
    m_curvesGraphs.iterateThroughCurveSegments(curveName,
                                               ftorWithCallback);
  }
}

void Graph::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Graph::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Graph::loadPostVersion5 (QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::loadPostVersion5";

  // If this is purely a serialized Document then we process every node under the root. However, if this is an error report file
  // then we need to skip the non-Document stuff. The common solution is to skip nodes outside the Document subtree using this flag
  bool inDocumentSubtree = false;

  // Import from xml. Loop to end of data or error condition occurs, whichever is first
  while (!reader.atEnd() &&
         !reader.hasError()) {
    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    // Special processing of DOCUMENT_SERIALIZE_IMAGE outside DOCUMENT_SERIALIZE_DOCUMENT, for an error report file
    if ((reader.name() == DOCUMENT_SERIALIZE_IMAGE) &&
        (tokenType == QXmlStreamReader::StartElement)) {

//      generateEmptyPixmap (reader.attributes());
    }

    // Branching to skip non-Document nodes, with the exception of any DOCUMENT_SERIALIZE_IMAGE outside DOCUMENT_SERIALIZE_DOCUMENT
    if ((reader.name() == DOCUMENT_SERIALIZE_DOCUMENT) &&
        (tokenType == QXmlStreamReader::StartElement)) {

      inDocumentSubtree = true;

    } else if ((reader.name() == DOCUMENT_SERIALIZE_DOCUMENT) &&
               (tokenType == QXmlStreamReader::EndElement)) {

      // Exit out of loop immediately
      break;
    }

    if (inDocumentSubtree) {

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
        } else if (tag == DOCUMENT_SERIALIZE_DOCUMENT) {
          // Do nothing. This is the root node
        } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
          m_modelExport.loadXml (reader);
        } else if (tag == DOCUMENT_SERIALIZE_GENERAL || tag == DOCUMENT_SERIALIZE_COMMON) {
          m_modelGeneral.loadXml (reader);
        } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
          m_modelGridRemoval.loadXml (reader);
        } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
          // A standard Document file has DOCUMENT_SERIALIZE_IMAGE inside DOCUMENT_SERIALIZE_DOCUMENT, versus an error report file
//          loadImage(reader);
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
  }
  if (reader.hasError ()) {

    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = reader.errorString();
  }

  // There are already one axes curve and at least one graph curve so we do not need to add any more graph curves
}

void Graph::loadPreVersion6 (QDataStream &str)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::loadPreVersion6";

  qint32 int32;
  double dbl, versionDouble, radius = 0.0;
  QString st;

  str >> int32; // Magic number
  str >> versionDouble;
  str >> st; // Version string
  str >> int32; // Background
//  str >> m_pixmap;
//  str >> m_name;
  str >> st; // CurveCmbText selection
  str >> st; // MeasureCmbText selection
  str >> int32;
  m_modelCoords.setCoordsType((CoordsType) int32);
  if (versionDouble >= 3) {
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
  if (versionDouble >= 5.2) {
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
  if (versionDouble >= 5) {
    QColor color;
    str >> color;
  } else {
    str >> int32; // Rgb color
  }
  str >> int32; // Foreground threshold low
  str >> int32; // Foreground threshold high
  str >> dbl; // Gap separation

  str >> int32; // Grid display is initialized flag
  str >> int32; // X count
  str >> int32; // Y count
  str >> int32; // X parameter
  str >> int32; // Y parameter
  str >> dbl; // X start
  str >> dbl; // Y start
  str >> dbl; // X step
  str >> dbl; // Y step
  str >> dbl; // X stop
  str >> dbl; // Y stop

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
  if (versionDouble < 4) {
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
}

DocumentModelAxesChecker Graph::modelAxesChecker() const
{
  return m_modelAxesChecker;
}

DocumentModelColorFilter Graph::modelColorFilter() const
{
  // Construct a curve-specific model
  DocumentModelColorFilter modelColorFilter(*this);

  return modelColorFilter;
}

DocumentModelCoords Graph::modelCoords() const
{
  return m_modelCoords;
}

CurveStyles Graph::modelCurveStyles() const
{
  // Construct a curve-specific model
  CurveStyles modelCurveStyles(*this);

  return modelCurveStyles;
}

DocumentModelDigitizeCurve Graph::modelDigitizeCurve() const
{
  return m_modelDigitizeCurve;
}

DocumentModelExportFormat Graph::modelExport() const
{
  return m_modelExport;
}

DocumentModelGeneral Graph::modelGeneral() const
{
  return m_modelGeneral;
}

DocumentModelGridRemoval Graph::modelGridRemoval() const
{
  return m_modelGridRemoval;
}

DocumentModelPointMatch Graph::modelPointMatch() const
{
  return m_modelPointMatch;
}

DocumentModelSegments Graph::modelSegments() const
{
  return m_modelSegments;
}

void Graph::movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen)
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->movePoint (pointIdentifier,
                    deltaScreen);
}

int Graph::nextOrdinalForCurve (const QString &curveName) const
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

QPointF Graph::positionGraph (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionGraph (pointIdentifier);
}

QPointF Graph::positionScreen (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionScreen (pointIdentifier);
}

void Graph::print () const
{
  QString text;
  QTextStream str (&text);

  printStream ("",
               str);
  std::cerr << text.toLatin1().data();
}

void Graph::printStream (QString indentation,
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
  m_modelGridRemoval.printStream (indentation,
                                  str);
  m_modelPointMatch.printStream (indentation,
                                 str);
  m_modelSegments.printStream (indentation,
                               str);
}

QString Graph::reasonForUnsuccessfulRead () const
{
  ENGAUGE_ASSERT (!m_successfulRead);

  return m_reasonForUnsuccessfulRead;
}

void Graph::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::removePointAxis identifier=" << identifier.toLatin1 ().data ();

  m_curveAxes->removePoint (identifier);
}

void Graph::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::removePointGraph identifier=" << identifier.toLatin1 ().data ();

  m_curvesGraphs.removePoint (identifier);
}

void Graph::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackRemovePointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackRemovePointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Graph::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_DOCUMENT);

  // Version number is tacked onto DOCUMENT_SERIALIZE_DOCUMENT since the alternative  (creating a new start element)
  // causes the code to complain during loading
  writer.writeAttribute(DOCUMENT_SERIALIZE_APPLICATION_VERSION_NUMBER, VERSION_NUMBER);

  // Serialize the Document image. That binary data is encoded as base64
  QByteArray array;
  QDataStream str (&array, QIODevice::WriteOnly);
//  QImage img = m_pixmap.toImage ();
//  str << img;
  writer.writeStartElement(DOCUMENT_SERIALIZE_IMAGE);

  // Image width and height are explicitly inserted for error reports, since the CDATA is removed
  // but we still want the image size for reconstructing the error(s)
//  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_WIDTH, QString::number (img.width()));
//  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_HEIGHT, QString::number (img.height()));

  writer.writeCDATA (array.toBase64 ());
  writer.writeEndElement();

  // Serialize the Document variables
  m_modelGeneral.saveXml (writer);
  m_modelCoords.saveXml (writer);
  m_modelDigitizeCurve.saveXml (writer);
  m_modelExport.saveXml (writer);
  m_modelAxesChecker.saveXml (writer);
  m_modelGridRemoval.saveXml (writer);
  m_modelPointMatch.saveXml (writer);
  m_modelSegments.saveXml (writer);
  m_curveAxes->saveXml (writer);
  m_curvesGraphs.saveXml (writer);
  writer.writeEndElement();
}

void Graph::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::setCurvesGraphs";

  m_curvesGraphs = curvesGraphs;
}

void Graph::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  m_modelAxesChecker = modelAxesChecker;
}

void Graph::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
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

void Graph::setModelCoords (const DocumentModelCoords &modelCoords)
{
  m_modelCoords = modelCoords;
}

void Graph::setModelCurveStyles(const CurveStyles &modelCurveStyles)
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

void Graph::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  m_modelDigitizeCurve = modelDigitizeCurve;
}

void Graph::setModelExport(const DocumentModelExportFormat &modelExport)
{
  m_modelExport = modelExport;
}

void Graph::setModelGeneral (const DocumentModelGeneral &modelGeneral)
{
  m_modelGeneral = modelGeneral;
}

void Graph::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  m_modelGridRemoval = modelGridRemoval;
}

void Graph::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  m_modelPointMatch = modelPointMatch;
}

void Graph::setModelSegments(const DocumentModelSegments &modelSegments)
{
  m_modelSegments = modelSegments;
}

bool Graph::successfulRead () const
{
  return m_successfulRead;
}

void Graph::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Graph::updatePointOrdinals";

  // The graph coordinates of all points in m_curvesGraphs must have already been updated at this point. See applyTransformation
  m_curvesGraphs.updatePointOrdinals (transformation);
}
