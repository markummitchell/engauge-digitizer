/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SCALE_BAR_H
#define SCALE_BAR_H

#include "DocumentModelSegments.h"
#include <QGraphicsLineItem>

class QGraphicsScene;

/// Scale bar that is defined as the line segment between two endpoints that are placed at the two ends of a
/// maps scale bar. The scale bar can be edited to set the scale bar length in graph coordinates
class ScaleBar : public QGraphicsLineItem
{
public:
  /// Single constructor.
  ScaleBar(QGraphicsScene &scene);
  ~ScaleBar();

private:
  ScaleBar();
};

#endif // SCALE_BAR_H
