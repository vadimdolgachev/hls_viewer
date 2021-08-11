#include "Define.h"

namespace hls {

std::optional<QString> Define::name() const
{
  return mName;
}

void Define::setName(const std::optional<QString>& name)
{
  mName = name;
}

std::optional<QString> Define::value() const
{
  return mValue;
}

void Define::setValue(const std::optional<QString>& value)
{
  mValue = value;
}

std::optional<QString> Define::import() const
{
  return mImport;
}

void Define::setImport(const std::optional<QString> &import)
{
  mImport = import;
}

} // namespace hls
