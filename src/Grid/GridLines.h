#ifndef GRID_LINES_H
#define GRID_LINES_H

#include "GridLine.h"
#include <QList>

class QPen;

typedef QList<GridLine*> GridLinesContainer;

/// Container class for GridLine objects
class GridLines
{
 public:
  /// Single constructor
  GridLines();

  /// Add specified grid line. Ownership of all allocated QGraphicsItems is passed to new GridLine
  void add (GridLine *gridLine);

  /// Deallocate and remove all grid lines
  void clear ();

  /// Set the pen style of each grid line
  void setPen (const QPen &pen);

  /// Make all grid lines visible or hidden
  void setVisible (bool visible);

 private:

  GridLinesContainer m_gridLinesContainer;

};

#endif // GRID_LINES_H
