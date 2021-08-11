#include "PlaylistExtractor.h"
#include "MasterPlaylistParser.h"

#include <QCoreApplication>
#include <QString>
#include <QStringBuilder>

#include <optional>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  hls::PlaylistExtractor hls(std::make_unique<hls::MasterPlaylistParser>());
  QObject::connect(&hls, &hls::PlaylistExtractor::done, [](auto playlist) {
    const auto masterPlaylist = std::dynamic_pointer_cast<hls::MasterPlaylist>(playlist);
    if (masterPlaylist) {
      for (auto stream : masterPlaylist->variantStreams()) {
        std::optional<hls::Media> audio;
        const auto it = std::find_if(std::begin(masterPlaylist->medias()),
                                     std::end(masterPlaylist->medias()),
                                     [stream](auto it) {return it.groupId() == stream.audio();});
        if (it != std::end(masterPlaylist->medias())) {
          audio = *it;
        }
        qDebug().noquote() << hls::toString(stream, audio) << "\n";
      }
    }
  });
  QObject::connect(&hls, &hls::PlaylistExtractor::error,
                   [](auto error) { qDebug() << error; });
  hls.extract("https://devstreaming-cdn.apple.com/videos/streaming/examples/"
              "img_bipbop_adv_example_ts/master.m3u8");
  return a.exec();
}
