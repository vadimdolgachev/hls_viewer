#include "Network.h"

const int REQUEST_TIMEOUT_MS = 5000;

namespace hls {

Network::Network(QObject *parent) :
  QObject(parent),
  mReply(nullptr)
{
  mTimer.setInterval(REQUEST_TIMEOUT_MS);
  mTimer.setSingleShot(true);
  connect(&mTimer, &QTimer::timeout, this, &Network::onTimeout);
}

void Network::get(QString url)
{
  mReply = mNAM.get(QNetworkRequest(url));
  mTimer.start();
  connect(mReply, &QNetworkReply::finished,
          this, &Network::onFinished);
  connect(mReply, &QNetworkReply::metaDataChanged,
          this, &Network::onMetaDataChanged);
  connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
          this, &Network::onError);
}

void Network::cancel()
{
  mTimer.stop();
  if (mReply) {
    mReply->abort();
  }
}

void Network::onTimeout()
{
  if (mReply) {
    mReply->blockSignals(true);
  }
  cancel();
  emit error("request timeout");
  if (mReply) {
    mReply->blockSignals(false);
  }
}

void Network::onFinished()
{
  mTimer.stop();
  if (mReply && mReply->isOpen()) {
    emit done(mReply->readAll());
  }
}

void Network::onMetaDataChanged()
{
  if (mReply) {
    emit metaDataChanged(mReply->rawHeaderPairs());
  }
}

void Network::onError(QNetworkReply::NetworkError networkError)
{
  Q_UNUSED(networkError)

  mTimer.stop();
  emit error(mReply->errorString());
}

} // namespace hls

