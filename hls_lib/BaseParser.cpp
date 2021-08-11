#include "BaseParser.h"

#include <QDebug>

namespace hls {

BaseParser::~BaseParser()
{

}

QString BaseParser::errorReadFromStream()
{
  return "Error read from stream";
}

QString BaseParser::errorParsePlaylist(int lineNumber, const QString &lineStr)
{
  return QString("Error parse m3u8 playlist at line: %1 : %2")
      .arg(lineNumber).arg(lineStr);
}

int hls::BaseParser::parseVersionTag(const QString &line)
{
  const auto &list = line.split(":");
  if (list.size() == 2) {
    return tagValueFromLine(TAG_VERSION, line).toInt();
  }
  return 0;
}

QString hls::BaseParser::tagValueFromLine(const QString &tag, const QString &line)
{
  auto list = line.split(tag);
  if (list.size() == 2) {
    return list[1].mid(1).trimmed();
  }
  return {};
}

int hls::BaseParser::parseInt(QString str)
{
  return str.toInt();
}

float hls::BaseParser::parseFloat(const QString &str)
{
  return str.toFloat();
}

} // namespace hls
