#ifndef PARSERTEXTSTREAM_H
#define PARSERTEXTSTREAM_H

#include <QByteArray>
#include <QString>
#include <QTextStream>

namespace hls {

class ParserStreamReader
{
public:
  ParserStreamReader(const QByteArray &data);

  QString readNextLine();
  QString nextLine();
  bool atEnd() const;
  bool status() const;
  int currentLineNumber() const;
  QString currentLine() const;

private:
  QString readRealLine();

  QTextStream mTS;
  int mLineNumber;
  QString mLine;
};

}

#endif // PARSERTEXTSTREAM_H
