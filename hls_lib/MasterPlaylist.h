#ifndef MASTERPLAYLIST_H
#define MASTERPLAYLIST_H

#include "BasePlaylist.h"
#include "tags/StreamInf.h"
#include "tags/Media.h"

#include <QList>
#include <QString>

namespace hls {

class MasterPlaylist : public BasePlaylist {
public:
  MasterPlaylist();
  ~MasterPlaylist();

  QList<StreamInf> variantStreams();
  void setVariantStreams(const QList<StreamInf> &variantStreams);

  QList<Media> medias() const;
  void setMedias(const QList<Media> &medias);

private:
  QList<StreamInf> mVariantStreams;
  QList<Media> mMedias;
};
}  // namespace hls

#endif // MASTERPLAYLIST_H
