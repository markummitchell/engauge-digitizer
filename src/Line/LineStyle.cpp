#include "LineStyle.h"

LineStyle::LineStyle (unsigned int width) :
  m_width (width)
{
}

QColor LineStyle::color () const
{
  return Qt::red;
}

unsigned int LineStyle::width () const
{
  return m_width;
}
