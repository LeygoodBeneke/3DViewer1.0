#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setOrganizationName("S21");
  QApplication::setApplicationName("3D_Viewer");

  MainWindow w;


  QFile file("style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  qApp->setStyleSheet(styleSheet);
  file.close();

  w.show();
  return a.exec();
}
