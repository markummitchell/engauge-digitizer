/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_NEXT_ORDINAL_H
#define CALLBACK_NEXT_ORDINAL_H

#include "CallbackSearchReturn.h"
#include <QPointF>
#include <QString>

class Point;

/// Callback for computing the next ordinal for a new point
class CallbackNextOrdinal
{
public:
  /// Single constructor
  CallbackNextOrdinal(const QString &curveName);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Computed next ordinal
  double nextOrdinal () const;

private:
  CallbackNextOrdinal();

  QString m_curveName;
  double m_maxOrdinalUsed;
};

#endif // CALLBACK_NEXT_ORDINAL_H
