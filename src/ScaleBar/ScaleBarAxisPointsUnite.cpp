/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackScaleBar.h"
#include "CmdMediator.h"
#include "Document.h"
#include "Logger.h"
#include <QVector>
#include "ScaleBarAxisPointsUnite.h"

ScaleBarAxisPointsUnite::ScaleBarAxisPointsUnite()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ScaleBarAxisPointsUnite::ScaleBarAxisPointsUnite";
}

ScaleBarAxisPointsUnite::~ScaleBarAxisPointsUnite()
{
}

QStringList ScaleBarAxisPointsUnite::axisPointIdentifiers (CmdMediator *cmdMediator) const
{
  CallbackScaleBar ftor;

  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackScaleBar::callback);
  cmdMediator->iterateThroughCurvePointsAxes (ftorWithCallback);

  return ftor.axisCurvePointIdentifiers ();
}

QStringList ScaleBarAxisPointsUnite::unite (CmdMediator *cmdMediator,
                                            const QStringList &pointIdentifiersIn) const
{
  const int AXIS_POINT_COUNT_IF_UNITING = 2;

  QStringList pointIdentifiersOut (pointIdentifiersIn);

  // Collect axis point identifiers
  QStringList axisIdentifiers = axisPointIdentifiers (cmdMediator);

  // Skip if not a map with scale bar
  if ((cmdMediator->document().documentAxesPointsRequired() == DOCUMENT_AXES_POINTS_REQUIRED_2) &&
      (axisIdentifiers.count () == AXIS_POINT_COUNT_IF_UNITING)) {

    // Calculate occurrence counts
    QVector<int> counts (AXIS_POINT_COUNT_IF_UNITING);
    for (int i = 0; i < AXIS_POINT_COUNT_IF_UNITING; i++) {
      counts [i] = 0;

      QStringList::const_iterator itr;
      for (itr = pointIdentifiersIn.begin (); itr != pointIdentifiersIn.end (); itr++) {
        QString pointIdentifier = *itr;

        if (axisIdentifiers [i] == pointIdentifier) {
          ++counts [i];
        }
      }
    }

    // Add in either of two cases
    if (counts [0] == 0 && counts [1] == 1) {
      // Add first
      pointIdentifiersOut << axisIdentifiers [0];
    } else if (counts [0] == 1 && counts [1] == 0) {
      // Add second
      pointIdentifiersOut << axisIdentifiers [1];
    }
  }

  return pointIdentifiersOut;
}
