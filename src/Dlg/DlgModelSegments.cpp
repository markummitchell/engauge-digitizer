#include "CmdMediator.h"
#include "DlgModelSegments.h"

DlgModelSegments::DlgModelSegments() :
  m_fillCorners (false)
{
}

DlgModelSegments::DlgModelSegments(const CmdMediator &cmdMediator) :
  m_fillCorners (cmdMediator.document().modelSegments().fillCorners())
{
}

DlgModelSegments::DlgModelSegments(const DlgModelSegments &other) :
  m_fillCorners (other.fillCorners ())
{
}

DlgModelSegments &DlgModelSegments::operator=(const DlgModelSegments &other)
{
  m_fillCorners = other.fillCorners ();

  return *this;
}

bool DlgModelSegments::fillCorners () const
{
  return m_fillCorners;
}

void DlgModelSegments::setFillCorners (bool fillCorners)
{
  m_fillCorners = fillCorners;
}
