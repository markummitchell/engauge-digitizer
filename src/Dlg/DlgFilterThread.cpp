#include "DlgFilterThread.h"
#include "DlgSettingsColorFilter.h"

DlgFilterThread::DlgFilterThread(const QPixmap &pixmapOriginal,
                                 QRgb rgbBackground,
                                 DlgSettingsColorFilter &dlgSettingsColorFilter)
    : m_pixmapOriginal(pixmapOriginal), m_rgbBackground(rgbBackground),
      m_dlgSettingsColorFilter(dlgSettingsColorFilter), m_dlgFilterWorker(0) {}

void DlgFilterThread::run() {
  // Create worker only once
  if (m_dlgFilterWorker == 0) {

    m_dlgFilterWorker = new DlgFilterWorker(m_pixmapOriginal, m_rgbBackground);

    // Connect signal to start process
    connect(&m_dlgSettingsColorFilter,
            SIGNAL(signalApplyFilter(ColorFilterMode, double, double)),
            m_dlgFilterWorker,
            SLOT(slotNewParameters(ColorFilterMode, double, double)));

    // Connect signal to return each piece of completed processing
    connect(m_dlgFilterWorker, SIGNAL(signalTransferPiece(int, QImage)),
            &m_dlgSettingsColorFilter, SLOT(slotTransferPiece(int, QImage)));
  }

  exec();
}
