/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_FILTER_THREAD_H
#define DLG_FILTER_THREAD_H

#include "DlgFilterWorker.h"
#include <QObject>
#include <QPixmap>
#include <QThread>

class DlgSettingsColorFilter;

/// Class for processing new filter settings. This is based on http://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
class DlgFilterThread : public QThread
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgFilterThread(const QPixmap &pixmapOriginal,
                  QRgb rgbBackground,
                  DlgSettingsColorFilter &dlgSettingsColorFilter);

  /// Run this thread.
  virtual void run();

signals:
  /// Send a processed vertical piece of the original pixmap. The destination is between xLeft and xLeft+pixmap.width()
  void signalTransferPiece (int xLeft,
                            QImage image);

private:
  DlgFilterThread();

  QPixmap m_pixmapOriginal;
  QRgb m_rgbBackground;

  DlgSettingsColorFilter &m_dlgSettingsColorFilter;

  // Worker must be created in the run method of this thread so it belongs to this thread rather than the GUI thread that called it
  DlgFilterWorker *m_dlgFilterWorker;
};

#endif // DLG_FILTER_THREAD_H
