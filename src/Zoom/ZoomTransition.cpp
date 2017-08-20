
/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Logger.h"
#include <qmath.h>
#include "ZoomTransition.h"

const double CLOSER = qPow (2, 1.0 / 3.0);
const double FARTHER = 1.0 / CLOSER;

ZoomTransition::ZoomTransition ()
{
  m_zoomMapToFactor [ZOOM_16_TO_1] = 16.0;
  m_zoomMapToFactor [ZOOM_16_TO_1_FARTHER] = 16.0 * FARTHER;
  m_zoomMapToFactor [ZOOM_8_TO_1_CLOSER] = 8.0 * CLOSER;
  m_zoomMapToFactor [ZOOM_8_TO_1] = 8.0;
  m_zoomMapToFactor [ZOOM_8_TO_1_FARTHER] = 8.0 * FARTHER;
  m_zoomMapToFactor [ZOOM_4_TO_1_CLOSER] = 4.0 * CLOSER;
  m_zoomMapToFactor [ZOOM_4_TO_1] = 4.0;
  m_zoomMapToFactor [ZOOM_4_TO_1_FARTHER] = 4.0 * FARTHER;
  m_zoomMapToFactor [ZOOM_2_TO_1_CLOSER] = 2.0 * CLOSER;
  m_zoomMapToFactor [ZOOM_2_TO_1] = 2.0;
  m_zoomMapToFactor [ZOOM_2_TO_1_FARTHER] = 2.0 * FARTHER;
  m_zoomMapToFactor [ZOOM_1_TO_1_CLOSER] = 1.0 * CLOSER;
  m_zoomMapToFactor [ZOOM_1_TO_1] = 1.0;
  m_zoomMapToFactor [ZOOM_1_TO_1_FARTHER] = 1.0 * FARTHER;
  m_zoomMapToFactor [ZOOM_1_TO_2_CLOSER] = 0.5 * CLOSER;
  m_zoomMapToFactor [ZOOM_1_TO_2] = 0.5;
  m_zoomMapToFactor [ZOOM_1_TO_2_FARTHER] = 0.5 * FARTHER;
  m_zoomMapToFactor [ZOOM_1_TO_4_CLOSER] = 0.25 * CLOSER;
  m_zoomMapToFactor [ZOOM_1_TO_4] = 0.25;
  m_zoomMapToFactor [ZOOM_1_TO_4_FARTHER] = 0.25 * FARTHER;
  m_zoomMapToFactor [ZOOM_1_TO_8_CLOSER] = 0.125 * CLOSER;
  m_zoomMapToFactor [ZOOM_1_TO_8] = 0.125;
  m_zoomMapToFactor [ZOOM_1_TO_8_FARTHER] = 0.125 * FARTHER;
  m_zoomMapToFactor [ZOOM_1_TO_16_CLOSER] = 0.0625 * CLOSER;
  m_zoomMapToFactor [ZOOM_1_TO_16] = 0.0625;  
}

double ZoomTransition::mapToFactor (ZoomFactor zoomFactor) const
{
  ENGAUGE_ASSERT (m_zoomMapToFactor.contains (zoomFactor));

  return m_zoomMapToFactor [zoomFactor];
}

ZoomFactor ZoomTransition::zoomIn (ZoomFactor currentZoomFactor,
                                   double m11,
                                   double m22,
                                   bool actionZoomFillIsChecked) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ZoomTransition::zoomIn";

  // Try to zoom in
  ZoomFactor zoomFactorOld = currentZoomFactor;

  if (actionZoomFillIsChecked) {

    // Zooming in means user probably wants the more squished direction to be zoomed in by one step.
    // Loop through the zoom values until a match is found
    double xScale = m11;
    double yScale = m22;
    double scale = qMin(xScale, yScale); // Fit so large extent just fits

    for (int zoom = ZOOM_1_TO_16_CLOSER; zoom >= 0; zoom--) {
      ZoomFactor zoomFactor = (ZoomFactor) zoom;
      if (scale < m_zoomMapToFactor [zoomFactor]) {
        zoomFactorOld = zoomFactor;
        break;
      }
    }
  }

  ZoomFactor zoomFactorNew = ZOOM_16_TO_1;
  if (zoomFactorOld > ZOOM_16_TO_1) {
    zoomFactorNew = (ZoomFactor) (zoomFactorOld - 1);
  }

  return zoomFactorNew;
}

ZoomFactor ZoomTransition::zoomOut (ZoomFactor currentZoomFactor,
                                    double m11,
                                    double m22,
                                    bool actionZoomFillIsChecked) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ZoomTransition::zoomOut";

  // Try to zoom out
  ZoomFactor zoomFactorOld = currentZoomFactor;

  if (actionZoomFillIsChecked) {

    // Zooming out means user probably wants the less squished direction to be zoomed out by one step.
    // Loop through the zoom values until a match is found
    double xScale = m11;
    double yScale = m22;
    double scale = qMax(xScale, yScale); // Fit so larger extent just fits

    for (int zoom = 0; zoom <= ZOOM_1_TO_16_CLOSER; zoom++) {
      ZoomFactor zoomFactor = (ZoomFactor) zoom;
      if (scale > m_zoomMapToFactor [zoomFactor]) {
        zoomFactorOld = zoomFactor;
        break;
      }
    }
  }

  ZoomFactor zoomFactorNew = ZOOM_1_TO_16;
  if (zoomFactorOld < ZOOM_1_TO_16) {
    zoomFactorNew = (ZoomFactor) (zoomFactorOld + 1);
  }

  return zoomFactorNew;
}
