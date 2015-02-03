#include "DlgFilterThread.h"
#include "DlgSettingsFilter.h"

DlgFilterThread::DlgFilterThread(const QPixmap &pixmapOriginal,
                                 QRgb rgbBackground,
                                 DlgSettingsFilter &dlgSettingsFilter) :
  m_pixmapOriginal (pixmapOriginal),
  m_rgbBackground (rgbBackground),
  m_dlgSettingsFilter (dlgSettingsFilter),
  m_dlgFilterWorker (0)
{
}

void DlgFilterThread::run ()
{
  // Create worker only once
  if (m_dlgFilterWorker == 0) {

    m_dlgFilterWorker = new DlgFilterWorker (m_pixmapOriginal,
                                             m_rgbBackground);

    // Connect signal to start process
    connect (&m_dlgSettingsFilter, SIGNAL (signalApplyFilter (FilterMode, double, double)),
             m_dlgFilterWorker, SLOT (slotNewParameters (FilterMode, double, double)));

    // Connect signal to return each piece of completed processing
    connect (m_dlgFilterWorker, SIGNAL (signalTransferPiece (int, QImage)),
             &m_dlgSettingsFilter, SLOT (slotTransferPiece (int, QImage)));
  }

  exec ();
}
