#include "CmdMediator.h"
#include "DlgModelFilter.h"

DlgModelFilter::DlgModelFilter() :
  m_filterParameter (FILTER_PARAMETER_INTENSITY)
{
}

DlgModelFilter::DlgModelFilter(const CmdMediator &cmdMediator) :
  m_filterParameter (cmdMediator.document().modelFilter().filterParameter())
{

}

DlgModelFilter::DlgModelFilter(const DlgModelFilter &other) :
  m_filterParameter (other.filterParameter())
{

}

DlgModelFilter &DlgModelFilter::operator=(const DlgModelFilter &other)
{
  m_filterParameter = other.filterParameter();

  return *this;
}

FilterParameter DlgModelFilter::filterParameter() const
{
  return m_filterParameter;
}

void DlgModelFilter::setFilterParameter(FilterParameter filterParameter)
{
  m_filterParameter = filterParameter;
}
