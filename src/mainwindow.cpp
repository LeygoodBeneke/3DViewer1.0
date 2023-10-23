#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = ui->widget;

    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(change_background_color()));

    connect(ui->vertices_color_btn,SIGNAL(clicked()),this,SLOT(change_vertices_color()));

    connect(ui->load_from_file_btn,SIGNAL(clicked()),this,SLOT(load_file()));
    connect(ui->screenshot_btn,SIGNAL(clicked()),this,SLOT(take_screenshot()));



    //connect(ui->record_btn,SIGNAL(clicked()),this,SLOT(create_gif()));

    connect(ui->record_btn,SIGNAL(clicked()),this,SLOT(rotation_x()));


    //connect(ui->rotation_x_spinbox, SIGNAL(valueChanged(int)), this, SLOT(set_rotation_x(int)));

    connect (ui->rotation_x_spinbox, SIGNAL(valueChanged(double)),this, SLOT(set_rotation_x(double)));
    connect (ui->rotation_y_spinbox, SIGNAL(valueChanged(double)),this, SLOT(set_rotation_y(double)));
    connect (ui->rotation_z_spinbox, SIGNAL(valueChanged(double)),this, SLOT(set_rotation_z(double)));


    connect (ui->vertices_display_method_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(set_vertices_method(int)));

    connect (ui->vertices_size_slider, SIGNAL(valueChanged(int)),this, SLOT(set_vertices_size(int)));
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
            QMessageBox::warning(this, "Warning!", "Invalid file extension. Expected '.obj'");
        } else {
            glWidget->modelPath = path;
            QString filename = fileInfo.fileName();
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

void MainWindow::change_vertices_color()
{
    QColor new_color = QColorDialog::getColor(Qt::white, this, tr("Vertices Color:"));
    glWidget->set_vertices_color(new_color);
}

void MainWindow::take_screenshot()
{
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString filter = "JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";
    QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", SRCDIR + filename, filter);
    if (!filepath.isEmpty()){
      QString extension = "jpg";
        extension = QFileInfo(filepath).suffix().toLower();
        extension = extension.isEmpty() ? "jpg" : extension;
        if (!(extension == "jpeg" || extension == "jpg" || extension == "bmp")) {
            QMessageBox::warning(this, "Warning!", "Invalid file extension. Expected JPG or BMP");
        }
        QPixmap pixmap (glWidget->size());
        QRect renderRect(QPoint(0, 0), glWidget->size());
        pixmap.fill(Qt::white);
        glWidget->render(&pixmap, QPoint(), renderRect);
        pixmap.save(filepath + "." + extension, extension.toUtf8().constData());
    }
}

void MainWindow::create_gif()
{
    // QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    // QString filter = "GIF files (*.gif);;All Files (*)";
    // QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", SRCDIR + filename, filter);
    // QVector<QImage> img;
    // QVector<QImage>::Iterator it;
    //     if (!filepath.isEmpty()){
    //     QGifImage gif(QSize(640, 480));
    //     gif.setDefaultDelay(100);
    //     //while(it.hasNext())
    //     for (it = img.begin(); it != img.end(); it++) {
    //         gif.addFrame(*it);
    //     }
    //     gif.save(filename);
    //     img.clear();
    // }
}

void MainWindow::set_rotation_x(double value) {
    glWidget->rotation_x(value);
}
void MainWindow::set_rotation_y(double value) {
    glWidget->rotation_y(value);
}
void MainWindow::set_rotation_z(double value) {
    glWidget->rotation_z(value);
}
void MainWindow::set_vertices_size(int value) {
    glWidget->set_vertices_size(value);
}
void MainWindow::set_vertices_method(int value) {
  glWidget->set_vertices_method(value);
}
