#ifndef START_H
#define START_H

#include <QString>

#include <optional>

namespace hls {

class Start {
public:
  Start();

  void setTimeOffset(float timeOffset);
  float timeOffset();
  std::optional<QString> precise();
  void setPrecise(const std::optional<QString> &precise);

private:
  float mTimeOffset;
  std::optional<QString> mPrecise;
};
}

#endif // START_H
