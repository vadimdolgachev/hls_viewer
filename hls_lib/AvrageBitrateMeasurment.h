#ifndef AVRAGEBITRATEMEASURMENT_H
#define AVRAGEBITRATEMEASURMENT_H

#include "BasePlaylist.h"
#include "MediaPlaylist.h"
#include "Network.h"
#include "tags/StreamInf.h"

#include <QObject>

#include <memory>

namespace hls {

class AvrageBitrateMeasurment : public QObject
{
  Q_OBJECT
public:
  AvrageBitrateMeasurment(const QString &baseUrl,
                          const QString &variantStreamUri,
                          QObject *parent = nullptr);
  ~AvrageBitrateMeasurment();

signals:
  void started();
  void done(int minAverageBitrate, int maxAverageBitrate);
  void error(QString error);

public:
  void measure();
  void stop();

private slots:
  void onExtractorDone(std::shared_ptr<BasePlaylist> playlist);
  void onExtractorError(QString extractorError);
  void onNetworkDone(QByteArray data);
  void onNetworkError(QString networkError);
  void onNetworkMetaDataChanged(QList<QNetworkReply::RawHeaderPair> metaData);

private:
  void downloadNextSegment();
  void downloadSegment();
  void calcAndSaveSegmentBitrate(int length);

  static int calcBitrate(float duration, int length);

  const QString mBaseUrl;
  const QString mVariantStreamUri;
  std::shared_ptr<MediaPlaylist> mMediaPlaylist;
  Network *mNetwork;
  int mSegmentIndex;
  int mMinAverageBitrate;
  int mMaxAverageBitrate;
};

}

#endif // AVRAGEBITRATEMEASURMENT_H
