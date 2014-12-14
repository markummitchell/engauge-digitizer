#include "DlgFilterWorker.h"
#include "DlgSettingsFilter.h"
#include "Logger.h"

const int NO_DELAY = 0;

DlgFilterWorker::DlgFilterWorker(const QPixmap &pixmapOriginal) :
  m_pixmapOriginal (pixmapOriginal),
  m_filterParameterRequested (NUM_FILTER_PARAMETERS),
  m_filterParameterCurrent (NUM_FILTER_PARAMETERS)
{
  m_restartTimer.setSingleShot (false);
  connect (&m_restartTimer, SIGNAL (timeout ()), this, SLOT (slotRestartTimeout()));
}

void DlgFilterWorker::slotRestartProcessing (FilterParameter filterParameter,
                                             double low,
                                             double high)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgFilterWorker::slotRestartProcessing";

  m_filterParameterRequested = filterParameter;
  m_low = low;
  m_high = high;

  m_restartTimer.start (NO_DELAY);
}

void DlgFilterWorker::slotRestartTimeout ()
{

}
