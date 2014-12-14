#ifndef DLG_FILTER_THREAD_H
#define DLG_FILTER_THREAD_H

#include "DlgFilterWorker.h"
#include "FilterParameter.h"
#include <QObject>
#include <QPixmap>
#include <QThread>

class DlgSettingsFilter;

/// Class for processing new filter settings. This is based on http://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
class DlgFilterThread : public QThread
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgFilterThread(const QPixmap &pixmapOriginal,
                  DlgSettingsFilter &dlgSettingsFilter);

  /// Run this thread.
  virtual void run();

signals:
  /// Send a processed vertical piece of the original pixmap. The destination is between xLeft and xLeft+pixmap.width()
  void signalTransferPiece (int xLeft,
                            QPixmap pixmap);

private:
  DlgFilterThread();

  QPixmap m_pixmapOriginal;
  FilterParameter m_filterParameterRequested; // Set by slotRestartProcessing
  FilterParameter m_filterParameterCurrent; // Set when processing restarts
  double m_low; // Requested/current low threshold
  double m_high; // Requested/current high threshold

  DlgFilterWorker m_dlgFilterWorker;
};

#endif // DLG_FILTER_THREAD_H
