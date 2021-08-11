#include "StreamInf.h"

namespace hls {

StreamInf::StreamInf() :
  mBandwidth(0)
{

}

std::optional<int> StreamInf::averageBandwidth() const
{
  return mAverageBandwidth;
}

void StreamInf::setAverageBandwidth(int averageBandwidth)
{
  mAverageBandwidth = averageBandwidth;
}

int StreamInf::bandwidth() const
{
  return mBandwidth;
}

void StreamInf::setBandwidth(int bandwidth)
{
  mBandwidth = bandwidth;
}

QString StreamInf::codecs() const
{
  return mCodecs;
}

void StreamInf::setCodecs(const QString &condecs)
{
  mCodecs = condecs;
}

std::optional<QSize> StreamInf::resolution() const
{
  return mResolution;
}

void StreamInf::setResolution(const QSize &resolution)
{
  mResolution = resolution;
}

std::optional<float> StreamInf::frameRate() const
{
  return mFrameRate;
}

void StreamInf::setFrameRate(float frameRate)
{
  mFrameRate = frameRate;
}

std::optional<QString> StreamInf::closedCaptions() const
{
  return mClosedCaptions;
}

void StreamInf::setClosedCaptions(const QString &closedCaptions)
{
  mClosedCaptions = closedCaptions;
}

std::optional<QString> StreamInf::subtitles() const
{
  return mSubtitles;
}

void StreamInf::setSubtitles(const QString &subtitles)
{
  mSubtitles = subtitles;
}

std::optional<QString> StreamInf::audio() const
{
  return mAudio;
}

void StreamInf::setAudio(const QString &audio)
{
  mAudio = audio;
}

QString StreamInf::uri() const
{
  return mUri;
}

void StreamInf::setUri(const QString &uri)
{
  mUri = uri;
}

std::optional<QString> StreamInf::video() const
{
  return mVideo;
}

void StreamInf::setVideo(const QString &video)
{
  mVideo = video;
}

} // namespace hls
