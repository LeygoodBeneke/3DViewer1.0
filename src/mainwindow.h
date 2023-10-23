#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QPixmap>
#include <QImage>
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

 private slots:
  void change_background_color();
  void change_vertices_color();
  void load_file();
  void take_screenshot();
  void create_gif();

  void set_rotation_x(double x);
  void set_rotation_y(double x);
  void set_rotation_z(double x);

  void set_vertices_size(int value);

};
#endif // MAINWINDOW_H

