#ifndef VARIANSTREAMWIDGETITEM_H
#define VARIANSTREAMWIDGETITEM_H

#include <QWidget>

#include <tags/StreamInf.h>

namespace Ui {
class VarianStreamWidgetItem;
}

class VarianStreamWidgetItem : public QWidget
{
  Q_OBJECT

public:
  explicit VarianStreamWidgetItem(QString baseUrl,
                                  QString variantStremUri,
                                  std::optional<int> averageBandwith,
                                  QWidget *parent = nullptr);
  ~VarianStreamWidgetItem();

  void setText(const QString &text);

signals:
  void stopAllWorkers();
  void error(QString error);

public slots:
    void onDeviationAverageBitrateChanged(int pct);

private slots:
  void onPressedCheckBitrate();
  void onMeasureAverageBitrateDone(int minAverageSegmentBitrate,
                                   int maxAverageSegmentBitrate);
  void onMeasureAverageBitrateError(QString errorMsg);

private:
  void runMeasureAverageBitrate();

  Ui::VarianStreamWidgetItem *ui;
  QString mBaseUrl;
  QString mVariantStremUri;
  std::optional<int> mAverageBandwith;
  bool mMeasureAverageBitrateInProgress;
  int mDeviationAverageBitratePct;
  int mMinAverageBitrate;
  int mMaxAverageBitrate;
};

#endif // VARIANSTREAMWIDGETITEM_H
