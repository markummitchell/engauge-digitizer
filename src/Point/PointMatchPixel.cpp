/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PointMatchPixel.h"

PointMatchPixel::PointMatchPixel (int xOffset,
                                  int yOffset,
                                  bool pixelIsOn) :
  m_posOffset (xOffset, yOffset),
  m_pixelIsOn (pixelIsOn)
{
}

PointMatchPixel::PointMatchPixel (const PointMatchPixel &other) :
  m_posOffset (other.xOffset(),
               other.yOffset()),
  m_pixelIsOn (other.pixelIsOn ())
{
}

PointMatchPixel &PointMatchPixel::operator= (const PointMatchPixel &other)
{
  m_posOffset = QPoint (other.xOffset(),
                        other.yOffset());
  m_pixelIsOn = other.pixelIsOn();

  return *this;
}

bool PointMatchPixel::pixelIsOn () const
{
  return m_pixelIsOn;
}

int PointMatchPixel::xOffset () const
{
  return m_posOffset.x();
}

int PointMatchPixel::yOffset () const
{
  return m_posOffset.y();
}
