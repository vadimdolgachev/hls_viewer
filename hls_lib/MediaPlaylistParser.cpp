#include "MediaPlaylist.h"
#include "MediaPlaylistParser.h"
#include "ParserStreamReader.h"

#include <QDebug>

namespace hls {

MediaPlaylistParser::MediaPlaylistParser()
{

}

std::unique_ptr<BasePlaylist> MediaPlaylistParser::parse(const QByteArray &data)
{
  ParserStreamReader reader(data);
  if (!reader.status()) {
    throw std::invalid_argument(errorReadFromStream().toStdString());
  }

  auto playlist = std::make_unique<hls::MediaPlaylist>();
  QSet<const char *> parsedTags;
  QList<MediaSegment> segments;

  while (!reader.atEnd()) {
    reader.readNextLine();

    if (reader.currentLine() == TAG_EXTM3U) {
      if (!parsedTags.contains(TAG_EXTM3U) && reader.currentLineNumber() == 1) {
        parsedTags.insert(TAG_EXTM3U);
      } else {
        throw std::invalid_argument(errorParsePlaylist(reader.currentLineNumber(),
                                                       reader.currentLine()).toStdString());
      }
    } else if (reader.currentLine().startsWith(TAG_VERSION)) {
      if (!parsedTags.contains(TAG_VERSION)) {
        parsedTags.insert(TAG_VERSION);
        playlist->setVersion(parseVersionTag(reader.currentLine()));
      } else {
        throw std::invalid_argument(errorParsePlaylist(reader.currentLineNumber(),
                                                       reader.currentLine()).toStdString());
      }
    } else if (reader.currentLine() == TAG_INDEPENDENT_SEGMENTS) {
      if (!parsedTags.contains(TAG_INDEPENDENT_SEGMENTS)) {
        parsedTags.insert(TAG_INDEPENDENT_SEGMENTS);
        playlist->setIndependentSegments(true);
      } else {
        throw std::invalid_argument(errorParsePlaylist(reader.currentLineNumber(),
                                                       reader.currentLine()).toStdString());
      }
    } else if (reader.currentLine().startsWith(TAG_TARGETDURATION)) {
      parsedTags.insert(TAG_TARGETDURATION);
      playlist->setTargetDuration(parseTargetdurationTag(reader.currentLine()));
    } else if (reader.currentLine().startsWith(TAG_MEDIA_SEQUENCE)) {
      parsedTags.insert(TAG_MEDIA_SEQUENCE);
      playlist->setMediaSequence(parseMediaSequenceTag(reader.currentLine()));
    } else if (reader.currentLine().startsWith(TAG_PLAYLIST_TYPE)) {
      parsedTags.insert(TAG_PLAYLIST_TYPE);
      playlist->setPlaylistType(parsePlaylistType(reader.currentLine()));
    } else if (reader.currentLine().startsWith(TAG_INF)) {
      MediaSegment segment;
      segment.setDuration(parseInfTag(reader.currentLine()));
      while (!reader.atEnd() && !(reader.nextLine().startsWith(TAG_INF)
                                  || reader.nextLine().startsWith(TAG_ENDLIST))) {
        reader.readNextLine();
      }
      segment.setUri(reader.currentLine());
      segments.append(segment);
    }
  }
  playlist->setSegments(segments);
  return std::move(playlist);
}

QString MediaPlaylistParser::parsePlaylistType(const QString &line)
{
  const auto &list = line.split(":");
  if (list.size() == 2) {
    return tagValueFromLine(TAG_PLAYLIST_TYPE, line);
  }
  return {};
}

int MediaPlaylistParser::parseMediaSequenceTag(const QString &line)
{
  const auto &list = line.split(":");
  if (list.size() == 2) {
    return tagValueFromLine(TAG_MEDIA_SEQUENCE, line).toInt();
  }
  return 0;
}

int MediaPlaylistParser::parseTargetdurationTag(const QString &line)
{
  const auto &list = line.split(":");
  if (list.size() == 2) {
    return tagValueFromLine(TAG_TARGETDURATION, line).toInt();
  }
  return 0;
}

float MediaPlaylistParser::parseInfTag(const QString &line)
{
  const auto &list = line.split(":");
  if (list.size() == 2) {
    return tagValueFromLine(TAG_INF,
                            line.split(",").value(0)).toFloat();
  }
  return 0;
}

} // namespace hls
