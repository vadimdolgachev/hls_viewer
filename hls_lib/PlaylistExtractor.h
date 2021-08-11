#ifndef PLAYLISTEXTRACTOR_H
#define PLAYLISTEXTRACTOR_H

#include "MasterPlaylist.h"
#include "Network.h"
#include "BaseParser.h"

#include <QObject>
#include <QString>

#include <memory>

namespace hls {

class PlaylistExtractor : public QObject {
  Q_OBJECT
public:
  PlaylistExtractor(std::unique_ptr<hls::BaseParser> parser,
                    QObject *parent = nullptr);

  void extract(const QString &url);

signals:
  void done(std::shared_ptr<BasePlaylist> playlist);
  void error(QString error);

private slots:
  void onNetworkDone(QByteArray data);
  void onNetworkError(QString networkError);

private:
  Network mNetwork;
  std::unique_ptr<hls::BaseParser> mParser;
};

} // namespace hls

#endif // PLAYLISTEXTRACTOR_H
