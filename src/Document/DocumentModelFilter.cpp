#include "CmdMediator.h"
#include "DocumentModelFilter.h"
#include "Logger.h"
#include <QXmlStreamWriter>

DocumentModelFilter::DocumentModelFilter() :
  m_filterParameter (FILTER_PARAMETER_INTENSITY)
{
}

DocumentModelFilter::DocumentModelFilter(const CmdMediator &cmdMediator) :
  m_filterParameter (cmdMediator.document().modelFilter().filterParameter())
{

}

DocumentModelFilter::DocumentModelFilter(const DocumentModelFilter &other) :
  m_filterParameter (other.filterParameter())
{

}

DocumentModelFilter &DocumentModelFilter::operator=(const DocumentModelFilter &other)
{
  m_filterParameter = other.filterParameter();

  return *this;
}

FilterParameter DocumentModelFilter::filterParameter() const
{
  return m_filterParameter;
}

void DocumentModelFilter::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelFilter::saveModel";

  stream.writeStartElement("DocumentModelFilter");
  stream.writeEndElement();
}

void DocumentModelFilter::setFilterParameter(FilterParameter filterParameter)
{
  m_filterParameter = filterParameter;
}
