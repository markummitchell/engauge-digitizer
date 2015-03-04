#ifndef DLG_FILTER_WORKER_H
#define DLG_FILTER_WORKER_H

#include "ColorFilterMode.h"
#include "DlgFilterCommand.h"
#include <QImage>
#include <QList>
#include <QObject>
#include <QPixmap>
#include <QRgb>
#include <QTimer>

typedef QList<DlgFilterCommand> FilterCommandQueue;

/// Class for processing new filter settings. This is based on http://blog.debao.me/2013/08/how-to-use-qworker-in-the-right-way-part-1/
class DlgFilterWorker : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgFilterWorker(const QPixmap &pixmapOriginal,
                  QRgb m_rgbBackground);

public slots:
  /// Start processing with a new set of parameters. Any ongoing processing is interrupted when m_filterMode changes.
  void slotNewParameters (ColorFilterMode colorFilterMode,
                          double low,
                          double high);

private slots:
  void slotRestartTimeout ();

signals:
  /// Send a processed vertical piece of the original pixmap. The destination is between xLeft and xLeft+pixmap.width()
  void signalTransferPiece (int xLeft,
                            QImage image);

private:
  DlgFilterWorker();

  QImage m_imageOriginal; // Use QImage rather than QPixmap so we can access pixel by pixel
  QRgb m_rgbBackground;

  FilterCommandQueue m_inputCommandQueue;
  ColorFilterMode m_colorFilterMode; // Set when processing restarts
  double m_low;
  double m_high;

  int m_xLeft;
  QTimer m_restartTimer; // Decouple slotRestartProcessing from the processing that this class performs
};

#endif // DLG_FILTER_WORKER_H
