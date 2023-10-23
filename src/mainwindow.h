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
  void load_file();
  void take_screenshot();
  void create_gif();
//  void load_settings();
//  void save_settings();
};
#endif // MAINWINDOW_H

