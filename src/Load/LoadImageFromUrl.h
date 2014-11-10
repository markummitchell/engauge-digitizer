#ifndef LOAD_IMAGE_FROM_URL_H
#define LOAD_IMAGE_FROM_URL_H

#include <QImage>
#include <QtNetwork/QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>

class MainWindow;
class QUrl;

/// Load QImage from url. This is trivial for a file, but requires an asynchronous download step for http urls.
class LoadImageFromUrl : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  LoadImageFromUrl(MainWindow &mainWindow);
  ~LoadImageFromUrl();

  /// Start the asynchronous loading of an image from the specified url.
  void startLoadImage (const QUrl &url);

private slots:
  void slotFinished ();
  void slotReadData ();

signals:
  /// Send the imported image to MainWindow. This completes the asynchronous loading of the image
  void signalImportImage (QString, QImage);

private:
  LoadImageFromUrl();

  void deallocate ();

  MainWindow &m_mainWindow;
  QUrl m_url;
  QNetworkAccessManager m_http;
  QNetworkReply *m_reply;
  QByteArray *m_buffer;
};

#endif // LOAD_IMAGE_FROM_URL_H
