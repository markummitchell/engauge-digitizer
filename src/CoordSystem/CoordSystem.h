/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_SYSTEM_H
#define COORD_SYSTEM_H

#include "CoordSystemInterface.h"
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
#include <QStringList>
#include <QXmlStreamReader>

class Curve;
class QByteArray;
class QDataStream;
class QImage;
class QTransform;
class QXmlStreamReader;
class QXmlStreamWriter;
class Transformation;

/// Storage of data belonging to one coordinate system. There can be one or more coordinate systems per graph, and one or
/// more graphs in the image belonging to a Document
class CoordSystem : public CoordSystemInterface
{
public:
  /// Single constructor
  CoordSystem ();

  /// Constructor for opened Graphs, and error report files. The specified file is opened and read
  CoordSystem (const QString &fileName);

  virtual void addGraphCurveAtEnd (const QString &curveName);
  virtual void addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    QString &identifier,
                                                    double ordinal,
                                                    bool isXOnly);
  virtual void addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    const QString &identifier,
                                                    double ordinal,
                                                    bool isXOnly);
  virtual void addPointGraphWithGeneratedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     QString &generatedIentifier,
                                                     double ordinal);
  virtual void addPointGraphWithSpecifiedIdentifier (const QString &curveName,
                                                     const QPointF &posScreen,
                                                     const QString &identifier,
                                                     double ordinal);
  virtual void addPointsInCurvesGraphs (CurvesGraphs &curvesGraphs);
  virtual void checkAddPointAxis (const QPointF &posScreen,
                                  const QPointF &posGraph,
                                  bool &isError,
                                  QString &errorMessage,
                                  bool isXOnly,
                                  DocumentAxesPointsRequired documentAxesPointsRequired);
  virtual void checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage,
                                   DocumentAxesPointsRequired documentAxesPointsRequired);
  virtual const Curve &curveAxes () const;
  virtual Curve *curveForCurveName (const QString &curveName);
  virtual const Curve *curveForCurveName (const QString &curveName) const;
  virtual const CurvesGraphs &curvesGraphs () const;
  virtual QStringList curvesGraphsNames () const;
  virtual int curvesGraphsNumPoints (const QString &curveName) const;
  virtual void editPointAxis (const QPointF &posGraph,
                              const QString &identifier);
  virtual void editPointGraph (bool isX,
                               bool isY,
                               double x,
                               double y,
                               const QStringList &identifiers,
                               const Transformation &transformation);

  /// Return true if y coordinate is undefined, otherwise x coordinae is undefined in DOCUMENT_AXES_POINT_REQUIRE_4 mode.
  /// Applies to axes points only
  bool isXOnly (const QString &pointIdentifier) const;

  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual bool loadCurvesFile (const QString &curvesFile);

  /// Load from file in pre-version 6 format. Number of axes points is read in and passed to Document
  void loadPreVersion6 (QDataStream &str,
                        double version,
                        DocumentAxesPointsRequired &documentAxesPointsRequired);
  /// Load from file in version 6 format. Number of axes points is read in and passed to Document
  void loadVersion6 (QXmlStreamReader &reader,
                     DocumentAxesPointsRequired &documentAxesPointsRequired);
  /// Load from file in versions 7 and 8 formats. Number of axes points is already defined at Document level
  void loadVersions7AndUp (QXmlStreamReader &reader);

  virtual DocumentModelAxesChecker modelAxesChecker() const;
  virtual DocumentModelColorFilter modelColorFilter() const;
  virtual DocumentModelCoords modelCoords () const;
  virtual CurveStyles modelCurveStyles() const;
  virtual DocumentModelDigitizeCurve modelDigitizeCurve() const;
  virtual DocumentModelExportFormat modelExport() const;
  virtual DocumentModelGeneral modelGeneral() const;
  virtual DocumentModelGridDisplay modelGridDisplay() const;
  virtual DocumentModelGridRemoval modelGridRemoval() const;
  virtual DocumentModelPointMatch modelPointMatch() const;
  virtual DocumentModelSegments modelSegments() const;
  virtual void movePoint (const QString &pointIdentifier,
                          const QPointF &deltaScreen);
  virtual int nextOrdinalForCurve (const QString &curveName) const;
  virtual QPointF positionGraph (const QString &pointIdentifier) const;
  virtual QPointF positionScreen (const QString &pointIdentifier) const;
  virtual void print () const;
  virtual void printStream (QString indentation,
                            QTextStream &str) const;
  virtual QString reasonForUnsuccessfulRead () const;
  virtual void removePointAxis (const QString &identifier);
  virtual void removePointGraph (const QString &identifier);
  virtual void removePointsInCurvesGraphs (CurvesGraphs &curvesGraphs);
  virtual void saveXml (QXmlStreamWriter &writer) const;
  virtual QString selectedCurveName () const;
  virtual void setCurveAxes (const Curve &curveAxes);
  virtual void setCurvesGraphs (const CurvesGraphs &curvesGraphs);
  virtual void setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);
  virtual void setModelColorFilter(const DocumentModelColorFilter &modelColorFilter);
  virtual void setModelCoords (const DocumentModelCoords &modelCoords);
  virtual void setModelCurveStyles(const CurveStyles &modelCurveStyles);
  virtual void setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void setModelExport(const DocumentModelExportFormat &modelExport);
  virtual void setModelGeneral (const DocumentModelGeneral &modelGeneral);
  virtual void setModelGridDisplay(const DocumentModelGridDisplay &modelGridDisplay);
  virtual void setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);
  void setModelPointMatch(const DocumentModelPointMatch &modelPointMatch);
  virtual void setModelSegments(const DocumentModelSegments &modelSegments);
  virtual void setSelectedCurveName(const QString &selectedCurveName);
  virtual bool successfulRead () const;
  virtual void updatePointOrdinals (const Transformation &transformation);

private:

  bool bytesIndicatePreVersion6 (const QByteArray &bytes) const;
  void initializeUnsetGridRemovalFromGridDisplay (double version);
  void resetSelectedCurveNameIfNecessary ();

  // Read variables
  bool m_successfulRead;
  QString m_reasonForUnsuccessfulRead;

  // Curves
  Curve *m_curveAxes;
  CurvesGraphs m_curvesGraphs;

  // Model objects for the various settings
  DocumentModelAxesChecker m_modelAxesChecker;
  // DocumentModelColorFilter is not here since filtering settings are stored inside the Curve class
  DocumentModelCoords m_modelCoords;
  // CurveStyles is not here since curve properties are stored inside the Curve class
  DocumentModelDigitizeCurve m_modelDigitizeCurve;
  DocumentModelExportFormat m_modelExport;
  DocumentModelGeneral m_modelGeneral;
  DocumentModelGridDisplay m_modelGridDisplay;
  DocumentModelGridRemoval m_modelGridRemoval;
  DocumentModelPointMatch m_modelPointMatch;
  DocumentModelSegments m_modelSegments;

  // Each coordinate systems manages its own selected curve name
  QString m_selectedCurveName;
};

#endif // COORD_SYSTEM_H
