#include "DlgFilterThread.h"
#include "DlgSettingsFilter.h"

DlgFilterThread::DlgFilterThread(const QPixmap &pixmapOriginal,
                                 QRgb rgbBackground,
                                 DlgSettingsFilter &dlgSettingsFilter) :
  m_pixmapOriginal (pixmapOriginal),
  m_rgbBackground (rgbBackground),
  m_dlgSettingsFilter (dlgSettingsFilter)
{
}

void DlgFilterThread::run ()
{
  m_dlgFilterWorker = new DlgFilterWorker (m_pixmapOriginal,
                                           m_rgbBackground);

  // Connect signal to start process
  connect (&m_dlgSettingsFilter, SIGNAL (signalApplyFilter (FilterParameter, double, double)),
           m_dlgFilterWorker, SLOT (slotRestartProcessing (FilterParameter, double, double)));

  // Connect signal to return each piece of completed processing
  connect (m_dlgFilterWorker, SIGNAL (signalTransferPiece (int, QImage)),
           &m_dlgSettingsFilter, SLOT (slotTransferPiece (int, QImage)));

  exec ();
}
