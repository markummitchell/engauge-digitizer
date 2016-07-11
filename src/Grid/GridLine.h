/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LINE_H
#define GRID_LINE_H

#include <QList>

class QGraphicsItem;
class QGraphicsScene;
class QPen;

typedef QList<QGraphicsItem *> SegmentContainer;

/// Single grid line drawn a straight or curved line. This is expected to be composed of QGraphicsEllipseItem and 
/// QGraphicsLineItem objects
class GridLine
{
public:
  /// Default constructor for storage in containers
  GridLine ();
  virtual ~GridLine ();

  /// Copy constructor. This will assert if called since copying of pointer containers is problematic
  GridLine (const GridLine &other);

  /// Assignment constructor. This will assert if called since copying of pointer containers is problematic
  GridLine &operator= (GridLine &other);

  /// Add graphics item which represents one segment of the line
  void add (QGraphicsItem *item);

  /// Set the pen style
  void setPen (const QPen &pen);

  /// Set each grid line as visible or hidden
  void setVisible (bool visible);

private:

  SegmentContainer m_segments;
};

#endif // GRID_LINE_H
