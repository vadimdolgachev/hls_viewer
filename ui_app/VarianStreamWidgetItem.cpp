#include "VarianStreamWidgetItem.h"
#include "ui_VarianStreamWidgetItem.h"
#include "Common.h"

#include <AvrageBitrateMeasurment.h>
#include <QDebug>
#include <QThread>

#include <cmath>

VarianStreamWidgetItem::VarianStreamWidgetItem(QString baseUrl,
                                               QString variantStremUri,
                                               std::optional<int> averageBandwith,
                                               QWidget *parent) :
  QWidget(parent),
  ui(new Ui::VarianStreamWidgetItem),
  mBaseUrl(baseUrl),
  mVariantStremUri(variantStremUri),
  mAverageBandwith(averageBandwith),
  mMeasureAverageBitrateInProgress(false),
  mDeviationAverageBitratePct(0),
  mMinAverageBitrate(0),
  mMaxAverageBitrate(0)
{
  ui->setupUi(this);

  connect(ui->checkPushButton, &QPushButton::pressed,
          this, &VarianStreamWidgetItem::onPressedCheckBitrate);
}

VarianStreamWidgetItem::~VarianStreamWidgetItem()
{
  emit stopAllWorkers();
  delete ui;
}

void VarianStreamWidgetItem::setText(const QString &text)
{
  ui->descriptonLabel->setText(text);
}

void VarianStreamWidgetItem::onDeviationAverageBitrateChanged(int pct)
{
  mDeviationAverageBitratePct = pct;
  onMeasureAverageBitrateDone(mMinAverageBitrate, mMaxAverageBitrate);
}

void VarianStreamWidgetItem::onPressedCheckBitrate()
{
  qDebug() << Q_FUNC_INFO;
  if (!mMeasureAverageBitrateInProgress) {
    runMeasureAverageBitrate();
  }
}

void VarianStreamWidgetItem::onMeasureAverageBitrateDone(int minAverageBitrate,
                                                         int maxAverageBitrate)
{
  mMeasureAverageBitrateInProgress = false;
  if (minAverageBitrate > 0 && maxAverageBitrate > 0) {
    mMinAverageBitrate = minAverageBitrate;
    mMaxAverageBitrate = maxAverageBitrate;
    if (mAverageBandwith && mAverageBandwith.value() > 0) {
      const auto ok = hls::checkAverageBitrate(mAverageBandwith.value(),
                                               mDeviationAverageBitratePct,
                                               mMinAverageBitrate,
                                               mMaxAverageBitrate);
      qDebug() << Q_FUNC_INFO << mMinAverageBitrate << mMaxAverageBitrate
               << mDeviationAverageBitratePct << ok;
      ui->checkPushButton->setText(ok ? tr("PASSED") : tr("NOT PASSED"));
    }
    ui->checkPushButton->setEnabled(false);
  }
}

void VarianStreamWidgetItem::onMeasureAverageBitrateError(QString errorMsg)
{
  ui->checkPushButton->setText(tr("Press to check"));
  emit error(errorMsg);
}

void VarianStreamWidgetItem::runMeasureAverageBitrate()
{
  const auto measurer = new hls::AvrageBitrateMeasurment(mBaseUrl, mVariantStremUri);
  const auto thread = new QThread;
  measurer->moveToThread(thread);
  connect(thread, &QThread::started,
          measurer, &hls::AvrageBitrateMeasurment::measure);
  connect(measurer, &hls::AvrageBitrateMeasurment::started,
          this, [this]() {
    ui->checkPushButton->setText(tr("Сalculation"));
    mMeasureAverageBitrateInProgress = true;
  });
  connect(measurer, &hls::AvrageBitrateMeasurment::done,
          this, &VarianStreamWidgetItem::onMeasureAverageBitrateDone);
  connect(measurer, &hls::AvrageBitrateMeasurment::error,
          this, &VarianStreamWidgetItem::onMeasureAverageBitrateError);
  connect(this, &VarianStreamWidgetItem::stopAllWorkers,
          measurer, &hls::AvrageBitrateMeasurment::stop);
  connect(measurer, &hls::AvrageBitrateMeasurment::done,
          thread, &QThread::quit);
  connect(measurer, &hls::AvrageBitrateMeasurment::done,
          measurer, &hls::AvrageBitrateMeasurment::deleteLater);
  connect(thread, &QThread::finished,
          thread, &QThread::deleteLater);
  thread->start();
}
