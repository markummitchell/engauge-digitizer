#include "CmdMediator.h"
#include "DlgModelPointMatch.h"

const double DEFAULT_POINT_SEPARATION = 0;
const double DEFAULT_MAX_POINT_SIZE = 1;
const ColorPalette DEFAULT_COLOR_ACCEPTED = COLOR_PALETTE_GREEN;
const ColorPalette DEFAULT_COLOR_CANDIDATE = COLOR_PALETTE_YELLOW;
const ColorPalette DEFAULT_COLOR_REJECTED = COLOR_PALETTE_RED;

DlgModelPointMatch::DlgModelPointMatch() :
  m_pointSeparation (DEFAULT_POINT_SEPARATION),
  m_maxPointSize (DEFAULT_MAX_POINT_SIZE),
  m_paletteColorAccepted (DEFAULT_COLOR_ACCEPTED),
  m_paletteColorCandidate (DEFAULT_COLOR_CANDIDATE),
  m_paletteColorRejected (DEFAULT_COLOR_REJECTED)
{
}

DlgModelPointMatch::DlgModelPointMatch(const CmdMediator &cmdMediator) :
  m_pointSeparation (cmdMediator.document().modelPointMatch().pointSeparation()),
  m_maxPointSize (cmdMediator.document().modelPointMatch().maxPointSize()),
  m_paletteColorAccepted (cmdMediator.document().modelPointMatch().paletteColorAccepted()),
  m_paletteColorCandidate (cmdMediator.document().modelPointMatch().paletteColorCandidate()),
  m_paletteColorRejected (cmdMediator.document().modelPointMatch().paletteColorRejected())
{
}

DlgModelPointMatch::DlgModelPointMatch(const DlgModelPointMatch &other) :
  m_pointSeparation (other.pointSeparation()),
  m_maxPointSize (other.maxPointSize()),
  m_paletteColorAccepted (other.paletteColorAccepted()),
  m_paletteColorCandidate (other.paletteColorCandidate()),
  m_paletteColorRejected (other.paletteColorRejected())
{
}

DlgModelPointMatch &DlgModelPointMatch::operator=(const DlgModelPointMatch &other)
{
  m_pointSeparation = other.pointSeparation();
  m_maxPointSize = other.maxPointSize();
  m_paletteColorAccepted = other.paletteColorAccepted();
  m_paletteColorCandidate = other.paletteColorCandidate();
  m_paletteColorRejected = other.paletteColorRejected();

  return *this;
}

double DlgModelPointMatch::maxPointSize () const
{
  return m_maxPointSize;
}

ColorPalette DlgModelPointMatch::paletteColorAccepted() const
{
  return m_paletteColorAccepted;
}

ColorPalette DlgModelPointMatch::paletteColorCandidate() const
{
  return  m_paletteColorCandidate;
}

ColorPalette DlgModelPointMatch::paletteColorRejected() const
{
  return m_paletteColorRejected;
}

double DlgModelPointMatch::pointSeparation() const
{
  return m_pointSeparation;
}

void DlgModelPointMatch::setMaxPointSize(double maxPointSize)
{
  m_maxPointSize = maxPointSize;
}

void DlgModelPointMatch::setPointSeparation(double pointSeparation)
{
  m_pointSeparation = pointSeparation;
}

void DlgModelPointMatch::setPaletteColorAccepted(ColorPalette paletteColorAccepted)
{
  m_paletteColorAccepted = paletteColorAccepted;
}

void DlgModelPointMatch::setPaletteColorCandidate(ColorPalette paletteColorCandidate)
{
  m_paletteColorCandidate = paletteColorCandidate;
}

void DlgModelPointMatch::setPaletteColorRejected(ColorPalette paletteColorRejected)
{
  m_paletteColorRejected = paletteColorRejected;
}
