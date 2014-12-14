#ifndef DLG_FILTER_WORKER_H
#define DLG_FILTER_WORKER_H

#include "FilterParameter.h"
#include <QObject>
#include <QPixmap>
#include <QTimer>

/// Class for processing new filter settings. This is based on http://blog.debao.me/2013/08/how-to-use-qworker-in-the-right-way-part-1/
class DlgFilterWorker : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgFilterWorker(const QPixmap &pixmapOriginal);

public slots:
  /// Start processing with a new set of parameters. Any ongoing processing is interrupted when m_filterParameter changes.
  void slotRestartProcessing (FilterParameter filterParameter,
                              double low,
                              double high);

private slots:
  void slotRestartTimeout ();

signals:
  /// Send a processed vertical piece of the original pixmap. The destination is between xLeft and xLeft+pixmap.width()
  void signalTransferPiece (int xLeft,
                            QPixmap pixmap);

private:
  DlgFilterWorker();

  QPixmap m_pixmapOriginal;
  FilterParameter m_filterParameterRequested; // Set by slotRestartProcessing
  FilterParameter m_filterParameterCurrent; // Set when processing restarts
  double m_low; // Requested/current low threshold
  double m_high; // Requested/current high threshold

  QTimer m_restartTimer; // Decouple slotRestartProcessing from the processing that this class performs
};

#endif // DLG_FILTER_WORKER_H
