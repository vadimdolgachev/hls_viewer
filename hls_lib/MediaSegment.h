#ifndef MEDIASEGMENT_H
#define MEDIASEGMENT_H

#include <QString>

namespace hls {

class MediaSegment
{
public:
  MediaSegment();

  float duration() const;
  void setDuration(float duration);

  QString uri() const;
  void setUri(const QString &uri);

private:
  float mDuration;
  QString mUri;
};

}

#endif // MEDIASEGMENT_H
