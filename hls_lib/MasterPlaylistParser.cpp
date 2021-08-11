#include "MasterPlaylistParser.h"
#include "ParserStreamReader.h"

#include <QTextStream>
#include <QDebug>

namespace hls {

std::unique_ptr<BasePlaylist> MasterPlaylistParser::parse(const QByteArray &data) {
  QSet<const char *> parsedTags;

  ParserStreamReader reader(data.trimmed());
  if (!reader.status()) {
    throw std::invalid_argument(errorReadFromStream().toStdString());
  }
  auto playlist = std::make_unique<MasterPlaylist>();
  QList<StreamInf> variantStreams;
  QList<Media> medias;
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
    } else if (reader.currentLine().startsWith(TAG_STREAM_INF)) {
      parsedTags.insert(TAG_STREAM_INF);
      const auto &line = reader.currentLine();
      const auto &uri = reader.readNextLine();
      variantStreams.append(parseStreamInfTag(line, uri));
    } else if (reader.currentLine().startsWith(TAG_MEDIA)) {
      parsedTags.insert(TAG_MEDIA);
      medias.append(parseMediaTag(reader.currentLine()));
    } else if (reader.currentLine().startsWith(TAG_I_FRAME_STREAM_INF)) {
      parsedTags.insert(TAG_I_FRAME_STREAM_INF);
    } else if (reader.currentLine().startsWith(TAG_SESSION_DATA)) {
      parsedTags.insert(TAG_SESSION_DATA);
    } else if (reader.currentLine().startsWith(TAG_SESSION_KEY)) {
      parsedTags.insert(TAG_SESSION_KEY);
    } else {
      throw std::invalid_argument(errorParsePlaylist(reader.currentLineNumber(),
                                                     reader.currentLine()).toStdString());
    }
  }
  playlist->setVariantStreams(variantStreams);
  playlist->setMedias(medias);
  return std::move(playlist);
}

StreamInf MasterPlaylistParser::parseStreamInfTag(const QString &tag,
                                                  const QString &uri)
{
  const auto &&attrs = parseTagAttrs(tagValueFromLine(TAG_STREAM_INF, tag));
  StreamInf si;
  si.setBandwidth(parseInt(attrs[ATTR_BANDWIDTH]));
  si.setAverageBandwidth(parseInt(attrs[ATTR_AVERAGE_BANDWIDTH]));
  si.setCodecs(parseString(attrs[ATTR_CODECS]));
  si.setResolution(parseResolution(attrs[ATTR_RESOLUTION]));
  si.setFrameRate(parseFloat(attrs[ATTR_FRAME_RATE]));
  si.setClosedCaptions(parseString(attrs[ATTR_CLOSED_CAPTIONS]));
  si.setAudio(parseString(attrs[ATTR_AUDIO]));
  si.setSubtitles(parseString(attrs[ATTR_SUBTITLES]));
  si.setUri(uri);
  return si;
}

Media MasterPlaylistParser::parseMediaTag(const QString &tag)
{
  const auto &&attrs = parseTagAttrs(tagValueFromLine(TAG_MEDIA, tag));
  Media media;
  media.setType(parseType(attrs[ATTR_TYPE]));
  media.setUri(parseString(attrs[ATTR_URI]));
  media.setGroupId(parseString(attrs[ATTR_GROUP_ID]));
  if (attrs.contains(ATTR_LANGUAGE)) {
    media.setLanguage(parseString(attrs[ATTR_LANGUAGE]));
  }
  media.setAssocLanguage(parseString(attrs[ATTR_ASSOC_LANGUAGE]));
  media.setName(parseString(attrs[ATTR_NAME]));
  media.setDefaultValue(parseString(attrs[ATTR_DEFAULT]));
  media.setAutoselect(parseString(attrs[ATTR_AUTOSELECT]));
  media.setForced(parseString(attrs[ATTR_FORCED]));
  media.setInstreamId(parseString(attrs[ATTR_INSTREAM_ID]));
  media.setCharacteristics(parseString(attrs[ATTR_CHARACTERISTICS]));

  if (attrs.contains(ATTR_CHANNELS)) {
    media.setChannels(parseString(attrs[ATTR_CHANNELS]));
  }
  return media;
}

QSize MasterPlaylistParser::parseResolution(const QString &str)
{
  QSize size;
  const auto &&list = str.split("x");
  if (list.size() == 2) {
    size.setWidth(list[0].toInt());
    size.setHeight(list[1].toInt());
  }
  return size;
}

QMap<QString, QString> MasterPlaylistParser::parseTagAttrs(const QString &tagValue)
{
  QMap<QString, QString> map;
  int cursor = 0;
  while (true) {
    // find attribute name
    int index = tagValue.indexOf('=', cursor);
    if (index < 0) {
      break;
    }
    const auto &&attr = tagValue.mid(cursor, index - cursor);
    cursor = index + 1;
    // find attribute value
    if (tagValue.at(cursor) == '"') {
      // quoted-string value
      index = tagValue.indexOf('"', cursor + 1) + 1;
    } else {
      // number and enum value
      index = tagValue.indexOf(',', cursor);
    }
    if (index < 0) {
      index = tagValue.size();
    }
    const auto &&val = tagValue.mid(cursor, index - cursor);
    cursor = index + 1;
    map[attr] = val;
  }
  return map;
}

QString MasterPlaylistParser::parseType(const QString &str)
{
  // parse to enumerate value Type
  return str;
}

QString MasterPlaylistParser::parseString(const QString &str)
{
  return QString(str).remove('"');
}

} // namespace hls

