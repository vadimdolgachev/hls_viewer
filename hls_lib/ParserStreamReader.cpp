#include "ParserStreamReader.h"

#include <QDebug>

namespace hls {

ParserStreamReader::ParserStreamReader(const QByteArray &data) :
  mTS(data),
  mLineNumber(0)
{

}

QString ParserStreamReader::readNextLine()
{
  return readRealLine();
}

bool ParserStreamReader::atEnd() const
{
  return mTS.atEnd();
}

bool ParserStreamReader::status() const
{
  return mTS.status() == QTextStream::Ok;
}

int ParserStreamReader::currentLineNumber() const
{
  return mLineNumber;
}

QString ParserStreamReader::currentLine() const
{
  return mLine;
}

QString ParserStreamReader::nextLine()
{
  const auto p = mTS.pos();
  const auto line = mTS.readLine();
  mTS.seek(p);
  return line;
}

QString ParserStreamReader::readRealLine()
{
  while (!mTS.atEnd()) {
    const auto &&line = mTS.readLine();
    if (!line.isEmpty()) {
      ++mLineNumber;
      mLine = line;
      return line;
    }
  }
  return {};
}

} // namespace hls
