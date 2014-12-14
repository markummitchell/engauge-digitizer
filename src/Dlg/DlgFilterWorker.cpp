#include "DlgFilterWorker.h"
#include "DlgSettingsFilter.h"
#include "Filter.h"
#include "Logger.h"
#include <QImage>

const int NO_DELAY = 0;
const int COLUMNS_PER_PIECE = 5;

DlgFilterWorker::DlgFilterWorker(const QPixmap &pixmapOriginal,
                                 QRgb rgbBackground) :
  m_imageOriginal (pixmapOriginal.toImage()),
  m_rgbBackground (rgbBackground),
  m_filterParameterRequested (NUM_FILTER_PARAMETERS),
  m_lowRequested (-1.0),
  m_highRequested (-1.0),
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
  // Try to process a new piece
  if ((m_filterParameterRequested != m_filterParameterCurrent) ||
      (m_lowRequested != m_low) ||
      (m_highRequested != m_high)) {

    // Start over from the left side
    m_filterParameterCurrent = m_filterParameterRequested;
    m_low = m_lowRequested;
    m_high = m_highRequested;

    m_xLeft = 0;

  } else {

    // To to process a new piece, starting at m_xLeft
    int xStop = m_xLeft + COLUMNS_PER_PIECE;
    if (xStop >= m_imageOriginal.width()) {
      xStop = m_imageOriginal.width();
    }

    Filter filter;
    int processedWidth = xStop - m_xLeft;
    QImage imageProcessed (processedWidth,
                           m_imageOriginal.height(),
                           QImage::Format_RGB32);
    for (int xFrom = m_xLeft, xTo = 0; xFrom < xStop; xFrom++, xTo++) {
      for (int y = 0; y < m_imageOriginal.height (); y++) {
        QColor pixel = m_imageOriginal.pixel (xFrom, y);
        bool isOn = filter.pixelIsOn (m_filterParameterCurrent,
                                      pixel,
                                      m_rgbBackground,
                                      m_low,
                                      m_high);
        imageProcessed.setPixel (xTo, y, (isOn ?
                                          QColor (Qt::black).rgb () :
                                          QColor (Qt::white).rgb ()));
      }
    }

    emit signalTransferPiece (m_xLeft,
                              imageProcessed);

    if (xStop < m_imageOriginal.width()) {
      m_restartTimer.start (NO_DELAY);
    }
  }
}
