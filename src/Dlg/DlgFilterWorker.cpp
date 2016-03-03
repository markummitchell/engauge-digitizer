/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorFilter.h"
#include "DlgFilterWorker.h"
#include "Logger.h"
#include <QImage>

const int NO_DELAY = 0;
const int COLUMNS_PER_PIECE = 5;

DlgFilterWorker::DlgFilterWorker(const QPixmap &pixmapOriginal,
                                 QRgb rgbBackground) :
  m_imageOriginal (pixmapOriginal.toImage()),
  m_rgbBackground (rgbBackground),
  m_colorFilterMode (NUM_COLOR_FILTER_MODES),
  m_low (-1.0),
  m_high (-1.0)
{
  m_restartTimer.setSingleShot (false);
  connect (&m_restartTimer, SIGNAL (timeout ()), this, SLOT (slotRestartTimeout()));
}

void DlgFilterWorker::slotNewParameters (ColorFilterMode colorFilterMode,
                                         double low,
                                         double high)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgFilterWorker::slotNewParameters filterMode=" << colorFilterMode
                              << " low=" << low
                              << " high=" << high;

  // Push onto queue
  DlgFilterCommand command (colorFilterMode,
                            low,
                            high);
  m_inputCommandQueue.push_back (command);

  if (!m_restartTimer.isActive()) {

    // Timer is not currently active so start it up
    m_restartTimer.start (NO_DELAY);
  }
}

void DlgFilterWorker::slotRestartTimeout ()
{
  if (m_inputCommandQueue.count() > 0) {

    DlgFilterCommand command = m_inputCommandQueue.last();
    m_inputCommandQueue.clear ();

    // Start over from the left side
    m_colorFilterMode = command.colorFilterMode();
    m_low = command.low0To1();
    m_high = command.high0To1();

    m_xLeft = 0;

    // Start timer to process first piece
    m_restartTimer.start (NO_DELAY);

  } else if (m_xLeft < m_imageOriginal.width ()) {

    // To to process a new piece, starting at m_xLeft
    int xStop = m_xLeft + COLUMNS_PER_PIECE;
    if (xStop >= m_imageOriginal.width()) {
      xStop = m_imageOriginal.width();
    }

    // From  here on, if a new command gets pushed onto the queue then we immediately stop processing
    // and do nothing except start the timer so we can start over after the next timeout. The goal is
    // to not tie up the gui by emitting signalTransferPiece unnecessarily.
    //
    // This code is basically a heavily customized version of ColorFilter::filterImage
    ColorFilter filter;
    int processedWidth = xStop - m_xLeft;
    QImage imageProcessed (processedWidth,
                           m_imageOriginal.height(),
                           QImage::Format_RGB32);
    for (int xFrom = m_xLeft, xTo = 0; (xFrom < xStop) && (m_inputCommandQueue.count() == 0); xFrom++, xTo++) {
      for (int y = 0; (y < m_imageOriginal.height ()) && (m_inputCommandQueue.count() == 0); y++) {
        QColor pixel = m_imageOriginal.pixel (xFrom, y);
        bool isOn = false;
        if (pixel.rgb() != m_rgbBackground) {

          isOn = filter.pixelUnfilteredIsOn (m_colorFilterMode,
                                             pixel,
                                             m_rgbBackground,
                                             m_low,
                                             m_high);
        }

        imageProcessed.setPixel (xTo, y, (isOn ?
                                          QColor (Qt::black).rgb () :
                                          QColor (Qt::white).rgb ()));
      }
    }

    if (m_inputCommandQueue.count() == 0) {
      emit signalTransferPiece (m_xLeft,
                                imageProcessed);
      m_xLeft += processedWidth;
    }

    if ((xStop < m_imageOriginal.width()) ||
        (m_inputCommandQueue.count () > 0)) {

      // Restart timer to process next piece
      m_restartTimer.start (NO_DELAY);
    }
  }
}
