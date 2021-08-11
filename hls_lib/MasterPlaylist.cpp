#include <QDebug>

#include "MasterPlaylist.h"

namespace hls {

MasterPlaylist::MasterPlaylist()
{

}

MasterPlaylist::~MasterPlaylist()
{

}

QList<StreamInf> MasterPlaylist::variantStreams()
{
  return mVariantStreams;
}

QList<Media> MasterPlaylist::medias() const
{
  return mMedias;
}

void MasterPlaylist::setVariantStreams(const QList<StreamInf> &variantStreams)
{
  mVariantStreams = variantStreams;
}

void MasterPlaylist::setMedias(const QList<Media> &medias)
{
  mMedias = medias;
}

} // namespace hls
