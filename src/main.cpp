#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setOrganizationName("S21");
  QApplication::setApplicationName("3D_Viewer");

  MainWindow w;
  w.show();
  return a.exec();
}
