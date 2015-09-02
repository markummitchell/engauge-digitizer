#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <QNetworkAccessManager>

class QNetworkReply;

/// Client for interacting with Engauge server
class NetworkClient : public QNetworkAccessManager
{
  Q_OBJECT;

 public:
  /// Single constructor
  NetworkClient();

  /// Upload the error report asynchronously
  void uploadErrorReport (const QString &report);

 public slots:

  /// Cleanup after response is returned
  void slotFinished (QNetworkReply *);

};

#endif // NETWORK_CLIENT_H
