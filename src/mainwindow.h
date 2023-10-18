#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include "openglwidget.h"

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

};
#endif // MAINWINDOW_H

