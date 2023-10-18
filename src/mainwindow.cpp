#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = new GLWidget(ui->openGLWidget);
    glWidget->setFixedSize(1350, 1000); //need to check its size
    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(change_background_color()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::change_background_color()
{
  QColor bg = glWidget->get_background();
  QColor new_bg = QColorDialog::getColor(bg, this, tr("Background Color:"));
  if (new_bg.isValid()) {
    glWidget->set_background(new_bg);
    glWidget->update();
    }
}
