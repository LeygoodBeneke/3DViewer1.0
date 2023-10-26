#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QImage>
#include <QTimer>
#include <QSettings>
#include <QDebug>
#include "QtGifImage/src/gifimage/qgifimage.h"

#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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
  void on_bg_btn_clicked();
  void on_load_file_btn_clicked();
  void on_snap_btn_clicked();
  void on_gif_btn_clicked();
  void create_gif();
  void load_settings();
  void save_settings();
  void reset_settings();
};
#endif // MAINWINDOW_H

