#include "MediaPlaylist.h"
#include "MediaPlaylistParser.h"
#include "PlaylistExtractor.h"
#include "AvrageBitrateMeasurment.h"

#include <QDebug>
#include <QThread>

#include <cmath>

const QString CONTENT_LENGTH_HEADER = "Content-Length";

namespace hls {

AvrageBitrateMeasurment::AvrageBitrateMeasurment(const QString &baseUrl,
                                                 const QString &variantStreamUri,
                                                 QObject *parent) :
  QObject(parent),
  mBaseUrl(baseUrl),
  mVariantStreamUri(variantStreamUri),
  mNetwork(nullptr),
  mSegmentIndex(0),
  mMinAverageBitrate(INT_MAX),
  mMaxAverageBitrate(INT_MIN)
{

}

AvrageBitrateMeasurment::~AvrageBitrateMeasurment()
{
  qDebug() << Q_FUNC_INFO;
}

void AvrageBitrateMeasurment::measure()
{
  mNetwork = new Network(this);

  connect(mNetwork, &Network::done,
          this, &AvrageBitrateMeasurment::onNetworkDone);
  connect(mNetwork, &Network::metaDataChanged,
          this, &AvrageBitrateMeasurment::onNetworkMetaDataChanged);
  connect(mNetwork, &Network::error,
          this, &AvrageBitrateMeasurment::onNetworkError);

  // TODO: need make cancel on stop
  auto extractor = new hls::PlaylistExtractor(std::make_unique<hls::MediaPlaylistParser>(),
                                              this);
  connect(extractor, &hls::PlaylistExtractor::done,
          this, &AvrageBitrateMeasurment::onExtractorDone);
  connect(extractor, &hls::PlaylistExtractor::error,
          this, &AvrageBitrateMeasurment::onExtractorError);
  extractor->extract(mBaseUrl + mVariantStreamUri);

  emit started();
}

void AvrageBitrateMeasurment::stop()
{
  emit done(0, 0);
}

void AvrageBitrateMeasurment::onExtractorDone(std::shared_ptr<BasePlaylist> playlist)
{
  const auto mediaPlaylist = std::dynamic_pointer_cast<MediaPlaylist>(playlist);
  if (mediaPlaylist) {
    mMediaPlaylist = mediaPlaylist;
    if (mMediaPlaylist->playlistType()
        && mMediaPlaylist->playlistType().value() == hls::PLAYLIST_TYPE_VOD) {
      downloadSegment();
    } else {
      emit error(tr("Variant stream(%1) isn't VOD type.").arg(mVariantStreamUri));
      emit done(0, 0);
    }
  }
}

void AvrageBitrateMeasurment::onExtractorError(QString extractorError)
{
  emit error(extractorError);
  stop();
}

void AvrageBitrateMeasurment::onNetworkDone(QByteArray data)
{
  // is called if `Content-Length` not found in metadata
  calcAndSaveSegmentBitrate(data.length());
  downloadNextSegment();
}

void AvrageBitrateMeasurment::onNetworkError(QString networkError)
{
  emit error(networkError);
  stop();
}

void AvrageBitrateMeasurment::onNetworkMetaDataChanged(QList<QNetworkReply::RawHeaderPair> metaData)
{
  const auto it = std::find_if(std::begin(metaData), std::end(metaData), [](auto pair) {
    return pair.first == CONTENT_LENGTH_HEADER;
  });
  if (it != std::end(metaData)) {
    mNetwork->blockSignals(true);
    mNetwork->cancel();
    mNetwork->blockSignals(false);

    calcAndSaveSegmentBitrate(it->second.toInt());
    downloadNextSegment();
  }
}

void AvrageBitrateMeasurment::downloadNextSegment()
{
  ++mSegmentIndex;
  downloadSegment();
}

void AvrageBitrateMeasurment::downloadSegment()
{
  if (mSegmentIndex < mMediaPlaylist->segments().size()) {
    if (mMediaPlaylist) {
      const auto segment = mMediaPlaylist->segments().at(mSegmentIndex);
      auto url = mBaseUrl + hls::baseUrl(mVariantStreamUri) + segment.uri();
      mNetwork->get(url);
    }
  } else {
    emit done(mMinAverageBitrate, mMaxAverageBitrate);
  }
}

void AvrageBitrateMeasurment::calcAndSaveSegmentBitrate(int length)
{
  const auto segment = mMediaPlaylist->segments().at(mSegmentIndex);
  const auto bitrate = calcBitrate(segment.duration(), length);
  mMinAverageBitrate = std::min(mMinAverageBitrate, bitrate);
  mMaxAverageBitrate = std::max(mMaxAverageBitrate, bitrate);
  qDebug() << mVariantStreamUri << segment.uri()
           << bitrate << std::lround(bitrate / 1000.f)
           << mMinAverageBitrate << mMaxAverageBitrate;
}

int AvrageBitrateMeasurment::calcBitrate(float duration, int length)
{
  return hls::BITS_PER_BYTE * std::lround(length / duration);
}

} // namespace hls
