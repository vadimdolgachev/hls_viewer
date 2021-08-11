#include "MediaPlaylist.h"

namespace hls {

MediaPlaylist::MediaPlaylist() :
  mTargetDuration(0),
  mMediaSequence(0)
{

}

int MediaPlaylist::targetDuration() const
{
  return mTargetDuration;
}

void MediaPlaylist::setTargetDuration(int targetDuration)
{
  mTargetDuration = targetDuration;
}

int MediaPlaylist::mediaSequence() const
{
  return mMediaSequence;
}

void MediaPlaylist::setMediaSequence(int mediaSequence)
{
  mMediaSequence = mediaSequence;
}

std::optional<QString> MediaPlaylist::playlistType() const
{
  return mPlaylistType;
}

void MediaPlaylist::setPlaylistType(const QString &playlistType)
{
  mPlaylistType = playlistType;
}

QList<hls::MediaSegment> MediaPlaylist::segments() const
{
  return mSegments;
}

void MediaPlaylist::setSegments(const QList<hls::MediaSegment> &segments)
{
  mSegments = segments;
}

} // namespace hls
