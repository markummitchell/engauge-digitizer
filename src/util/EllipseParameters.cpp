/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EllipseParameters.h"

EllipseParameters::EllipseParameters () :
  m_posCenter (QPointF (0, 0)),
  m_angleRadians (0),
  m_a (0),
  m_b (0)
{
}

EllipseParameters::EllipseParameters (const QPointF &posCenter,
                                      double angleRadians,
                                      double a,
                                      double b) :
  m_posCenter (posCenter),
  m_angleRadians (angleRadians),
  m_a (a),
  m_b (b)
{
}

EllipseParameters &EllipseParameters::operator= (const EllipseParameters &other)
{
  m_posCenter = other.posCenter();
  m_angleRadians = other.angleRadians();
  m_a = other.a ();
  m_b = other.b ();

  return *this;
}

EllipseParameters::EllipseParameters (const EllipseParameters &other) :
  m_posCenter (other.posCenter()),
  m_angleRadians (other.angleRadians()),
  m_a (other.a ()),
  m_b (other.b ())
{
}
EllipseParameters::~EllipseParameters()
{
}

double EllipseParameters::a () const
{
  return m_a;
}

double EllipseParameters::angleRadians () const
{
  return m_angleRadians;
}

double EllipseParameters::b () const
{
  return m_b;
}

QPointF EllipseParameters::posCenter () const
{
  return m_posCenter;
}
