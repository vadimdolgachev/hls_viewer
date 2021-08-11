#ifndef MEDIA_H
#define MEDIA_H

#include <QString>

#include <optional>

namespace hls {

class Media {
public:
  QString type() const;
  void setType(const QString &type);

  std::optional<QString> uri() const;
  void setUri(const QString &uri);

  QString groupId() const;
  void setGroupId(const QString &groupId);

  std::optional<QString> language() const;
  void setLanguage(const QString &language);

  std::optional<QString> assocLanguage() const;
  void setAssocLanguage(const QString &assocLanguage);

  QString name() const;
  void setName(const QString &name);

  std::optional<QString> defaultValue() const;
  void setDefaultValue(const QString &defaultValue);

  std::optional<QString> autoselect() const;
  void setAutoselect(const QString &autoselect);

  std::optional<QString> forced() const;
  void setForced(const QString &forced);

  std::optional<QString> instreamId() const;
  void setInstreamId(const QString &instreamId);

  std::optional<QString> characteristics() const;
  void setCharacteristics(const QString &characteristics);

  std::optional<QString> channels() const;
  void setChannels(const QString &channels);

private:
  QString mType;
  std::optional<QString> mUri;
  QString mGroupId;
  std::optional<QString> mLanguage;
  std::optional<QString> mAssocLanguage;
  QString mName;
  std::optional<QString> mDefaultValue;
  std::optional<QString> mAutoselect;
  std::optional<QString> mForced;
  std::optional<QString> mInstreamId;
  std::optional<QString> mCharacteristics;
  std::optional<QString> mChannels;
};
} // namespace hls

#endif // MEDIA_H
