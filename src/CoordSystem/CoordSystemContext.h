#ifndef COORD_SYSTEM_CONTEXT_H
#define COORD_SYSTEM_CONTEXT_H

#include "CoordSystem.h"
#include "CoordSystemInterface.h"

/// This class plays the role of context class in a state machine, although the 'states' are actually different
/// instantiations of the CoordSystem class. At any point in time, one CoordSystem is active (as selected by the user)
class CoordSystemContext : public CoordSystemInterface
{
 public:
  /// Single constructor
  CoordSystemContext();
  ~CoordSystemContext();

  virtual void addGraphCurveAtEnd (const QString &curveName);
  virtual void addPointAxisWithGeneratedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    QString &identifier,
                                                    double ordinal);
  virtual void addPointAxisWithSpecifiedIdentifier (const QPointF &posScreen,
                                                    const QPointF &posGraph,
                                                    const QString &identifier,
                                                    double ordinal);
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
                                  QString &errorMessage);
  virtual void checkEditPointAxis (const QString &pointIdentifier,
                                   const QPointF &posScreen,
                                   const QPointF &posGraph,
                                   bool &isError,
                                   QString &errorMessage);

  /// Current CoordSystem
  const CoordSystem &coordSystem () const;

  virtual const Curve &curveAxes () const;
  virtual Curve *curveForCurveName (const QString &curveName);
  virtual const Curve *curveForCurveName (const QString &curveName) const;
  virtual const CurvesGraphs &curvesGraphs () const;
  virtual QStringList curvesGraphsNames () const;
  virtual int curvesGraphsNumPoints (const QString &curveName) const;
  virtual void editPointAxis (const QPointF &posGraph,
                              const QString &identifier);
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvePointsAxes (const Functor2wRet<const QString  &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurveSegments (const QString &curveName,
                                            const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);
  virtual void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;
  virtual bool loadCurvesFile (const QString &curvesFile);
  virtual DocumentModelAxesChecker modelAxesChecker() const;
  virtual DocumentModelColorFilter modelColorFilter() const;
  virtual DocumentModelCoords modelCoords () const;
  virtual CurveStyles modelCurveStyles() const;
  virtual DocumentModelDigitizeCurve modelDigitizeCurve() const;
  virtual DocumentModelExportFormat modelExport() const;
  virtual DocumentModelGeneral modelGeneral() const;
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
  virtual void setCurvesGraphs (const CurvesGraphs &curvesGraphs);
  virtual void setModelAxesChecker(const DocumentModelAxesChecker &modelAxesChecker);
  virtual void setModelColorFilter(const DocumentModelColorFilter &modelColorFilter);
  virtual void setModelCoords (const DocumentModelCoords &modelCoords);
  virtual void setModelCurveStyles(const CurveStyles &modelCurveStyles);
  virtual void setModelDigitizeCurve (const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void setModelExport(const DocumentModelExportFormat &modelExport);
  virtual void setModelGeneral (const DocumentModelGeneral &modelGeneral);
  virtual void setModelGridRemoval(const DocumentModelGridRemoval &modelGridRemoval);
  void setModelPointMatch(const DocumentModelPointMatch &modelPointMatch);
  virtual void setModelSegments(const DocumentModelSegments &modelSegments);
  virtual bool successfulRead () const;
  virtual void updatePointOrdinals (const Transformation &transformation);

 private:

  CoordSystem m_coordSystem;

};

#endif // COORD_SYSTEM_CONTEXT_H
