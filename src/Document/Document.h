#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DocumentModelAxesChecker.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelCommon.h"
#include "DocumentModelCoords.h"
#include "DocumentModelDigitizeCurve.h"
#include "DocumentModelExportFormat.h"
#include "DocumentModelGridRemoval.h"
#include "DocumentModelPointMatch.h"
#include "DocumentModelSegments.h"
#include "PointStyle.h"
#include <QList>
#include <QPixmap>
#include <QString>
#include <QXmlStreamReader>

class Curve;
class QByteArray;
class QImage;
class QTransform;
class QXmlStreamWriter;
class Transformation;

/// Storage of one imported image and the data attached to that image
class Document
{
public:
  /// Constructor for imported images and dragged images
  Document (const QImage &image);

  /// Constructor for opened Documents, and error report files. The specified file is opened and read
  Document (const QString &fileName);

  /// Add new graph curve to the list of existing graph curves.
  void addGraphCurveAtEnd (const QString &curveName);

  /// Add a single axis point with a generated point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  void addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            QString &identifier,
                                            double ordinal);

  /// Add a single axis point with the specified point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  void addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            const QString &identifier,
                                            double ordinal);

  /// Add a single graph point with a generated point identifier.
  void addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                             const QPointF &posScreen,
                                             QString &generatedIentifier,
                                             double ordinal);

  /// Add a single graph point with the specified point identifer. Note that PointStyle is not applied to the point within the Document.
  void addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                             const QPointF &posScreen,
                                             const QString &identifier,
                                             double ordinal);

  /// Add all points identified in the specified CurvesGraphs. See also removePointsInCurvesGraphs
  void addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs);

  /// Check before calling addPointAxis. Also returns the next available ordinal number (to prevent clashes)
  void checkAddPointAxis (const QPointF &posScreen,
                          const QPointF &posGraph,
                          bool &isError,
                          QString &errorMessage);

  /// Check before calling editPointAxis
  void checkEditPointAxis (const QString &pointIdentifier,
                           const QPointF &posScreen,
                           const QPointF &posGraph,
                           bool &isError,
                           QString &errorMessage);

  /// Get method for axis curve.
  const Curve &curveAxes () const;

  /// See CurvesGraphs::curveForCurveNames, although this also works for AXIS_CURVE_NAME.
  const Curve *curveForCurveName (const QString &curveName) const;

  /// Make all Curves available, read only, for CmdAbstract classes only.
  const CurvesGraphs &curvesGraphs () const;

  /// See CurvesGraphs::curvesGraphsNames.
  QStringList curvesGraphsNames () const;

  /// See CurvesGraphs::curvesGraphsNumPoints.
  int curvesGraphsNumPoints (const QString &curveName) const;

  /// Edit the graph coordinates of a single axis point. Call this after checkAddPointAxis to guarantee success in this call
  void editPointAxis (const QPointF &posGraph,
                      const QString &identifier);

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// See Curve::iterateThroughCurveSegments, for any axes or graph curve
  void iterateThroughCurveSegments (const QString &curveName,
                                    const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// Get method for DocumentModelAxesChecker.
  DocumentModelAxesChecker modelAxesChecker() const;

  /// Get method for DocumentModelColorFilter.
  DocumentModelColorFilter modelColorFilter() const;

  /// Get method for DocumentModelCommon.
  DocumentModelCommon modelCommon() const;

  /// Get method for DocumentModelCoords.
  DocumentModelCoords modelCoords () const;

  /// Get method for CurveStyles.
  CurveStyles modelCurveStyles() const;

  /// Get method for DocumentModelDigitizeCurve.
  DocumentModelDigitizeCurve modelDigitizeCurve() const;

  /// Get method for DocumentModelExportFormat.
  DocumentModelExportFormat modelExport() const;

  /// Get method for DocumentModelGridRemoval.
  DocumentModelGridRemoval modelGridRemoval() const;

  /// Get method for DocumentModelPointMatch.
  DocumentModelPointMatch modelPointMatch() const;

  /// Get method for DocumentModelSegments.
  DocumentModelSegments modelSegments() const;

  /// See Curve::movePoint
  void movePoint (const QString &pointIdentifier,
                  const QPointF &deltaScreen);

  /// Default next ordinal value for specified curve
  int nextOrdinalForCurve (const QString &curveName) const;

  /// Return the image that is being digitized.
  QPixmap pixmap () const;

  /// See Curve::positionGraph.
  QPointF positionGraph (const QString &pointIdentifier) const;

  /// See Curve::positionScreen.
  QPointF positionScreen (const QString &pointIdentifier) const;

  /// Debugging method for printing directly from symbolic debugger
  void print () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Return an informative text message explaining why startup loading failed. Applies if successfulRead returns false
  QString reasonForUnsuccessfulRead () const;

  /// Perform the opposite of addPointAxis.
  void removePointAxis (const QString &identifier);

  /// Perform the opposite of addPointGraph.
  void removePointGraph (const QString &identifier);

  /// Remove all points identified in the specified CurvesGraphs. See also addPointsInCurvesGraphs
  void removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs);

  /// Save document to xml
  void saveXml (QXmlStreamWriter &writer) const;

  /// Let CmdAbstract classes overwrite CurvesGraphs.
  void setCurvesGraphs (const CurvesGraphs &curvesGraphs);

  /// Set method for DocumentModelAxesChecker.
  void setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);

  /// Set method for DocumentModelColorFilter.
  void setModelColorFilter(const DocumentModelColorFilter &modelColorFilter);

  /// Set method for DocumentModelCommon.
  void setModelCommon (const DocumentModelCommon &modelCommon);

  /// Set method for DocumentModelCoords.
  void setModelCoords (const DocumentModelCoords &modelCoords);

  /// Set method for CurveStyles.
  void setModelCurveStyles(const CurveStyles &modelCurveStyles);

  /// Set method for DocumentModelDigitizeCurve.
  void setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);

  /// Set method for DocumentModelExportFormat.
  void setModelExport(const DocumentModelExportFormat &modelExport);

  /// Set method for DocumentModelGridRemoval.
  void setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);

  /// Set method for DocumentModelPointMatch.
  void setModelPointMatch(const DocumentModelPointMatch &modelPointMatch);

  /// Set method for DocumentModelSegments.
  void setModelSegments(const DocumentModelSegments &modelSegments);

  /// Return true if startup loading succeeded. If the loading failed then reasonForUnsuccessfulRed will explain why
  bool successfulRead () const;

  /// Update point ordinals after point addition/removal or dragging. See GraphicsScene::updatePointOrdinalsAfterDrag.
  /// Graph coordinates of point must be up to date
  void updatePointOrdinals (const Transformation &transformation);

private:
  Document ();

  bool bytesIndicatePreVersion6 (const QByteArray &bytes) const;
  Curve *curveForCurveName (const QString &curveName); // For use by Document only. External classes should use functors
  void generateEmptyPixmap(const QXmlStreamAttributes &attributes);
  void loadCurvesGraphs(QXmlStreamReader &reader);
  void loadImage(QXmlStreamReader &reader);
  void loadPostVersion5 (QXmlStreamReader &reader);
  void loadPreVersion6 (QDataStream &str);

  // Metadata
  QString m_name;
  QPixmap m_pixmap;

  // Read variables
  bool m_successfulRead;
  QString m_reasonForUnsuccessfulRead;

  // Curves
  Curve *m_curveAxes;
  CurvesGraphs m_curvesGraphs;

  // Model objects for the various settings
  DocumentModelAxesChecker m_modelAxesChecker;
  // DocumentModelColorFilter is not here since filtering settings are stored inside the Curve class
  DocumentModelCommon m_modelCommon;
  DocumentModelCoords m_modelCoords;
  // CurveStyles is not here since curve properties are stored inside the Curve class
  DocumentModelDigitizeCurve m_modelDigitizeCurve;
  DocumentModelExportFormat m_modelExport;
  DocumentModelGridRemoval m_modelGridRemoval;
  DocumentModelPointMatch m_modelPointMatch;
  DocumentModelSegments m_modelSegments;
};

#endif // DOCUMENT_H
