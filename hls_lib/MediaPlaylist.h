#ifndef MEDIAPLAYLIST_H
#define MEDIAPLAYLIST_H

#include "BasePlaylist.h"
#include "MediaSegment.h"

#include <QList>

namespace hls {

class MediaPlaylist : public BasePlaylist
{
public:
  MediaPlaylist();

  int targetDuration() const;
  void setTargetDuration(int targetDuration);

  int mediaSequence() const;
  void setMediaSequence(int mediaSequence);

  std::optional<QString> playlistType() const;
  void setPlaylistType(const QString &playlistType);

  QList<hls::MediaSegment> segments() const;
  void setSegments(const QList<hls::MediaSegment> &segments);

private:
  int mTargetDuration;
  int mMediaSequence;
  std::optional<QString> mPlaylistType;
  QList<hls::MediaSegment> mSegments;
};

}

#endif // MEDIAPLAYLIST_H
