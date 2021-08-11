#include "MainWindow.h"
#include "VarianStreamWidgetItem.h"
#include "ui_MainWindow.h"
#include "PlaylistExtractor.h"
#include "MasterPlaylistParser.h"

#include <AvrageBitrateMeasurment.h>
#include <QTextEdit>
#include <QMessageBox>
#include <QAbstractItemView>

#include <memory>

const auto STARTED_HLS_PLAYLIST = "https://devstreaming-cdn.apple.com/videos/streaming"
                                  "/examples/img_bipbop_adv_example_ts/master.m3u8";

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mMasterPlaylistExtractor(std::make_unique<hls::MasterPlaylistParser>())
{
  ui->setupUi(this);

  connect(&mMasterPlaylistExtractor, &hls::PlaylistExtractor::done,
          this, &MainWindow::onExctractorDone);
  connect(&mMasterPlaylistExtractor, &hls::PlaylistExtractor::error,
          this, &MainWindow::onExtractorError);

  connect(ui->extractPushButton, &QPushButton::pressed,
          this, &MainWindow::onPressedExtract);

  ui->playlistUrlLineEdit->setText(STARTED_HLS_PLAYLIST);
  ui->playlistUrlLineEdit->setCursorPosition(0);
  ui->deviationSpinBox->setValue(hls::DEVIATION_AVERAGE_BITRATE_VOD_PCT);
  ui->deviationSpinBox->setMaximum(100);
  ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
  ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::onPressedExtract()
{
  const auto url = ui->playlistUrlLineEdit->text();
  mMasterPlaylistExtractor.extract(url);
  setEnabled(false);
  ui->listWidget->clear();
}

void MainWindow::onExctractorDone(std::shared_ptr<hls::BasePlaylist> playlist)
{
  const auto masterPlaylist = std::dynamic_pointer_cast<hls::MasterPlaylist>(playlist);

  if (masterPlaylist) {
    for (auto stream : masterPlaylist->variantStreams()) {
      std::optional<hls::Media> audio;
      const auto it = std::find_if(std::begin(masterPlaylist->medias()),
                                   std::end(masterPlaylist->medias()),
                                   [stream](auto it) {return it.groupId() == stream.audio();});
      if (it != std::end(masterPlaylist->medias())) {
        audio = *it;
      }
      auto widget = new VarianStreamWidgetItem(hls::baseUrl(ui->playlistUrlLineEdit->text()),
                                               stream.uri(),
                                               stream.averageBandwidth());
      connect(ui->deviationSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
              widget, &VarianStreamWidgetItem::onDeviationAverageBitrateChanged);
      connect(widget, &VarianStreamWidgetItem::error,
              this, &MainWindow::onVarianStreamWidgetItemError);
      widget->onDeviationAverageBitrateChanged(ui->deviationSpinBox->value());
      widget->setText(hls::toString(stream, audio));
      const auto item = new QListWidgetItem(ui->listWidget);
      item->setSizeHint(widget->sizeHint());
      ui->listWidget->setItemWidget(item, widget);
    }
  }
  setEnabled(true);
}

void MainWindow::onExtractorError(QString error)
{
  setEnabled(true);
  showError(error);
}

void MainWindow::onVarianStreamWidgetItemError(QString error)
{
  showError(error);
}

void MainWindow::showError(const QString &error)
{
  QMessageBox::critical(this, tr("Error"), error);
}
