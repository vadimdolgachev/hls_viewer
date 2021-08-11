#include "BasePlaylist.h"

#include <QDebug>

namespace hls {

BasePlaylist::BasePlaylist() :
  mVersion(1),
  mIsIndependentSegments(false)
{

}

BasePlaylist::~BasePlaylist()
{

}

int BasePlaylist::version() const
{
  return mVersion;
}

bool BasePlaylist::isIndependentSegments() const
{
  return mIsIndependentSegments;
}

std::optional<Define> BasePlaylist::define()
{
  return mDefine;
}

std::optional<Start> BasePlaylist::start()
{
  return mStart;
}

void BasePlaylist::setDefine(const std::optional<Define> &define)
{
  mDefine = define;
}

void BasePlaylist::setStart(const std::optional<Start> &start)
{
  mStart = start;
}

void BasePlaylist::setIndependentSegments(bool isIndependentSegments)
{
  mIsIndependentSegments = isIndependentSegments;
}

void BasePlaylist::setVersion(int version)
{
  mVersion = version;
}

} // namespace hls
