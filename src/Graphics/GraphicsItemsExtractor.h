/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ITEMS_EXTRACTOR_H
#define GRAPHICS_ITEMS_EXTRACTOR_H

#include <QStringList>

class QGraphicsItem;

enum AxisOrGraph {
  AXIS_POINTS,
  GRAPH_POINTS
};

/// This class consolidates utility routines that deal with graphics items that are getting extracted from the scene
class GraphicsItemsExtractor
{
public:
  /// Single constructor
  GraphicsItemsExtractor();
  ~GraphicsItemsExtractor();

  /// Return true if all selected points are of the specified axis or graph type
  bool allSelectedItemsAreEitherAxisOrGraph (const QList<QGraphicsItem*> &items,
                                             AxisOrGraph axisOrGraph) const;

  /// Return list of selected point identifiers
  QStringList selectedPointIdentifiers (const QList<QGraphicsItem*> &items) const;
  
};

#endif // GRAPHICS_ITEMS_EXTRACTOR_H
