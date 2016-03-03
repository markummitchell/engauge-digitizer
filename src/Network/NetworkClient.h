/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <QByteArray>
#include <QNetworkAccessManager>

class QNetworkReply;

/// Client for interacting with Engauge server
class NetworkClient : public QNetworkAccessManager
{
  Q_OBJECT;

 public:
  /// Single constructor
  NetworkClient(QObject *parent);

  /// Upload the error report asynchronously
  void uploadErrorReport (const QString &report);

 public slots:

  /// Cleanup after response is returned
  void slotFinished (QNetworkReply *);

 private:
  NetworkClient();

  QString cleanXml (const QString &before);

};

#endif // NETWORK_CLIENT_H
