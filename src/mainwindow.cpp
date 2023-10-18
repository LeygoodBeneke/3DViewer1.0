#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());
    glWidget = new GLWidget(ui->openGLWidget);
    glWidget->setFixedSize(1350, 1000); //need to check its size

    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(change_background_color()));
    connect(ui->load_from_file_btn,SIGNAL(clicked()),this,SLOT(load_file()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::load_file()
{
    QString path = QFileDialog::getOpenFileName(this, "Load a file", QDir::currentPath());
    QFileInfo fileInfo(path);
    if (!path.isEmpty()) {
        if (fileInfo.suffix() != "obj") {
            QMessageBox::warning(this, "Warning", "Invalid file extension. Expected '.obj'");
        } else {
            QString filename = fileInfo.fileName();
            //QFile file(filename);
            ui->Filename_Label->setText(filename);
        }
    }
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
