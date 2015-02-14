#include "EnumsToQt.h"
#include "GraphicsLine.h"
#include "LineStyle.h"
#include <QLineF>
#include <QPen>

GraphicsLine::GraphicsLine(const LineStyle &lineStyle) :
  m_wanted (true)
{
  // Line pen is set here. The line geometry is set later, after the constructor has finished
  QColor color (ColorPaletteToQColor (lineStyle.paletteColor ()));
  unsigned int width = lineStyle.width ();

  QPen pen (QBrush (color),
            width);
  setPen (pen);
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

void GraphicsLine::setWanted (bool wanted)
{
  m_wanted = wanted;
}

bool GraphicsLine::wanted () const
{
  return m_wanted;
}
