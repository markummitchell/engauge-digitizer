/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridLines.h"
#include <QPen>

GridLines::GridLines()
{
}

void GridLines::add (GridLine *gridLine)
{
  m_gridLinesContainer.push_back (gridLine);
}

void GridLines::clear ()
{
  for (int i = 0; i < m_gridLinesContainer.count(); i++) {
    GridLine *gridLine = m_gridLinesContainer [i];
    if (gridLine != 0) {
      delete gridLine;
    }
  }

  m_gridLinesContainer.clear();
}

void GridLines::setPen (const QPen &pen)
{
  for (int i = 0; i < m_gridLinesContainer.count(); i++) {
    m_gridLinesContainer [i]->setPen (pen);
  }
}

void GridLines::setVisible (bool visible)
{
  for (int i = 0; i < m_gridLinesContainer.count(); i++) {
    m_gridLinesContainer [i]->setVisible (visible);
  }
}
