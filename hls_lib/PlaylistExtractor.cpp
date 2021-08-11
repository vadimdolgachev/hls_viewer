#include "PlaylistExtractor.h"

#include <QNetworkReply>

namespace hls {

PlaylistExtractor::PlaylistExtractor(std::unique_ptr<hls::BaseParser> parser,
                                     QObject *parent) :
  QObject(parent),
  mParser(std::move(parser))
{
  connect(&mNetwork, &Network::done,
          this, &PlaylistExtractor::onNetworkDone);
  connect(&mNetwork, &Network::error,
          this, &PlaylistExtractor::onNetworkError);
}

void PlaylistExtractor::extract(const QString &url)
{
  qDebug() << Q_FUNC_INFO << url;
  mNetwork.cancel();
  mNetwork.get(url);
}

void PlaylistExtractor::onNetworkDone(QByteArray data)
{
  try {
    emit done(mParser->parse(data));
  } catch (const std::invalid_argument &e) {
    emit error(e.what());
  }
}

void PlaylistExtractor::onNetworkError(QString networkError)
{
  emit error(networkError);
}

} // namespace hls

