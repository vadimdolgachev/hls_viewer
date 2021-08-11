#include "Common.h"

#include <QStringList>
#include <QTextStream>
#include <QDebug>

#include <cmath>

QString hls::baseUrl(const QString &url)
{
  QString baseUrl(url);
  const auto i = baseUrl.lastIndexOf('/');
  if (i > 0) {
    baseUrl.remove(i + 1, url.size() - i);
  }
  return baseUrl;
}

QString hls::toString(const StreamInf &stream, const std::optional<Media> &audio)
{
  QString description;
  QTextStream ts(&description);
  ts << "Bandwidth: " << stream.bandwidth();
  if (stream.averageBandwidth()) {
    ts << endl << "Average bandwidth: " << stream.averageBandwidth().value();
  }
  ts << endl << "Codecs: " << stream.codecs();
  if (stream.resolution()) {
    ts << endl << "Resolution: " << QString("%1x%2")
          .arg(stream.resolution().value().width())
          .arg(stream.resolution().value().height());
  }
  if (stream.frameRate()) {
    ts << endl << "Frame rate: " << stream.frameRate().value();
  }
  ts << endl << "Uri: " << stream.uri();
  if (audio) {
    ts << endl << "Audio rendition:";
    ts  << endl << "Name: " << audio->name();
    if (audio->uri()) {
      ts << endl << "Uri: " << audio->uri().value();
    }
    if (audio->channels()) {
      ts << endl << "Channels: " << audio->channels().value();
    }
    if (audio->language()) {
      ts << endl << "Language: " << audio->language().value();
    }
  }
  return description;
}

bool hls::checkAverageBitrate(int bandwith,
                              int mDeviationPct,
                              int minAverageBitrate,
                              int maxAverageBitrate)
{
  auto deviation = std::lround(100.f * std::abs(bandwith - minAverageBitrate) / bandwith);
  const auto ok = deviation <= mDeviationPct;
  deviation = std::lround(100.f * std::abs(bandwith - maxAverageBitrate) / bandwith);
  return ok && deviation <= mDeviationPct;
}

const int hls::DEVIATION_AVERAGE_BITRATE_VOD_PCT = 10;
const int hls::BITS_PER_BYTE = 8;
const char * const hls::PLAYLIST_TYPE_VOD = "VOD";

const char * const hls::TAG_EXTM3U = "#EXTM3U";
const char * const hls::TAG_VERSION = "#EXT-X-VERSION";
const char * const hls::TAG_INDEPENDENT_SEGMENTS = "#EXT-X-INDEPENDENT-SEGMENTS";
const char * const hls::TAG_STREAM_INF = "#EXT-X-STREAM-INF";
const char * const hls::TAG_MEDIA = "#EXT-X-MEDIA";
const char * const hls::TAG_I_FRAME_STREAM_INF = "#EXT-X-I-FRAME-STREAM-INF";
const char * const hls::TAG_SESSION_DATA = "#EXT-X-SESSION-DATA";
const char * const hls::TAG_SESSION_KEY = "#EXT-X-SESSION-KEY";
const char * const hls::TAG_TARGETDURATION = "#EXT-X-TARGETDURATION";
const char * const hls::TAG_MEDIA_SEQUENCE = "#EXT-X-MEDIA-SEQUENCE";
const char * const hls::TAG_PLAYLIST_TYPE = "#EXT-X-PLAYLIST-TYPE";
const char * const hls::TAG_INF = "#EXTINF";
const char * const hls::TAG_ENDLIST = "#EXT-X-ENDLIST";

const char * const hls::ATTR_AVERAGE_BANDWIDTH = "AVERAGE-BANDWIDTH";
const char * const hls::ATTR_BANDWIDTH = "BANDWIDTH";
const char * const hls::ATTR_CODECS = "CODECS";
const char * const hls::ATTR_RESOLUTION = "RESOLUTION";
const char * const hls::ATTR_FRAME_RATE = "FRAME-RATE";
const char * const hls::ATTR_CLOSED_CAPTIONS = "CLOSED-CAPTIONS";
const char * const hls::ATTR_AUDIO = "AUDIO";
const char * const hls::ATTR_SUBTITLES = "SUBTITLES";
const char * const hls::ATTR_URI = "URI";
const char * const hls::ATTR_TYPE = "TYPE";
const char * const hls::ATTR_GROUP_ID = "GROUP-ID";
const char * const hls::ATTR_LANGUAGE = "LANGUAGE";
const char * const hls::ATTR_ASSOC_LANGUAGE = "ASSOC-LANGUAGE";
const char * const hls::ATTR_NAME = "NAME";
const char * const hls::ATTR_DEFAULT = "DEFAULT";
const char * const hls::ATTR_AUTOSELECT = "AUTOSELECT";
const char * const hls::ATTR_FORCED = "FORCED";
const char * const hls::ATTR_INSTREAM_ID = "INSTREAM-ID";
const char * const hls::ATTR_CHARACTERISTICS = "CHARACTERISTICS";
const char * const hls::ATTR_CHANNELS = "CHANNELS";
