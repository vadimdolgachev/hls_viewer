#ifndef COMMON_H
#define COMMON_H

#include <QString>

#include <tags/Media.h>
#include <tags/StreamInf.h>

namespace hls
{

QString baseUrl(const QString &url);
QString toString(const StreamInf &stream, const std::optional<Media> &media = {});
bool checkAverageBitrate(int bandwith,
                         int mDeviationPct,
                         int minAverageBitrate,
                         int maxAverageBitrate);

extern const int DEVIATION_AVERAGE_BITRATE_VOD_PCT;
extern const int BITS_PER_BYTE;
extern const char * const PLAYLIST_TYPE_VOD;

// tags
extern const char * const TAG_EXTM3U;
extern const char * const TAG_VERSION;
extern const char * const TAG_INDEPENDENT_SEGMENTS;
extern const char * const TAG_STREAM_INF;
extern const char * const TAG_MEDIA;
extern const char * const TAG_I_FRAME_STREAM_INF;
extern const char * const TAG_SESSION_DATA;
extern const char * const TAG_SESSION_KEY;
extern const char * const TAG_TARGETDURATION;
extern const char * const TAG_MEDIA_SEQUENCE;
extern const char * const TAG_PLAYLIST_TYPE;
extern const char * const TAG_INF;
extern const char * const TAG_ENDLIST;

// attributes
extern const char * const ATTR_AVERAGE_BANDWIDTH;
extern const char * const ATTR_BANDWIDTH;
extern const char * const ATTR_CODECS;
extern const char * const ATTR_RESOLUTION;
extern const char * const ATTR_FRAME_RATE;
extern const char * const ATTR_CLOSED_CAPTIONS;
extern const char * const ATTR_AUDIO;
extern const char * const ATTR_SUBTITLES;
extern const char * const ATTR_URI;
extern const char * const ATTR_TYPE;
extern const char * const ATTR_GROUP_ID;
extern const char * const ATTR_LANGUAGE;
extern const char * const ATTR_ASSOC_LANGUAGE;
extern const char * const ATTR_NAME;
extern const char * const ATTR_DEFAULT;
extern const char * const ATTR_AUTOSELECT;
extern const char * const ATTR_FORCED;
extern const char * const ATTR_INSTREAM_ID;
extern const char * const ATTR_CHARACTERISTICS;
extern const char * const ATTR_CHANNELS;

}; // namespace hls

#endif // COMMON_H
