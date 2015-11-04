#include "CallbackAddPointsInCurvesGraphs.h"
#include "CallbackCheckAddPointAxis.h"
#include "CallbackCheckEditPointAxis.h"
#include "CallbackNextOrdinal.h"
#include "CallbackRemovePointsInCurvesGraphs.h"
#include "Curve.h"
#include "CurveStyles.h"
#include "Document.h"
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
#include "Transformation.h"
#include "Xml.h"

const int FOUR_BYTES = 4;

Document::Document (const QImage &image) :
  m_name ("untitled"),
  m_curveAxes (new Curve (AXIS_CURVE_NAME,
                          ColorFilterSettings::defaultFilter (),
                          CurveStyle (LineStyle::defaultAxesCurve(),
                                      PointStyle::defaultAxesCurve ())))
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::Document"
                              << " image=" << image.width() << "x" << image.height();

  m_successfulRead = true; // Reading from QImage always succeeds, resulting in empty Document

  m_pixmap.convertFromImage (image);

  m_curvesGraphs.addGraphCurveAtEnd (Curve (DEFAULT_GRAPH_CURVE_NAME,
                                            ColorFilterSettings::defaultFilter (),
                                            CurveStyle (LineStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()),
                                                        PointStyle::defaultGraphCurve (m_curvesGraphs.numCurves ()))));
}

Document::Document (const QString &fileName) :
  m_name (fileName),
  m_curveAxes (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::Document"
                              << " fileName=" << fileName.toLatin1().data();

  m_successfulRead = true;

  // Grab first few bytes to determine the version number
  QFile *file = new QFile (fileName);
  if (file->open(QIODevice::ReadOnly)) {

    QByteArray bytesStart = file->read (FOUR_BYTES);
    file->close ();

    if (bytesIndicatePreVersion6 (bytesStart)) {

      QFile *file = new QFile (fileName);
      if (file->open (QIODevice::ReadOnly)) {
        QDataStream str (file);

        loadPreVersion6 (str);

      } else {

        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = "Operating system says file is not readable";

      }
    } else {

      QFile *file = new QFile (fileName);
      if (file->open (QIODevice::ReadOnly | QIODevice::Text)) {

        QXmlStreamReader reader (file);

        loadPostVersion5 (reader);

        // Close and deactivate
        file->close ();
        delete file;
        file = 0;

      } else {

        m_successfulRead = false;
        m_reasonForUnsuccessfulRead = "Operating system says file is not readable";
      }
    }
  } else {
    file->close ();
    m_successfulRead = false;
    m_reasonForUnsuccessfulRead = QString ("File '%1' was not found")
                                  .arg (fileName);

  }
}

void Document::addGraphCurveAtEnd (const QString &curveName)
{
  m_curvesGraphs.addGraphCurveAtEnd  (Curve (curveName,
                                             ColorFilterSettings::defaultFilter (),
                                             CurveStyle (LineStyle::defaultGraphCurve(m_curvesGraphs.numCurves()),
                                                         PointStyle::defaultGraphCurve(m_curvesGraphs.numCurves()))));
}

void Document::addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
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

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxisWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
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

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointAxisWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " posGraph=" << QPointFToString (posGraph).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     QString &identifier,
                                                     double ordinal)
{
  Point point (curveName,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  identifier = point.identifier();

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraphWithGeneratedIdentifier"
                              << " ordinal=" << ordinal
                              << " posScreen=" << QPointFToString (posScreen).toLatin1 ().data ()
                              << " identifier=" << identifier.toLatin1 ().data ();
}

void Document::addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     const QString &identifier,
                                                     double ordinal)
{
  Point point (curveName,
               identifier,
               posScreen,
               ordinal);
  m_curvesGraphs.addPoint (point);

  LOG4CPP_INFO_S ((*mainCat)) << "Document::addPointGraphWithSpecifiedIdentifier"
                              << " ordinal=" << ordinal
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

bool Document::bytesIndicatePreVersion6 (const QByteArray &bytes) const
{
  QByteArray preVersion6MagicNumber;
  preVersion6MagicNumber.resize (FOUR_BYTES);
  preVersion6MagicNumber[0] = 0x00;
  preVersion6MagicNumber[1] = 0x00;
  preVersion6MagicNumber[2] = 0xCA;
  preVersion6MagicNumber[3] = 0xFE;

  return (bytes == preVersion6MagicNumber);
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

void Document::generateEmptyPixmap(const QXmlStreamAttributes &attributes)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::generateEmptyPixmap";

  int width = 800, height = 500; // Defaults

  if (attributes.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_WIDTH) &&
      attributes.hasAttribute (DOCUMENT_SERIALIZE_IMAGE_HEIGHT)) {

    width = attributes.value (DOCUMENT_SERIALIZE_IMAGE_WIDTH).toInt();
    height = attributes.value (DOCUMENT_SERIALIZE_IMAGE_HEIGHT).toInt();

  }

  m_pixmap = QPixmap (width, height);
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

void Document::iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  if (curveName == AXIS_CURVE_NAME) {
    m_curveAxes->iterateThroughCurveSegments(ftorWithCallback);
  } else {
    m_curvesGraphs.iterateThroughCurveSegments(curveName,
                                               ftorWithCallback);
  }
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  ENGAUGE_CHECK_PTR (m_curveAxes);

  m_curvesGraphs.iterateThroughCurvesPoints (ftorWithCallback);
}

void Document::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
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

    // This point can be reached if:
    // 1) File is broken
    // 2) Bad character is in text, and NetworkClient::cleanXml did not do its job
    reader.raiseError ("Cannot read image data");
  }
}

void Document::loadPostVersion5 (QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadPostVersion5";

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

      generateEmptyPixmap (reader.attributes());
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
        } else if (tag == DOCUMENT_SERIALIZE_COMMON) {
          m_modelCommon.loadXml (reader);
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
        } else if (tag == DOCUMENT_SERIALIZE_GRID_REMOVAL) {
          m_modelGridRemoval.loadXml (reader);
        } else if (tag == DOCUMENT_SERIALIZE_IMAGE) {
          // A standard Document file has DOCUMENT_SERIALIZE_IMAGE inside DOCUMENT_SERIALIZE_DOCUMENT, versus an error report file
          loadImage(reader);
        } else if (tag == DOCUMENT_SERIALIZE_POINT_MATCH) {
          m_modelPointMatch.loadXml (reader);
        } else if (tag == DOCUMENT_SERIALIZE_SEGMENTS) {
         m_modelSegments.loadXml (reader);
        } else {
          m_successfulRead = false;
          m_reasonForUnsuccessfulRead = QString ("Unexpected xml token '%1' encountered").arg (tokenType);
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

void Document::loadPreVersion6 (QDataStream &str)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::loadPreVersion6";

  qint32 int32;
  double dbl, versionDouble, radius = 0.0;
  QString st;

  str >> int32; // Magic number
  str >> versionDouble;
  str >> st; // Version string
  str >> int32; // Background
  str >> m_pixmap;
  str >> m_name;
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

DocumentModelAxesChecker Document::modelAxesChecker() const
{
  return m_modelAxesChecker;
}

DocumentModelColorFilter Document::modelColorFilter() const
{
  // Construct a curve-specific model
  DocumentModelColorFilter modelColorFilter(*this);

  return modelColorFilter;
}

DocumentModelCommon Document::modelCommon() const
{
  return m_modelCommon;
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

DocumentModelDigitizeCurve Document::modelDigitizeCurve() const
{
  return m_modelDigitizeCurve;
}

DocumentModelExportFormat Document::modelExport() const
{
  return m_modelExport;
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

int Document::nextOrdinalForCurve (const QString &curveName) const
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

void Document::print () const
{
  QString text;
  QTextStream str (&text);

  printStream ("",
               str);
  std::cerr << text.toLatin1().data();
}

void Document::printStream (QString indentation,
                            QTextStream &str) const
{
  str << indentation << "Document\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "name=" << m_name << "\n";
  str << indentation << "pixmap=" << m_pixmap.width() << "x" <<  m_pixmap.height() << "\n";

  m_curveAxes->printStream (indentation,
                            str);
  m_curvesGraphs.printStream (indentation,
                              str);

  m_modelAxesChecker.printStream (indentation,
                                  str);
  m_modelCommon.printStream (indentation,
                             str);
  m_modelCoords.printStream (indentation,
                             str);
  m_modelDigitizeCurve.printStream (indentation,
                                    str);
  m_modelExport.printStream (indentation,
                             str);
  m_modelGridRemoval.printStream (indentation,
                                  str);
  m_modelPointMatch.printStream (indentation,
                                 str);
  m_modelSegments.printStream (indentation,
                               str);
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

void Document::saveXml (QXmlStreamWriter &writer) const
{
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
  m_modelCommon.saveXml (writer);
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

void Document::setCurvesGraphs (const CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::setCurvesGraphs";

  m_curvesGraphs = curvesGraphs;
}

void Document::setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker)
{
  m_modelAxesChecker = modelAxesChecker;
}

void Document::setModelColorFilter(const DocumentModelColorFilter &modelColorFilter)
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

void Document::setModelCommon (const DocumentModelCommon &modelCommon)
{
  m_modelCommon = modelCommon;
}

void Document::setModelCoords (const DocumentModelCoords &modelCoords)
{
  m_modelCoords = modelCoords;
}

void Document::setModelCurveStyles(const CurveStyles &modelCurveStyles)
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

void Document::setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve)
{
  m_modelDigitizeCurve = modelDigitizeCurve;
}

void Document::setModelExport(const DocumentModelExportFormat &modelExport)
{
  m_modelExport = modelExport;
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

void Document::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Document::updatePointOrdinals";

  // The graph coordinates of all points in m_curvesGraphs must have already been updated at this point. See applyTransformation
  m_curvesGraphs.updatePointOrdinals (transformation);
}
