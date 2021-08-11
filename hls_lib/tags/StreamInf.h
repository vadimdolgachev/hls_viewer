#ifndef STREAMINF_H
#define STREAMINF_H

#include <QSize>
#include <QString>

#include <optional>

namespace hls {

class StreamInf
{
public:
  StreamInf();

  int bandwidth() const;
  void setBandwidth(int bandwidth);

  std::optional<int> averageBandwidth() const;
  void setAverageBandwidth(int averageBandwidth);

  QString codecs() const;
  void setCodecs(const QString &codecs);

  std::optional<QSize> resolution() const;
  void setResolution(const QSize &resolution);

  std::optional<float> frameRate() const;
  void setFrameRate(float frameRate);

  std::optional<QString> closedCaptions() const;
  void setClosedCaptions(const QString &closedCaptions);

  std::optional<QString> subtitles() const;
  void setSubtitles(const QString &subtitles);

  std::optional<QString> audio() const;
  void setAudio(const QString &audio);

  QString uri() const;
  void setUri(const QString &uri);

  std::optional<QString> video() const;
  void setVideo(const QString &video);

private:
  int mBandwidth;
  std::optional<int> mAverageBandwidth;
  QString mCodecs;
  std::optional<QSize> mResolution;
  std::optional<float> mFrameRate;
  std::optional<QString> mAudio;
  std::optional<QString> mVideo;
  std::optional<QString> mClosedCaptions;
  std::optional<QString> mSubtitles;
  QString mUri;
};

} // namespace hls

#endif // STREAMINF_H
