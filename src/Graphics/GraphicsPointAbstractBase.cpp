#include "EngaugeAssert.h"
#include "GraphicsPointAbstractBase.h"

GraphicsPointAbstractBase::GraphicsPointAbstractBase() :
  m_lineWithPointAsStart (0),
  m_lineWithPointAsEnd (0)
{
}

GraphicsPointAbstractBase::~GraphicsPointAbstractBase()
{
}

void GraphicsPointAbstractBase::moveAttachedLines (const QPointF &pos)
{
  // shit
}

void GraphicsPointAbstractBase::reset ()
{
  m_lineWithPointAsEnd = 0;
  m_lineWithPointAsStart = 0;
}

void GraphicsPointAbstractBase::setLineStyle(const LineStyle &lineStyle)
{
  // If this is not the last point then it is bound to a line as the start point
  // shit
}

void GraphicsPointAbstractBase::setLineWithPointAsEnd (GraphicsLine *graphicsLine)
{
  m_lineWithPointAsEnd = graphicsLine;
}

void GraphicsPointAbstractBase::setLineWithPointAsStart (GraphicsLine *graphicsLine)
{
  m_lineWithPointAsStart = graphicsLine;
}
