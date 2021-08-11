#include "Start.h"

namespace hls {

Start::Start() :
  mTimeOffset(0)
{

}

float Start::timeOffset()
{
  return mTimeOffset;
}

std::optional<QString> Start::precise()
{
  return mPrecise;
}

void Start::setTimeOffset(float timeOffset)
{
  mTimeOffset = timeOffset;
}

void Start::setPrecise(const std::optional<QString> &precise)
{
  mPrecise = precise;
}

} // namespace hls
