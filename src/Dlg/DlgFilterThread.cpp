#include "DlgFilterThread.h"
#include "DlgSettingsFilter.h"

DlgFilterThread::DlgFilterThread(const QPixmap &pixmapOriginal,
                                 DlgSettingsFilter &dlgSettingsFilter) :
  m_pixmapOriginal (pixmapOriginal),
  m_filterParameterRequested (NUM_FILTER_PARAMETERS),
  m_filterParameterCurrent (NUM_FILTER_PARAMETERS),
  m_dlgFilterWorker (pixmapOriginal)
{
  connect (&dlgSettingsFilter, SIGNAL (signalApplyFilter (FilterParameter, double, double)),
           &m_dlgFilterWorker, SLOT (slotRestartProcessing (FilterParameter, double, double)));
  connect (&m_dlgFilterWorker, SIGNAL (signalTransferPiece (int, QPixmap pixmap)),
           &dlgSettingsFilter, SLOT (slotTransferPiece (int, QPixmap pixmap)));
}

void DlgFilterThread::run ()
{
  exec ();
}
