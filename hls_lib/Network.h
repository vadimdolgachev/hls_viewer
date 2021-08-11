#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>

namespace hls {

class Network : public QObject
{
  Q_OBJECT
public:
  Network(QObject *parent = nullptr);

public:
  void get(QString url);
  void cancel();

signals:
  void done(QByteArray data);
  void error(QString error);
  void metaDataChanged(QList<QNetworkReply::RawHeaderPair>);

private slots:
  void onTimeout();
  void onFinished();
  void onMetaDataChanged();
  void onError(QNetworkReply::NetworkError networkError);

private:
  QNetworkAccessManager mNAM;
  QNetworkReply *mReply;
  QTimer mTimer;
};

}

#endif // NETWORK_H
