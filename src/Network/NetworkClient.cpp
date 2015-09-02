#include "NetworkClient.h"
#include <QNetworkReply>
#include <QNetworkRequest>


const QString SERVER_URL ("http://localhost");

NetworkClient::NetworkClient ()
{
  connect (this, SIGNAL (finished (QNetworkReply *)), this, SLOT (slotFinished (QNetworkReply *)));
}

void NetworkClient::slotFinished (QNetworkReply *reply)
{
  reply->deleteLater();
}

void NetworkClient::uploadErrorReport (const QString &report)
{
  // Put report into byte array
  QByteArray postData = report.toLatin1();

  QNetworkRequest request (SERVER_URL);
  request.setRawHeader (QString ("Content-Type").toLatin1(),
                        QString ("multipart/form-data; boundary=margin").toLatin1());
  request.setRawHeader (QString ("Content-Length").toLatin1(),
                        QString::number (postData.length()).toLatin1());

  post(request,
       postData);
}
