#include "EnumsToQt.h"
#include "GraphicsLine.h"
#include "LineStyle.h"
#include "Logger.h"
#include <QLineF>
#include <QPen>

GraphicsLine::GraphicsLine(double ordinalAssociated,
                           double ordinalOther) :
  m_ordinalAssociated (ordinalAssociated),
  m_ordinalOther (ordinalOther),
  m_wanted (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLine::GraphicsLine"
                              << " ordinalAssociated=" << ordinalAssociated
                              << " ordinalOther=" << ordinalOther;
}

void GraphicsLine::moveStart (const QPointF &pos)
{
  QLineF newLine (pos,
                  line().p2 ());

  setLine (newLine);
}

void GraphicsLine::moveEnd (const QPointF &pos)
{
  QLineF newLine (line().p1 (),
                  pos);

  setLine (newLine);
}

void GraphicsLine::setLineStyle (const LineStyle &lineStyle)
{
  // Line pen is set here. The line geometry is set later, after the constructor has finished
  QColor color (ColorPaletteToQColor (lineStyle.paletteColor ()));
  unsigned int width = lineStyle.width ();

  QPen pen (QBrush (color),
            width);
  setPen (pen);
}

void GraphicsLine::setWanted (bool wanted)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsLine::setWanted"
                               << " ordinalAssociated=" << m_ordinalAssociated
                               << " ordinalOther=" << m_ordinalOther
                               << " wanted=" << (wanted ? "true" : "false");

  m_wanted = wanted;
}

bool GraphicsLine::wanted () const
{
  return m_wanted;
}
