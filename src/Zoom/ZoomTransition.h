/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ZOOM_TRANSITION_H
#define ZOOM_TRANSITION_H

#include <QMap>
#include "ZoomFactor.h"

/// Perform calculations to determine the next zoom setting given the current zoom setting, when zooming in or out
class ZoomTransition
{
public:
  /// Single constructor.
  ZoomTransition ();

  /// Return the floating precision zoom factor given the enum value
  double mapToFactor (ZoomFactor zoomFactor) const;
  
  /// Zoom in
  ZoomFactor zoomIn (ZoomFactor currentZoomFactor,
                     double m11,
                     double m22,
                     bool actionZoomFillIsChecked) const;

  /// Zoom out
  ZoomFactor zoomOut (ZoomFactor currentZoomFactor,
                      double m11,
                      double m22,
                      bool actionZoomFillIsChecked) const;

private:
  QMap<ZoomFactor, double> m_zoomMapToFactor;
};

#endif // ZOOM_TRANSITION_H
