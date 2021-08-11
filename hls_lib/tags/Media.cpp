#include "Media.h"

namespace hls {

QString Media::type() const
{
  return mType;
}

void Media::setType(const QString &type)
{
  mType = type;
}

std::optional<QString> Media::uri() const {
  return mUri;
}

void Media::setUri(const QString& uri) {
  mUri = uri;
}

QString Media::groupId() const
{
  return mGroupId;
}

void Media::setGroupId(const QString &groupId)
{
  mGroupId = groupId;
}

std::optional<QString> Media::language() const {
  return mLanguage;
}

void Media::setLanguage(const QString& language) {
  mLanguage = language;
}

std::optional<QString> Media::assocLanguage() const {
  return mAssocLanguage;
}

void Media::setAssocLanguage(const QString& assocLanguage) {
  mAssocLanguage = assocLanguage;
}

QString Media::name() const
{
  return mName;
}

void Media::setName(const QString &name)
{
  mName = name;
}

std::optional<QString> Media::defaultValue() const {
  return mDefaultValue;
}

void Media::setDefaultValue(const QString& defaultValue) {
  mDefaultValue = defaultValue;
}

std::optional<QString> Media::autoselect() const {
  return mAutoselect;
}

void Media::setAutoselect(const QString& autoselect) {
  mAutoselect = autoselect;
}

std::optional<QString> Media::forced() const {
  return mForced;
}

void Media::setForced(const QString& forced) {
  mForced = forced;
}

std::optional<QString> Media::instreamId() const {
  return mInstreamId;
}

void Media::setInstreamId(const QString& instreamId) {
  mInstreamId = instreamId;
}

std::optional<QString> Media::characteristics() const {
  return mCharacteristics;
}

void Media::setCharacteristics(const QString& characteristics) {
  mCharacteristics = characteristics;
}

std::optional<QString> Media::channels() const {
  return mChannels;
}

void Media::setChannels(const QString& channels) {
  mChannels = channels;
}

} // namespace hls
