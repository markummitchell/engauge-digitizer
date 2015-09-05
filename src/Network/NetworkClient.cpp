#include "Logger.h"
#include "NetworkClient.h"
#include <QNetworkReply>
#include <QNetworkRequest>


const QString SERVER_URL ("http://engaugedigitizer.net/receive_crash_report.php");

NetworkClient::NetworkClient (QObject *parent) :
  QNetworkAccessManager (parent)
{
  connect (this, SIGNAL (finished (QNetworkReply *)), this, SLOT (slotFinished (QNetworkReply *)));
}

QString NetworkClient::cleanXml (const QString &before)
{
  LOG4CPP_INFO_S ((*mainCat)) << "NetworkClient::cleanXml";

  // Remove characters that are known to break the xml parsing in Document. Bad characters AFTER the
  // CDATA will break the parsing of the CDATA, which is a very hard bug to track down, so this
  // method should prevent that specific issue

  QString after;
  for (int i = 0; i < before.size(); i++) {

    if (before.at (i).unicode() < 128) {

      after += before.at (i);
    }
  }

  return after;
}

void NetworkClient::slotFinished (QNetworkReply *reply)
{
  reply->deleteLater();
}

void NetworkClient::uploadErrorReport (const QString &report)
{
  QString reportClean = cleanXml (report);

  // Put report into byte array, which must persist until the finished signal
  // is received according to QNetworkAccessManager::post documentation
  QByteArray postData = reportClean.toLatin1();

  QNetworkRequest request (SERVER_URL);
  request.setHeader (QNetworkRequest::ContentTypeHeader,
                     QVariant (QString ("text/xml")));
  request.setHeader (QNetworkRequest::ContentLengthHeader,
                     QVariant (qulonglong (postData.size())));

  post(request,
       postData);
}
