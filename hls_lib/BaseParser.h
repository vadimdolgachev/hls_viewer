#ifndef BASEPARSER_H
#define BASEPARSER_H

#include "BasePlaylist.h"

#include <memory>

namespace hls {

class BaseParser {
public:
  virtual ~BaseParser();

  virtual std::unique_ptr<BasePlaylist> parse(const QByteArray &data) = 0;

protected:
  static QString errorReadFromStream();
  static QString errorParsePlaylist(int lineNumber, const QString &lineStr);
  static int parseVersionTag(const QString &line);
  static QString tagValueFromLine(const QString &tag, const QString &line);
  static int parseInt(QString str);
  static float parseFloat(const QString &str);
};

} // namespace hls

#endif // BASEPARSER
