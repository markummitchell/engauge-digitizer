#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "CurvesGraphs.h"
#include "DlgModelCoords.h"
#include "DlgModelCurveProperties.h"
#include "DlgModelExport.h"
#include "DlgModelFilter.h"
#include "DlgModelGridDisplay.h"
#include "DlgModelGridRemoval.h"
#include "DlgModelPointMatch.h"
#include "DlgModelSegments.h"
#include "PointStyle.h"
#include <QList>
#include <QPixmap>
#include <QString>

class Curve;
class QImage;
class QTransform;

/// Storage of one imported image and the data attached to that image
class Document
{
public:
  /// Constructor for imported images and dragged images
  Document (const QImage &image);

  /// Constructor for opened Documents. The specified file is opened and read
  Document (const QString &fileName);

  /// Add new graph curve to the list of existing graph curves.
  void addGraphCurveAtEnd (const QString &curveName);

  /// Add a single axis point with a generated point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  void addPointAxis (const QPointF &posScreen,
                     const QPointF &posGraph,
                     QString &identifier);

  /// Add a single axis point with the specified point identifier. Call this after checkAddPointAxis to guarantee success in this call.
  /// \param posScreen Screen coordinates from QGraphicsView
  /// \param posGraph Graph coordiantes from user
  /// \param identifier Identifier for new axis point
  void addPointAxis (const QPointF &posScreen,
                     const QPointF &posGraph,
                     const QString &identifier);

  /// Add a single graph point with a generated point identifier.
  void addPointGraph (const QString &curveName,
                      const QPointF &posScreen,
                      QString &identifier);

  /// Add a single graph point with the specified point identifer. Note that PointStyle is not applied to the point within the Document.
  void addPointGraph (const QString &curveName,
                      const QPointF &posScreen,
                      const QString &identifier);

  /// Add all points identified in the specified CurvesGraphs. See also removePointsInCurvesGraphs
  void addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs);

  /// See CurvesGraphs::applyTransformation.
  void applyTransformation (const Transformation &transformation);

  /// Check before calling addPointAxis.
  void checkAddPointAxis (const QPointF &posScreen,
                          const QPointF &posGraph,
                          bool &isError,
                          QString &errorMessage);

  /// Check before calling editPointAxis.
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

  /// Get method for DlgModelCoords.
  DlgModelCoords modelCoords () const;

  /// Get method for DlgModelCurveProperties.
  DlgModelCurveProperties modelCurveProperties() const;

  /// Get method for DlgModelExport.
  DlgModelExport modelExport() const;

  /// Get method for DlgModelFilter.
  DlgModelFilter modelFilter() const;

  /// Get method for DlgModelGridDisplay.
  DlgModelGridDisplay modelGridDisplay() const;

  /// Get method for DlgModelGridRemoval.
  DlgModelGridRemoval modelGridRemoval() const;

  /// Get method for DlgModelPointMatch.
  DlgModelPointMatch modelPointMatch() const;

  /// Get method for DlgModelSegments.
  DlgModelSegments modelSegments() const;

  /// Edit the graph coordinates of a single axis point. Call this after checkAddPointAxis to guarantee success in this call
  void editPointAxis (const QPointF &posGraph,
                      const QString &identifier);

  /// See CurvesGraphs::exportToClipboard
  void exportToClipboard (const QStringList &selected,
                          bool transformIsDefined,
                          QTextStream &strCsv,
                          QTextStream &strHtml,
                          CurvesGraphs &curvesGraphs) const;

  /// Return true if Document has changed since last time file was saved.
  bool isModified () const;

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Curve::iterateThroughCurvePoints, for the axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Curve::movePoint
  void movePoint (const QString &pointIdentifier,
                  const QPointF &deltaScreen);

  /// Return the image that is being digitized.
  QPixmap pixmap () const;

  /// See Curve::positionGraph.
  QPointF positionGraph (const QString &pointIdentifier) const;

  /// See Curve::positionScreen.
  QPointF positionScreen (const QString &pointIdentifier) const;

  /// Return an informative text message explaining why startup loading failed. Applies if successfulRead returns false
  QString reasonForUnsuccessfulRead () const;

  /// Perform the opposite of addPointAxis.
  void removePointAxis (const QString &identifier);

  /// Perform the opposite of addPointGraph.
  void removePointGraph (const QString &identifier);

  /// Remove all points identified in the specified CurvesGraphs. See also addPointsInCurvesGraphs
  void removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs);

  /// Let CmdAbstract classes overwrite CurvesGraphs.
  void setCurvesGraphs (const CurvesGraphs &curvesGraphs);

  /// Set method for DlgModelCoords.
  void setModelCoords (const DlgModelCoords &modelCoords);

  /// Set method for DlgModelCurveProperties.
  void setModelCurveProperties(const DlgModelCurveProperties &modelCurveProperties);

  /// Set method for DlgModelExport.
  void setModelExport(const DlgModelExport &modelExport);

  /// Set method for DlgModelFilter.
  void setModelFilter(const DlgModelFilter &modelFilter);

  /// Set method for DlgModelGridDisplay.
  void setModelGridDisplay(const DlgModelGridDisplay &modelGridDisplay);

  /// Set method for DlgModelGridRemoval.
  void setModelGridRemoval(const DlgModelGridRemoval &modelGridRemoval);

  /// Set method for DlgModelPointMatch.
  void setModelPointMatch(const DlgModelPointMatch &modelPointMatch);

  /// Set method for DlgModelSegments.
  void setModelSegments(const DlgModelSegments &modelSegments);

  /// Return true if startup loading succeeded. If the loading failed then reasonForUnsuccessfulRed will explain why
  bool successfulRead () const;

private:
  Document ();

  Curve *curveForCurveName (const QString &curveName); // For use by Document only. External classes should use functors

  QString m_name;
  QPixmap m_pixmap;

  bool m_successfulRead;
  QString m_reasonForUnsuccessfulRead;

  bool m_isModified;

  Curve *m_curveAxes;
  CurvesGraphs m_curvesGraphs;

  DlgModelCoords m_modelCoords;
  DlgModelCurveProperties m_modelCurveProperties;
  DlgModelExport m_modelExport;
  DlgModelFilter m_modelFilter;
  DlgModelGridDisplay m_modelGridDisplay;
  DlgModelGridRemoval m_modelGridRemoval;
  DlgModelPointMatch m_modelPointMatch;
  DlgModelSegments m_modelSegments;
};

#endif // DOCUMENT_H
