#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <PlaylistExtractor.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onPressedExtract();
  void onExctractorDone(std::shared_ptr<hls::BasePlaylist> playlist);
  void onExtractorError(QString error);
  void onVarianStreamWidgetItemError(QString error);

private:
  void showError(const QString &error);

  Ui::MainWindow *ui;
  hls::PlaylistExtractor mMasterPlaylistExtractor;
};
#endif // MAINWINDOW_H

