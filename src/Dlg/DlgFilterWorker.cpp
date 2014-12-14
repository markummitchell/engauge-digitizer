#include "DlgFilterWorker.h"
#include "DlgSettingsFilter.h"

DlgFilterWorker::DlgFilterWorker(const QPixmap &pixmapOriginal) :
  m_pixmapOriginal (pixmapOriginal),
  m_filterParameterRequested (NUM_FILTER_PARAMETERS),
  m_filterParameterCurrent (NUM_FILTER_PARAMETERS)
{
}

void DlgFilterWorker::slotRestartProcessing (FilterParameter filterParameter,
                                             double low,
                                             double high)
{
  m_filterParameterRequested = filterParameter;
  m_low = low;
  m_high = high;
}
