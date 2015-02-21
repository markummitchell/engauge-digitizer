#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "CurveStyles.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
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
#include "Xml.h"

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
  m_curveAxes (0)
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
        if (tag == DOCUMENT_SERIALIZE_AXES_CHECKER){
          m_modelAxesChecker.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_COORDS) {
          m_modelCoords.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_CURVE) {
          m_curveAxes = new Curve (reader);
        } else if (tag == DOCUMENT_SERIALIZE_CURVES_GRAPHS) {
          m_curvesGraphs.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_DOCUMENT) {
          // Do nothing. This is the root node
        } else if (tag == DOCUMENT_SERIALIZE_EXPORT) {
          m_modelExport.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
          m_modelGridRemoval.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
          loadImage(reader);
        } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
          m_modelPointMatch.loadXml(reader);
        } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
          m_modelSegments.loadXml(reader);
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

  // There are already one axes curve and at least one graph curve so we do not need to add any more graph curves
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
  ENGAUGE_CHECK_PTR (m_curveAxes);

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
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curveAxes->iterateThroughCurvePoints (ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
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

DocumentModelAxesChecker Document::modelAxesChecker() const
{
  return m_modelAxesChecker;
}

DocumentModelCoords Document::modelCoords() const
{
  return m_modelCoords;
}

CurveStyles Document::modelCurveStyles() const
{
  // Construct a curve-specific model
  CurveStyles modelCurveStyles(*this);

  return modelCurveStyles;
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
  ENGAUGE_ASSERT (!m_successfulRead);

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

void Document::saveXml(QXmlStreamWriter &writer)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::saveXml";

  writer.writeStartDocument();
  writer.writeDTD("<!DOCTYPE engauge>");
  writer.writeStartElement(DOCUMENT_SERIALIZE_DOCUMENT);

  // Serialize the Document image. That binary data is encoded as base64
  QByteArray array;
  QDataStream str (&array, QIODevice::WriteOnly);
  QImage img = m_pixmap.toImage ();
  str << img;
  writer.writeStartElement(DOCUMENT_SERIALIZE_IMAGE);

  // Image width and height are explicitly inserted for error reports, since the CDATA is removed
  // but we still want the image size for reconstructing the error(s)
  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_WIDTH, QString::number (img.width()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_IMAGE_HEIGHT, QString::number (img.height()));

  writer.writeCDATA (array.toBase64 ());
  writer.writeEndElement();

  // Serialize the Document variables
  m_modelCoords.saveXml(writer);
  m_modelExport.saveXml(writer);
  m_modelAxesChecker.saveXml(writer);
  m_modelGridRemoval.saveXml(writer);
  m_modelPointMatch.saveXml(writer);
  m_modelSegments.saveXml(writer);
  m_curveAxes->saveXml(writer);
  m_curvesGraphs.saveXml(writer);
  writer.writeEndElement();
  writer.writeEndDocument();
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

void Document::setModelCurveStyles(const CurveStyles &modelCurveStyles)
{
  // Save the LineStyle for each Curve
  LineStyles::const_iterator itrL;
  for (itrL = modelCurveStyles.lineStyles().constBegin ();
       itrL != modelCurveStyles.lineStyles().constEnd();
       itrL++) {

    QString curveName = itrL.key();
    const LineStyle &lineStyle = itrL.value();

    Curve *curve = curveForCurveName (curveName);
    curve->setLineStyle (lineStyle);
  }

  // Save the PointStyle for each Curve
  PointStyles::const_iterator itrP;
  for (itrP = modelCurveStyles.pointStyles().constBegin ();
       itrP != modelCurveStyles.pointStyles().constEnd ();
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
