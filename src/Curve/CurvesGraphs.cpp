#include "Curve.h"
#include "CurvesGraphs.h"
#include "Point.h"
#include <QTextStream>
#include "Transformation.h"

CurvesGraphs::CurvesGraphs()
{
}

void CurvesGraphs::addGraphCurveAtEnd (Curve curve)
{
  m_curvesGraphs.push_back (curve);
}

void CurvesGraphs::addPoint (const Point &point)
{
  QString curveName = Point::curveNameFromPointIdentifier (point.identifier());

  Curve *curve = curveForCurveName (curveName);
  curve->addPoint (point);
}

void CurvesGraphs::applyTransformation (const Transformation &transformation)
{
  CurveList::iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    Curve &curve = *itr;
    curve.applyTransformation (transformation);
  }
}

Curve *CurvesGraphs::curveForCurveName (const QString &curveName)
{
  CurveList::iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    Curve &curve = *itr;
    if (curveName == curve.curveName ()) {
      return &curve;
    }
  }

  return 0;
}

const Curve *CurvesGraphs::curveForCurveName (const QString &curveName) const
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curveName == curve.curveName ()) {
      return &curve;
    }
  }

  return 0;
}

QStringList CurvesGraphs::curvesGraphsNames () const
{
  QStringList names;

  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    names << curve.curveName ();
  }

  return names;
}

int CurvesGraphs::curvesGraphsNumPoints (const QString &curveName) const
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curve.curveName () == curveName) {
      return curve.numPoints ();
    }
  }

  return 0;
}

void CurvesGraphs::exportToClipboard (const QStringList &selected,
                                      bool transformIsDefined,
                                      QTextStream &strCsv,
                                      QTextStream &strHtml,
                                      CurvesGraphs &curvesGraphs) const
{
  // For speed, build a hash as a fast lookup table
  QHash<QString, bool> selectedHash;
  QStringList::const_iterator itrH;
  for (itrH = selected.begin (); itrH != selected.end (); itrH++) {
    QString pointIdentifier = *itrH;
    selectedHash [pointIdentifier] = false;
  }

  // Export
  CurveList::const_iterator itrC;
  for (itrC = m_curvesGraphs.begin(); itrC != m_curvesGraphs.end (); itrC++) {

    const Curve &curve = *itrC;
    curve.exportToClipboard (selectedHash,
                             transformIsDefined,
                             strCsv,
                             strHtml,
                             curvesGraphs);
  }
}

void CurvesGraphs::iterateThroughCurvePoints (const QString &curveNameWanted,
                                              const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curve.curveName () == curveNameWanted) {

      curve.iterateThroughCurvePoints (ftorWithCallback);
      return;
    }
  }

  Q_ASSERT (false);
}

void CurvesGraphs::iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.iterateThroughCurvePoints (ftorWithCallback);
  }
}

int CurvesGraphs::numCurves () const
{
  return m_curvesGraphs.count ();
}

void CurvesGraphs::removePoint (const QString &pointIdentifier)
{
  QString curveName = Point::curveNameFromPointIdentifier(pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->removePoint (pointIdentifier);
}
