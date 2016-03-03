/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_SYSTEM_INTERFACE_H
#define COORD_SYSTEM_INTERFACE_H

#include "CallbackSearchReturn.h"
#include "CurveStyles.h"
#include "DocumentModelAxesChecker.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelCoords.h"
#include "DocumentModelDigitizeCurve.h"
#include "DocumentModelExportFormat.h"
#include "DocumentModelGeneral.h"
#include "DocumentModelGridRemoval.h"
#include "DocumentModelPointMatch.h"
#include "DocumentModelSegments.h"
#include "functor.h"
#include "Point.h"

class Curve;
class CurvesGraphs;
class QPointF;
class QString;
class QStringList;
class Transformation;

/// Interface common to CoordSystemContext and CoordSystem classes
class CoordSystemInterface
{
public:
  /// Single constructor
  CoordSystemInterface ();
  virtual ~CoordSystemInterface ();

  /// Add new graph curve to the list of existing graph curves.
  virtual void addGraphCurveAtEnd (const QString &curveName) = 0;

  /// Add a single axis point with a generated point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  /// \param isXOnly True if graph coordinates have only x coordinate
  virtual void addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    QString &identifier,
                                                    double ordinal,
                                                    bool isXOnly) = 0;

  /// Add a single axis point with the specified point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  /// \param ordinal Unique, for curve, ordinal number
  /// \param isXOnly True if graph coordinates have only x coordinate
  virtual void addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    const QString &identifier,
                                                    double ordinal,
                                                    bool isXOnly) = 0;

  /// Add a single graph point with a generated point identifier.
  virtual void addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     QString &generatedIentifier,
                                                     double ordinal) = 0;

  /// Add a single graph point with the specified point identifer. Note that PointStyle is not applied to the point within the Graph.
  virtual void addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     const QString &identifier,
                                                     double ordinal) = 0;

  /// Add all points identified in the specified CurvesGraphs. See also removePointsInCurvesGraphs
  virtual void addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs) = 0;

  /// Check before calling addPointAxis. Also returns the next available ordinal number (to prevent clashes)
  virtual void checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage,
                                  bool isXOnly) = 0;

  /// Check before calling editPointAxis
  virtual void checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage) = 0;

  /// Get method for axis curve.
  virtual const Curve &curveAxes () const = 0;

  /// See CurvesGraphs::curveForCurveName, although this also works for AXIS_CURVE_NAME.
  virtual Curve *curveForCurveName (const QString &curveName) = 0;

  /// See CurvesGraphs::curveForCurveNames, although this also works for AXIS_CURVE_NAME.
  virtual const Curve *curveForCurveName (const QString &curveName) const = 0;

  /// Make all Curves available, read only, for CmdAbstract classes only.
  virtual const CurvesGraphs &curvesGraphs () const = 0;

  /// See CurvesGraphs::curvesGraphsNames.
  virtual QStringList curvesGraphsNames () const = 0;

  /// See CurvesGraphs::curvesGraphsNumPoints.
  virtual int curvesGraphsNumPoints (const QString &curveName) const = 0;

  /// Edit the graph coordinates of a single axis point. Call this after checkAddPointAxis to guarantee success in this call
  virtual void editPointAxis (const QPointF &posGraph,
                              const QString &identifier) = 0;

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) = 0;

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const = 0;

  /// See Curve::iterateThroughCurveSegments, for any axes or graph curve
  virtual void iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const = 0;

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) = 0;

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const = 0;

  /// Load the curve names in the specified Engauge file into the current graph. This is called near the end of the import process only
  virtual bool loadCurvesFile (const QString &curvesFile) = 0;

  /// Get method for DocumentModelAxesChecker.
  virtual DocumentModelAxesChecker modelAxesChecker() const = 0;

  /// Get method for DocumentModelColorFilter.
  virtual DocumentModelColorFilter modelColorFilter() const = 0;

  /// Get method for DocumentModelCoords.
  virtual DocumentModelCoords modelCoords () const = 0;

  /// Get method for CurveStyles.
  virtual CurveStyles modelCurveStyles() const = 0;

  /// Get method for DocumentModelDigitizeCurve.
  virtual DocumentModelDigitizeCurve modelDigitizeCurve() const = 0;

  /// Get method for DocumentModelExportFormat.
  virtual DocumentModelExportFormat modelExport() const = 0;

  /// Get method for DocumentModelGeneral.
  virtual DocumentModelGeneral modelGeneral() const = 0;

  /// Get method for DocumentModelGridRemoval.
  virtual DocumentModelGridRemoval modelGridRemoval() const = 0;

  /// Get method for DocumentModelPointMatch.
  virtual DocumentModelPointMatch modelPointMatch() const = 0;

  /// Get method for DocumentModelSegments.
  virtual DocumentModelSegments modelSegments() const = 0;

  /// See Curve::movePoint
  virtual void movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen) = 0;

  /// Default next ordinal value for specified curve
  virtual int nextOrdinalForCurve (const QString &curveName) const = 0;

  /// See Curve::positionGraph.
  virtual QPointF positionGraph (const QString &pointIdentifier) const = 0;

  /// See Curve::positionScreen.
  virtual QPointF positionScreen (const QString &pointIdentifier) const = 0;

  /// Debugging method for printing directly from symbolic debugger
  virtual void print () const = 0;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  virtual void printStream (QString indentation,
                            QTextStream &str) const = 0;

  /// Return an informative text message explaining why startup loading failed. Applies if successfulRead returns false
  virtual QString reasonForUnsuccessfulRead () const = 0;

  /// Perform the opposite of addPointAxis.
  virtual void removePointAxis (const QString &identifier) = 0;

  /// Perform the opposite of addPointGraph.
  virtual void removePointGraph (const QString &identifier) = 0;

  /// Remove all points identified in the specified CurvesGraphs. See also addPointsInCurvesGraphs
  virtual void removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs) = 0;

  /// Save graph to xml
  virtual void saveXml (QXmlStreamWriter &writer) const = 0;

  /// Let CmdAbstract classes overwrite CurvesGraphs.
  virtual void setCurvesGraphs (const CurvesGraphs &curvesGraphs) = 0;

  /// Set method for DocumentModelAxesChecker.
  virtual void setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker) = 0;

  /// Set method for DocumentModelColorFilter.
  virtual void setModelColorFilter(const DocumentModelColorFilter &modelColorFilter) = 0;

  /// Set method for DocumentModelCoords.
  virtual void setModelCoords (const DocumentModelCoords &modelCoords) = 0;

  /// Set method for CurveStyles.
  virtual void setModelCurveStyles(const CurveStyles &modelCurveStyles) = 0;

  /// Set method for DocumentModelDigitizeCurve.
  virtual void setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve) = 0;

  /// Set method for DocumentModelExportFormat.
  virtual void setModelExport(const DocumentModelExportFormat &modelExport) = 0;

  /// Set method for DocumentModelGeneral.
  virtual void setModelGeneral (const DocumentModelGeneral &modelGeneral) = 0;

  /// Set method for DocumentModelGridRemoval.
  virtual void setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval) = 0;

  /// Set method for DocumentModelPointMatch.
  virtual void setModelPointMatch(const DocumentModelPointMatch &modelPointMatch) = 0;

  /// Set method for DocumentModelSegments.
  virtual void setModelSegments(const DocumentModelSegments &modelSegments) = 0;

  /// Return true if startup loading succeeded. If the loading failed then reasonForUnsuccessfulRed will explain why
  virtual bool successfulRead () const = 0;

  /// Update point ordinals after point addition/removal or dragging. See GraphicsScene::updatePointOrdinalsAfterDrag.
  /// Graph coordinates of point must be up to date
  virtual void updatePointOrdinals (const Transformation &transformation) = 0;
};

#endif // COORD_SYSTEM_INTERFACE_H
