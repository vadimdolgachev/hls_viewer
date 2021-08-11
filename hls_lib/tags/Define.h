#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

#include <optional>

namespace hls {

class Define {
public:
  std::optional<QString> name() const;
  void setName(const std::optional<QString> &name);

  std::optional<QString> value() const;
  void setValue(const std::optional<QString> &value);

  std::optional<QString> import() const;
  void setImport(const std::optional<QString> &import);

private:
  std::optional<QString> mName;
  std::optional<QString> mValue;
  std::optional<QString> mImport;
};
}

#endif // DEFINE_H
