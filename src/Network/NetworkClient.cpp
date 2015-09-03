#include "NetworkClient.h"
#include <QNetworkReply>
#include <QNetworkRequest>


const QString SERVER_URL ("http://localhost/receive_crash_report.php");

NetworkClient::NetworkClient (QObject *parent) :
  QNetworkAccessManager (parent)
{
  connect (this, SIGNAL (finished (QNetworkReply *)), this, SLOT (slotFinished (QNetworkReply *)));
}

void NetworkClient::slotFinished (QNetworkReply *reply)
{
  reply->deleteLater();
}

void NetworkClient::uploadErrorReport (const QString &report)
{
  // Put report into byte array, which must persist until the finished signal
  // is received according to QNetworkAccessManager::post documentation
  QByteArray postData = report.toLatin1();

  QNetworkRequest request (SERVER_URL);
  request.setHeader (QNetworkRequest::ContentTypeHeader,
                     QVariant (QString ("text/xml")));
  request.setHeader (QNetworkRequest::ContentLengthHeader,
                     QVariant (qulonglong (postData.size())));

  post(request,
       postData);
}
