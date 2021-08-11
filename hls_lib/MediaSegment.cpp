#include "MediaSegment.h"

namespace hls {

MediaSegment::MediaSegment()
{

}

float MediaSegment::duration() const
{
  return mDuration;
}

void MediaSegment::setDuration(float duration)
{
  mDuration = duration;
}

QString MediaSegment::uri() const
{
  return mUri;
}

void MediaSegment::setUri(const QString &uri)
{
  mUri = uri;
}

} // namespace hls
