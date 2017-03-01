/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "CoordSystemContext.h"
#include "CoordSystemIndex.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DocumentAxesPointsRequired.h"
#include "DocumentModelAxesChecker.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelCoords.h"
#include "DocumentModelDigitizeCurve.h"
#include "DocumentModelExportFormat.h"
#include "DocumentModelGeneral.h"
#include "DocumentModelGridDisplay.h"
#include "DocumentModelGridRemoval.h"
#include "DocumentModelPointMatch.h"
#include "DocumentModelSegments.h"
#include "PointStyle.h"
#include <QList>
#include <QPixmap>
#include <QString>
#include <QXmlStreamReader>

class CoordSystem;
class Curve;
class QByteArray;
class QFile;
class QImage;
class QTransform;
class QXmlStreamWriter;
class Transformation;

/// Storage of one imported image and the data attached to that image
class Document
{
public:
  /// Constructor for imported images and dragged images. Only one coordinate system is create - others are added later externally
  Document (const QImage &image);

  /// Constructor for opened Documents, and error report files. The specified file is opened and read.
  Document (const QString &fileName);

  /// Add some number (0 or more) of additional coordinate systems. This is only safe to call during import
  /// and before any changes have been made to the Document
  void addCoordSystems(unsigned int numberCoordSystemToAdd);

  /// Add new graph curve to the list of existing graph curves.
  void addGraphCurveAtEnd (const QString &curveName);

  /// Add a single axis point with a generated point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  /// \param isXOnly True if point has only an x coordinate
  void addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            QString &identifier,
                                            double ordinal,
                                            bool isXOnly);

  /// Add a single axis point with the specified point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  /// \param isXOnly True if point has only an x coordinate
  void addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                            const QPointF &posGraph,
                                            const QString &identifier,
                                            double ordinal,
                                            bool isXOnly);

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

  /// Add scale with a generated point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen0 Screen coordinates of first point from QGraphicsView
  /// \param posScreen1 Screen coordinates of second point from QGraphicsView
  /// \param scaleLength Scale bar length in graph coordinates
  /// \param identifier0 Identifier for first new axis point
  /// \param identifier1 Identifier for second new axis point
  /// \param ordinal0 Unique, for curve, ordinal number of first point
  /// \param ordinal1 Unique, for curve, ordinal number of second point
  void addScaleWithGeneratedIdentifier (const QPointF &posScreen0,
                                        const QPointF &posScreen1,
                                        double scaleLength,
                                        QString &identifier0,
                                        QString &identifier1,
                                        double ordinal0,
                                        double ordinal1);

  /// Check before calling addPointAxis. Also returns the next available ordinal number (to prevent clashes)
  void checkAddPointAxis (const QPointF &posScreen,
                          const QPointF &posGraph,
                          bool &isError,
                          QString &errorMessage,
                          bool isXOnly);

  /// Check before calling editPointAxis
  void checkEditPointAxis (const QString &pointIdentifier,
                           const QPointF &posScreen,
                           const QPointF &posGraph,
                           bool &isError,
                           QString &errorMessage);

  /// Currently active CoordSystem
  const CoordSystem &coordSystem() const;

  /// Number of CoordSystem
  unsigned int coordSystemCount() const;

  /// Index of current active CoordSystem
  CoordSystemIndex coordSystemIndex() const;

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

  /// Get method for DocumentAxesPointsRequired
  DocumentAxesPointsRequired documentAxesPointsRequired () const;

  /// Edit the graph coordinates of a single axis point. Call this after checkAddPointAxis to guarantee success in this call
  void editPointAxis (const QPointF &posGraph,
                      const QString &identifier);

  /// Edit the graph coordinates of one or more graph points
  void editPointGraph (bool isX,
                       bool isY,
                       double x,
                       double y,
                       const QStringList &identifiers,
                       const Transformation &transformation);

  /// Initialize grid display. This is called immediately after the transformation has been defined for the first time
  void initializeGridDisplay (const Transformation &transformation);

  /// See Curve::isXOnly
  bool isXOnly (const QString &pointIdentifier) const;

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

  /// Load the curve names in the specified Engauge file into the current document. This is called near the end of the import process only
  bool loadCurvesFile (const QString &curvesFile);

  /// Get method for DocumentModelAxesChecker.
  DocumentModelAxesChecker modelAxesChecker() const;

  /// Get method for DocumentModelColorFilter.
  DocumentModelColorFilter modelColorFilter() const;

  /// Get method for DocumentModelCoords.
  DocumentModelCoords modelCoords () const;

  /// Get method for CurveStyles.
  CurveStyles modelCurveStyles() const;

  /// Get method for DocumentModelDigitizeCurve.
  DocumentModelDigitizeCurve modelDigitizeCurve() const;

  /// Get method for DocumentModelExportFormat.
  DocumentModelExportFormat modelExport() const;

  /// Get method for DocumentModelGeneral.
  DocumentModelGeneral modelGeneral() const;

  /// Get method for DocumentModelGridDisplay.
  DocumentModelGridDisplay modelGridDisplay() const;

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

  /// Currently selected curve name. This is used to set the selected curve combobox in MainWindow
  QString selectedCurveName () const;

  /// Set the index of current active CoordSystem
  void setCoordSystemIndex(CoordSystemIndex coordSystemIndex);

  /// Let CmdAbstract classes overwrite axes Curve.
  void setCurveAxes (const Curve &curveAxes);

  /// Let CmdAbstract classes overwrite CurvesGraphs.
  void setCurvesGraphs (const CurvesGraphs &curvesGraphs);

  /// Set the number of axes points required. This is called during the Document creation process, after imported images have
  /// been previewed or loaded files have had at least some xml parsing
  void setDocumentAxesPointsRequired (DocumentAxesPointsRequired documentAxesPointsRequired);

  /// Set method for DocumentModelAxesChecker.
  void setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);

  /// Set method for DocumentModelColorFilter.
  void setModelColorFilter(const DocumentModelColorFilter &modelColorFilter);

  /// Set method for DocumentModelCoords.
  void setModelCoords (const DocumentModelCoords &modelCoords);

  /// Set method for CurveStyles.
  void setModelCurveStyles(const CurveStyles &modelCurveStyles);

  /// Set method for DocumentModelDigitizeCurve.
  void setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);

  /// Set method for DocumentModelExportFormat.
  void setModelExport(const DocumentModelExportFormat &modelExport);

  /// Set method for DocumentModelGeneral.
  void setModelGeneral (const DocumentModelGeneral &modelGeneral);

  /// Set method for DocumentModelGridDisplay.
  void setModelGridDisplay(const DocumentModelGridDisplay &modelGridDisplay);

  /// Set method for DocumentModelGridRemoval.
  void setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);

  /// Set method for DocumentModelPointMatch.
  void setModelPointMatch(const DocumentModelPointMatch &modelPointMatch);

  /// Set method for DocumentModelSegments.
  void setModelSegments(const DocumentModelSegments &modelSegments);

  /// Set method for the background pixmap
  void setPixmap (const QImage &image);

  /// Save curve name that is selected for the current coordinate system, for the next time the coordinate system reappears
  void setSelectedCurveName (const QString &selectedCurveName);

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
  void loadImage(QXmlStreamReader &reader);
  void loadPreVersion6 (QDataStream &str);
  void loadVersion6 (QFile *file);
  void loadVersions7AndUp (QFile *file);
  void overrideGraphDefaultsWithMapDefaults ();
  int versionFromFile (QFile *file) const;

  // Metadata
  QString m_name;
  QPixmap m_pixmap;

  // Number of axes points used is set during creation/import
  DocumentAxesPointsRequired m_documentAxesPointsRequired;

  // Read variables
  bool m_successfulRead;
  QString m_reasonForUnsuccessfulRead;

  CoordSystemContext m_coordSystemContext;
};

#endif // DOCUMENT_H
