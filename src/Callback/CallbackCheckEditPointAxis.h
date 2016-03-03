/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_CHECK_EDIT_POINT_AXIS_H
#define CALLBACK_CHECK_EDIT_POINT_AXIS_H

#include "CallbackAxisPointsAbstract.h"
#include <QPointF>
#include <QString>

class DocumentModelCoords;
class Point;

/// Callback for sanity checking the screen and graph coordinates of an axis point that is in the axes curve, before changing its graph coordinates.
class CallbackCheckEditPointAxis : public CallbackAxisPointsAbstract
{
public:
  /// Single constructor.
  CallbackCheckEditPointAxis(const DocumentModelCoords &modelCoords,
                             const QString &pointIdentifier,
                             const QPointF &posScreen,
                             const QPointF &posGraph,
                             DocumentAxesPointsRequired documentAxesPointsRequired);

  /// True if an error occurred during iteration.
  bool isError () const;

  /// Error message that explains the problem indicated by isError.
  QString errorMessage () const;

private:
  CallbackCheckEditPointAxis();
};

#endif // CALLBACK_CHECK_EDIT_POINT_AXIS_H
