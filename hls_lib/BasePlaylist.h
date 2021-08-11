#ifndef BASEPLAYLIST_H
#define BASEPLAYLIST_H

#include "Common.h"
#include "tags/Define.h"
#include "tags/Start.h"

#include <QString>

#include <optional>

namespace hls {

class BasePlaylist {
public:
  BasePlaylist();
  virtual ~BasePlaylist();

  int version() const;
  void setVersion(int version);

  bool isIndependentSegments() const;
  void setIndependentSegments(bool isIndependentSegments);

  std::optional<Define> define();
  void setDefine(const std::optional<Define>& define);

  std::optional<Start> start();
  void setStart(const std::optional<Start> &start);

private:
  int mVersion;
  bool mIsIndependentSegments;
  std::optional<Define> mDefine;
  std::optional<Start> mStart;
};

}

#endif // BASEPLAYLIST_H
