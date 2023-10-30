#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QVector>

#include "QtGifImage/src/gifimage/qgifimage.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GLWidget *glWidget;
  QTimer *timer;
  QGifImage *gif;
  int counter;
  QSettings *settings;

 private slots:
  void change_vertices_color();
  void change_edges_color();
  void on_background_color_btn_clicked();
  void on_load_from_file_btn_clicked();
  void on_screenshot_btn_clicked();
  void on_record_btn_clicked();
  void create_gif();
  void load_settings();
  void save_settings();
  void reset_settings();
};
#endif  // MAINWINDOW_H
