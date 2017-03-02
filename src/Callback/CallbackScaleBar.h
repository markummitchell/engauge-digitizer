/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_SCALE_BAR_H
#define CALLBACK_SCALE_BAR_H

#include "CallbackSearchReturn.h"
#include <QString>
#include <QStringList>

class Point;

/// Callback for identifying, for the scale bar of a map, various quantities
class CallbackScaleBar
{
public:
  /// Single constructor.
  CallbackScaleBar();

  /// Points in axis curve
  QStringList axisCurvePointIdentifiers () const;
 
  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);
  
  /// Length of scale bar
  double scaleBarLength () const;
  
  /// Identified axis point
  QString scaleBarPointIdentifier () const;

private:

  double m_scaleBarLength;
  QString m_scaleBarPointIdentifier;
  QStringList m_axisCurvePointIdentifiers;
};

#endif // CALLBACK_SCALE_BAR_H
