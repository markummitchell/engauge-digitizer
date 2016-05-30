/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COORD_SYSTEM_CONTEXT_H
#define COORD_SYSTEM_CONTEXT_H

#include "CoordSystem.h"
#include "CoordSystemIndex.h"
#include "CoordSystemInterface.h"
#include "DocumentAxesPointsRequired.h"
#include <QVector>

class QDataStream;
class QXmlStreamReader;
class QXmlStreamWriter;

typedef QVector<CoordSystem*> CoordSystems;

/// This class plays the role of context class in a state machine, although the 'states' are actually different
/// instantiations of the CoordSystem class. At any point in time, one CoordSystem is active (as selected by the user)
class CoordSystemContext : public CoordSystemInterface
{
 public:
  /// Default constructor for constructing from opened file
  CoordSystemContext();

  ~CoordSystemContext();

  /// Add specified number of coordinate systems to the original one created by the constructor
  void addCoordSystems(DocumentAxesPointsRequired documentAxesPointsRequired,
                       unsigned int numberCoordSystemToAdd);

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
                                  bool isXOnly);
  virtual void checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage);

  /// Current CoordSystem
  const CoordSystem &coordSystem () const;

  /// Number of CoordSystem
  unsigned int coordSystemCount() const;

  /// Index of current CoordSystem
  CoordSystemIndex coordSystemIndex () const;

  virtual const Curve &curveAxes () const;
  virtual Curve *curveForCurveName (const QString &curveName);
  virtual const Curve *curveForCurveName (const QString &curveName) const;
  virtual const CurvesGraphs &curvesGraphs () const;
  virtual QStringList curvesGraphsNames () const;
  virtual int curvesGraphsNumPoints (const QString &curveName) const;
  virtual void editPointAxis (const QPointF &posGraph,
                              const QString &identifier);

  /// True/false if y/x value is empty
  bool isXOnly (const QString &pointIdentifier) const;

  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual bool loadCurvesFile (const QString &curvesFile);

  /// Load from file in pre-version 6 format
  void loadPreVersion6 (QDataStream &str,
                        double version);
  /// Load from file in version 6 format, into the single CoordSystem
  void loadVersion6 (QXmlStreamReader &reader);
  /// Load one CoordSystem from file in version 7 format or newer, into the most recent CoordSystem which was just created before
  /// the call to this method
  void loadVersions7AndUp (QXmlStreamReader &reader,
                           DocumentAxesPointsRequired documentAxesPointsRequired);

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

  /// Index of current CoordSystem
  void setCoordSystemIndex (CoordSystemIndex coordSystemIndex);

  virtual void setCurveAxes (const Curve &curveAxes);
  virtual void setCurvesGraphs (const CurvesGraphs &curvesGraphs); // Applies to current coordinate system
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

  CoordSystemIndex m_coordSystemIndex;
  CoordSystems m_coordSystems;

};

#endif // COORD_SYSTEM_CONTEXT_H
