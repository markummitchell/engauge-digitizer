#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "Document.h"
#include "DocumentModelCurveProperties.h"
#include "DocumentSerialize.h"
#include "EnumsToQt.h"
#include <iostream>
#include "Logger.h"
#include "Point.h"
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QtToString.h>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Transformation.h"

Document::Document (const QImage &image) :
  m_name ("untitled"),
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          CurveFilter::defaultFilter (),
                          LineStyle::defaultAxesCurve(),
                          PointStyle::defaultAxesCurve ()))
{
  m_successfulRead = true; // Reading from QImage always succeeds, resulting in empty Document

  m_pixmap.convertFromImage (image);

  m_curvesGraphs.addGraphCurveAtEnd (Curve (DEFAULT_GRAPH_CURVE_NAME,
                                            CurveFilter::defaultFilter (),
                                            LineStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()),
                                            PointStyle::defaultGraphCurve (m_curvesGraphs.numCurves ())));
}

Document::Document (const QString &fileName) :
  m_name (fileName),
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          CurveFilter::defaultFilter (),
                          LineStyle::defaultAxesCurve(),
                          PointStyle::defaultAxesCurve()))
{
  m_successfulRead = true;

  QFile *file = new QFile (fileName);
  if (file->open (QIODevice::ReadOnly | QIODevice::Text)) {

    // Import from xml. Loop to end of data or error condition occurs, whichever is first
    QXmlStreamReader reader (file);
    while (!reader.atEnd() && !reader.hasError()) {
      QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

      // Iterate to next StartElement
      if (tokenType == QXmlStreamReader::StartElement) {

        // This is a StartElement, so process it
        QString tag = reader.name().toString();
        if (tag == DOCUMENT_SERIALIZE_AXES_CHECKER) {
          loadAxesChecker(reader);
        } else if (tag == DOCUMENT_SERIALIZE_COORDS) {
          loadCoords(reader);
        } else if (tag == DOCUMENT_SERIALIZE_CURVES_GRAPHS) {
          loadCurvesGraphs(reader);
        } else if (tag == DOCUMENT_SERIALIZE_DOCUMENT) {
          // Do nothing. This is the root node
        } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
          loadExport(reader);
        } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
          loadGridRemoval(reader);
        } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
          loadImage(reader);
        } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
          loadPointMatch(reader);
        } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
          loadSegments(reader);
        } else {
          m_successfulRead = false;
          m_reasonForUnsuccessfulRead = QString ("Unexpected xml token '%1' encountered").arg (tokenType);
          break;
        }
      }
    }
    if (reader.hasError ()) {

      m_successfulRead = false;
      m_reasonForUnsuccessfulRead = reader.errorString();
    }

    // Close and deactivate
    file->close ();
    delete file;
    file = 0;

  } else {

    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = "Operating system says file is not readable";
  }

  m_curvesGraphs.addGraphCurveAtEnd (Curve (DEFAULT_GRAPH_CURVE_NAME,
                                            CurveFilter::defaultFilter (),
                                            LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                            PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves())));
}

void Document::addGraphCurveAtEnd (const QString &curveName)
{
  m_curvesGraphs.addGraphCurveAtEnd  (Curve (curveName,
                                             CurveFilter::defaultFilter (),
                                             LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                             PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves())));
}

void Document::addPointAxis (const QPointF &posScreen,
                             const QPointF &posGraph,
                             QString &identifier)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               posGraph);
  m_curveAxes->addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointAxis (const QPointF &posScreen,
                             const QPointF &posGraph,
                             const QString &identifier)
{
  Point point (AXIS_CURVE_NAME,
               posScreen,
               identifier,
               posGraph);
  m_curveAxes->addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxis"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraph (const QString &curveName,
                              const QPointF &posScreen,
                              QString &identifier)
{
  Point point (curveName,
               posScreen);
  m_curvesGraphs.addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraph"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraph (const QString &curveName,
                              const QPointF &posScreen,
                              const QString &identifier)
{
  Point point (curveName,
               posScreen,
               identifier);
  m_curvesGraphs.addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraph"
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackAddPointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackAddPointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::applyTransformation (const Transformation &transformation)
{
  m_curvesGraphs.applyTransformation (transformation);
}

void Document::checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkAddPointAxis"
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

void Document::checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::checkEditPointAxis"
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

const Curve &Document::curveAxes () const
{
  Q_CHECK_PTR (m_curveAxes);

  return *m_curveAxes;
}

Curve *Document::curveForCurveName (const QString &curveName)
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const Curve *Document::curveForCurveName (const QString &curveName) const
{
  if (curveName == AXIS_CURVE_NAME) {

    return m_curveAxes;

  } else {

    return m_curvesGraphs.curveForCurveName (curveName);

  }
}

const CurvesGraphs &Document::curvesGraphs () const
{
  return m_curvesGraphs;
}

QStringList Document::curvesGraphsNames() const
{
  return m_curvesGraphs.curvesGraphsNames();
}

int Document::curvesGraphsNumPoints(const QString &curveName) const
{
  return m_curvesGraphs.curvesGraphsNumPoints(curveName);
}

void Document::editPointAxis (const QPointF &posGraph,
                              const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::editPointAxis posGraph=("
                              << posGraph.x () << ", " << posGraph.y () << ") identifier="
                              << identifier.toLatin1 ().data ();

  m_curveAxes->editPoint (posGraph,
                          identifier);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  Q_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  Q_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  Q_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::loadAxesChecker(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadAxesChecker";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR)) {

    m_modelAxesChecker.setCheckerMode ((CheckerMode) attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE).toInt());
    m_modelAxesChecker.setCheckerSeconds (attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS).toInt());
    m_modelAxesChecker.setLineColor ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_AXES_CHECKER)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read axes checker data");
  }
}

void Document::loadCoords(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadCoords";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_TYPE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS)) {

    m_modelCoords.setCoordsType ((CoordsType) attributes.value(DOCUMENT_SERIALIZE_COORDS_TYPE).toInt());
    m_modelCoords.setOriginRadius (attributes.value(DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS).toDouble());
    m_modelCoords.setCoordScaleXTheta ((CoordScale) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA).toInt());
    m_modelCoords.setCoordScaleYRadius ((CoordScale) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS).toInt());
    m_modelCoords.setCoordThetaUnits ((CoordThetaUnits) attributes.value(DOCUMENT_SERIALIZE_COORDS_THETA_UNITS).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_COORDS)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read coordinates data");
  }
}

void Document::loadCurvesGraphs(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadCurvesGraphs";

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CURVES_GRAPHS)){
    loadNextFromReader(reader);
  }
}

void Document::loadExport(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadExport";

  bool success = false;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_RELATIONS_INTERVAL) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_DELIMITER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_HEADER) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_EXPORT_X_LABEL)) {

    m_modelExport.setPointsSelectionFunctions ((ExportPointsSelectionFunctions) attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS).toInt());
    m_modelExport.setPointsInterval (attributes.value(DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL).toDouble());
    m_modelExport.setPointsSelectionRelations ((ExportPointsSelectionRelations) attributes.value(DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS).toInt());
    m_modelExport.setRelationsInterval (attributes.value(DOCUMENT_SERIALIZE_EXPORT_RELATIONS_INTERVAL).toDouble());
    m_modelExport.setLayoutFunctions ((ExportLayoutFunctions) attributes.value(DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS).toInt());
    m_modelExport.setDelimiter ((ExportDelimiter) attributes.value (DOCUMENT_SERIALIZE_EXPORT_DELIMITER).toInt());
    m_modelExport.setHeader ((ExportHeader) attributes.value(DOCUMENT_SERIALIZE_EXPORT_HEADER).toInt());
    m_modelExport.setXLabel (attributes.value(DOCUMENT_SERIALIZE_EXPORT_X_LABEL).toString());

    // Read element containing excluded curve names
    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);
    if ((tokenType == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_EXPORT_CURVE_NAMES_NOT_EXPORTED)) {

      QStringList curveNamesNotExported;

      tokenType = loadNextFromReader(reader);
      while (tokenType == QXmlStreamReader::StartElement) {

        if (reader.name() == DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED) {
          curveNamesNotExported << reader.text().toString();
        }
        tokenType = loadNextFromReader(reader);
      }

      // Save curve names
      m_modelExport.setCurveNamesNotExported(curveNamesNotExported);

      // Read until end of this subtree
      while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
      (reader.name() != DOCUMENT_SERIALIZE_EXPORT)){
        loadNextFromReader(reader);
      }

      success = true;
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read coordinates data");
  }
}

void Document::loadGridRemoval(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadGridRemoval";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y)) {

    QString removeValue = attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES).toString();

    m_modelGridRemoval.setRemoveDefinedGridLines (removeValue == DOCUMENT_SERIALIZE_BOOL_TRUE);
    m_modelGridRemoval.setCloseDistance (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE).toDouble());
    m_modelGridRemoval.setGridCoordDisableX ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X).toInt());
    m_modelGridRemoval.setCountX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X).toInt());
    m_modelGridRemoval.setStartX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X).toDouble());
    m_modelGridRemoval.setStepX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X).toDouble());
    m_modelGridRemoval.setStopX (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X).toDouble());
    m_modelGridRemoval.setGridCoordDisableY ((GridCoordDisable) attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y).toInt());
    m_modelGridRemoval.setCountY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y).toInt());
    m_modelGridRemoval.setStartY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y).toDouble());
    m_modelGridRemoval.setStepY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y).toDouble());
    m_modelGridRemoval.setStopY (attributes.value(DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y).toDouble());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_GRID_REMOVAL)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read grid removal data");
  }
}

void Document::loadImage(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadImage";

  loadNextFromReader(reader); // Read to CDATA
  if (reader.isCDATA ()) {

    // Get base64 array
    QByteArray array64 = reader.text().toString().toUtf8();

    // Decoded array
    QByteArray array;
    array = QByteArray::fromBase64(array64);

    // Read decoded array into image
    QDataStream str (&array, QIODevice::ReadOnly);
    QImage img = m_pixmap.toImage ();
    str >> img;
    m_pixmap = QPixmap::fromImage (img);

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_IMAGE)){
      loadNextFromReader(reader);
    }

  } else {
    reader.raiseError ("Cannot read image data");
  }
}

QXmlStreamReader::TokenType Document::loadNextFromReader (QXmlStreamReader &reader) const
{
  QXmlStreamReader::TokenType tokenType = reader.readNext();

  LOG4CPP_DEBUG_S ((*mainCat)) << "Document::loadNextFromReader "
                               << " tokenType=" << XmlReaderTokenTypeToString (tokenType).toLatin1().data()
                               << " tag=" << reader.name().toLatin1().data();

  return tokenType;
}

void Document::loadPointMatch(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadPointMatch";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SEPARATION) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED)) {

    m_modelPointMatch.setMinPointSeparation (attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SEPARATION).toDouble());
    m_modelPointMatch.setMaxPointSize (attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE).toDouble());
    m_modelPointMatch.setPaletteColorAccepted ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED).toInt());
    m_modelPointMatch.setPaletteColorCandidate ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE).toInt());
    m_modelPointMatch.setPaletteColorRejected ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_POINT_MATCH)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read point match data");
  }
}

void Document::loadSegments(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadSegments";

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_SEGMENTS)){
    loadNextFromReader(reader);
  }
}

DocumentModelAxesChecker Document::modelAxesChecker() const
{
  return m_modelAxesChecker;
}

DocumentModelCoords Document::modelCoords() const
{
  return m_modelCoords;
}

DocumentModelCurveProperties Document::modelCurveProperties() const
{
  // Construct a curve-specific model
  DocumentModelCurveProperties modelCurveProperties(*this);

  return modelCurveProperties;
}

DocumentModelExport Document::modelExport() const
{
  return m_modelExport;
}

DocumentModelFilter Document::modelFilter() const
{
  // Construct a curve-specific model
  DocumentModelFilter modelFilter(*this);

  return modelFilter;
}

DocumentModelGridRemoval Document::modelGridRemoval() const
{
  return m_modelGridRemoval;
}

DocumentModelPointMatch Document::modelPointMatch() const
{
  return m_modelPointMatch;
}

DocumentModelSegments Document::modelSegments() const
{
  return m_modelSegments;
}

void Document::movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen)
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->movePoint (pointIdentifier,
                    deltaScreen);
}

QPixmap Document::pixmap () const
{
  return m_pixmap;
}

QPointF Document::positionGraph (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionGraph (pointIdentifier);
}

QPointF Document::positionScreen (const QString &pointIdentifier) const
{
  QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

  const Curve *curve = curveForCurveName (curveName);
  return curve->positionScreen (pointIdentifier);
}

QString Document::reasonForUnsuccessfulRead () const
{
  Q_ASSERT (!m_successfulRead);

  return m_reasonForUnsuccessfulRead;
}

void Document::removePointAxis (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointAxis identifier=" << identifier.toLatin1 ().data ();

  m_curveAxes->removePoint (identifier);
}

void Document::removePointGraph (const QString &identifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::removePointGraph identifier=" << identifier.toLatin1 ().data ();

  m_curvesGraphs.removePoint (identifier);
}

void Document::removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  CallbackRemovePointsInCurvesGraphs ftor (*this);

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackRemovePointsInCurvesGraphs::callback);

  curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::saveDocument(QXmlStreamWriter &stream)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::saveDocument";

  stream.writeStartDocument();
  stream.writeDTD("<!DOCTYPE engauge>");
  stream.writeStartElement(DOCUMENT_SERIALIZE_DOCUMENT);

  // Serialize the Document image. That binary data is encoded as base64
  QByteArray array;
  QDataStream str (&array, QIODevice::WriteOnly);
  QImage img = m_pixmap.toImage ();
  str << img;
  stream.writeStartElement(DOCUMENT_SERIALIZE_IMAGE);
  stream.writeCDATA (array.toBase64 ());
  stream.writeEndElement();

  // Serialize the Document variables
  m_modelCoords.saveDocument(stream);
  m_modelExport.saveDocument(stream);
  m_modelAxesChecker.saveDocument(stream);
  m_modelGridRemoval.saveDocument(stream);
  m_modelPointMatch.saveDocument(stream);
  m_modelSegments.saveDocument(stream);
  m_curveAxes->saveDocument(stream);
  m_curvesGraphs.saveDocument(stream);
  stream.writeEndElement();
  stream.writeEndDocument();
}

void Document::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCurvesGraphs";

  m_curvesGraphs = curvesGraphs;
}

void Document::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  m_modelAxesChecker = modelAxesChecker;
}

void Document::setModelCoords (const DocumentModelCoords &modelCoords)
{
  m_modelCoords = modelCoords;
}

void Document::setModelCurveProperties(const DocumentModelCurveProperties &modelCurveProperties)
{
  // Save the LineStyle for each Curve
  LineStyles::const_iterator itrL;
  for (itrL = modelCurveProperties.lineStyles().constBegin ();
       itrL != modelCurveProperties.lineStyles().constEnd();
       itrL++) {

    QString curveName = itrL.key();
    const LineStyle &lineStyle = itrL.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setLineStyle (lineStyle);
  }

  // Save the PointStyle for each Curve
  PointStyles::const_iterator itrP;
  for (itrP = modelCurveProperties.pointStyles().constBegin ();
       itrP != modelCurveProperties.pointStyles().constEnd ();
       itrP++) {

    QString curveName = itrP.key();
    const PointStyle &pointStyle = itrP.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setPointStyle (pointStyle);
  }
}

void Document::setModelExport(const DocumentModelExport &modelExport)
{
  m_modelExport = modelExport;
}

void Document::setModelFilter(const DocumentModelFilter &modelFilter)
{
  // Save the CurveFilter for each Curve
  CurveFilters::const_iterator itr;
  for (itr = modelFilter.curveFilters().constBegin ();
       itr != modelFilter.curveFilters().constEnd();
       itr++) {

    QString curveName = itr.key();
    const CurveFilter &curveFilter = itr.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setCurveFilter (curveFilter);
  }
}

void Document::setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval)
{
  m_modelGridRemoval = modelGridRemoval;
}

void Document::setModelPointMatch(const DocumentModelPointMatch &modelPointMatch)
{
  m_modelPointMatch = modelPointMatch;
}

void Document::setModelSegments(const DocumentModelSegments &modelSegments)
{
  m_modelSegments = modelSegments;
}

bool Document::successfulRead () const
{
  return m_successfulRead;
}
