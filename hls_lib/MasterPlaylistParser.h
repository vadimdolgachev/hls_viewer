#ifndef MASTERPLAYLISTPARSER_H
#define MASTERPLAYLISTPARSER_H

#include "MasterPlaylist.h"
#include "BaseParser.h"
#include "tags/Media.h"

#include <QByteArray>
#include <QSet>

namespace hls {

class MasterPlaylistParser : public BaseParser {
public:
  std::unique_ptr<BasePlaylist> parse(const QByteArray& data);

private:
  static StreamInf parseStreamInfTag(const QString &tag, const QString &uri);
  static Media parseMediaTag(const QString &tag);
  static QString parseString(const QString &str);
  static QSize parseResolution(const QString &str);
  static QMap<QString, QString> parseTagAttrs(const QString &tagValue);
  static QString parseType(const QString &str);
};
} // namespace hls

#endif // MASTERPLAYLISTPARSER_H
