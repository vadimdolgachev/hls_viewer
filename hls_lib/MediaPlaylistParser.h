#ifndef MEDIAPLAYLISTPARSER_H
#define MEDIAPLAYLISTPARSER_H

#include "BaseParser.h"

namespace hls {

class MediaPlaylistParser : public BaseParser
{
public:
  MediaPlaylistParser();

  std::unique_ptr<BasePlaylist> parse(const QByteArray &data);

private:
  static QString parsePlaylistType(const QString &line);
  static int parseMediaSequenceTag(const QString &line);
  static int parseTargetdurationTag(const QString &line);
  static float parseInfTag(const QString &line);
};

}

#endif // MEDIAPLAYLISTPARSER_H
