#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  glWidget = ui->widget;
  settings = new QSettings(this);
  load_settings();

  connect(ui->background_color_btn, SIGNAL(clicked()), this,
          SLOT(on_bg_btn_clicked()));
  connect(ui->load_from_file_btn, SIGNAL(clicked()), this,
          SLOT(on_load_file_btn_clicked()));
  connect(ui->screenshot_btn, SIGNAL(clicked()), this,
          SLOT(on_snap_btn_clicked()));
  connect(ui->record_btn, SIGNAL(clicked()), this, SLOT(on_gif_btn_clicked()));
  connect(ui->vertices_color_btn, SIGNAL(clicked()), this,
          SLOT(change_vertices_color()));
  connect(ui->edges_color_btn, SIGNAL(clicked()), this,
          SLOT(change_edges_color()));

  connect(ui->rotation_x_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(rotation_x(double)));
  connect(ui->rotation_y_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(rotation_y(double)));
  connect(ui->rotation_z_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(rotation_z(double)));
  connect(ui->position_x_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(set_position_x(double)));
  connect(ui->position_y_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(set_position_y(double)));
  connect(ui->position_z_spinbox, SIGNAL(valueChanged(double)), ui->widget,
          SLOT(set_position_z(double)));

  connect(ui->model_scale_slider, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(set_scale(int)));

  connect(ui->vertices_display_method_combobox,
          SIGNAL(currentIndexChanged(int)), ui->widget,
          SLOT(set_vertices_method(int)));
  connect(ui->edges_type_combobox, SIGNAL(currentIndexChanged(int)), ui->widget,
          SLOT(set_edges_type(int)));
  connect(ui->projection_type_combobox, SIGNAL(currentIndexChanged(int)),
          ui->widget, SLOT(set_projection_type(int)));
  connect(ui->vertices_size_slider, SIGNAL(valueChanged(int)), ui->widget,
          SLOT(set_vertices_size(int)));
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
}

void MainWindow::on_load_file_btn_clicked() {
  QString path =
      QFileDialog::getOpenFileName(this, "Load a file", QDir::currentPath());
  QFileInfo fileInfo(path);
  if (!path.isEmpty()) {
    if (fileInfo.suffix() != "obj") {
      QMessageBox::warning(this, "Warning!",
                           "Invalid file extension. Expected '.obj'");
    } else {
      glWidget->modelPath = path;
      QString filename = fileInfo.fileName();
      ui->Filename_Label->setText(filename);
      glWidget->initialize_model();

      ui->edges_count_label->setText(
          QString::number(glWidget->get_edges_count()));
      ui->vertices_count_label->setText(
          QString::number(glWidget->get_points_count()));
    }
  }
}

void MainWindow::on_bg_btn_clicked() {
  QColor bg = glWidget->get_background();
  QColor new_bg = QColorDialog::getColor(bg, this, tr("Background Color:"));
  if (new_bg.isValid()) {
    glWidget->set_background(new_bg);
    glWidget->update();
  }
}

void MainWindow::change_vertices_color() {
  QColor new_color =
      QColorDialog::getColor(Qt::white, this, tr("Vertices Color:"));
  glWidget->set_vertices_color(new_color);
}

void MainWindow::change_edges_color() {
  QColor new_color =
      QColorDialog::getColor(Qt::white, this, tr("Vertices Color:"));
  glWidget->set_edges_color(new_color);
}

void MainWindow::on_snap_btn_clicked() {
  QString filename =
      QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
  QString filter = "JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";
  QString filepath = QFileDialog::getSaveFileName(
      this, "Enter the name of screenshot", SRCDIR + filename, filter);
  if (!filepath.isEmpty()) {
    QString extension = "jpg";
    extension = QFileInfo(filepath).suffix().toLower();
    extension = extension.isEmpty() ? "jpg" : extension;
    if (!(extension == "jpeg" || extension == "jpg" || extension == "bmp")) {
      QMessageBox::warning(this, "Warning!",
                           "Invalid file extension. Expected JPG or BMP");
    }
    QImage image = glWidget->grab().toImage();
    image.save(filepath, extension.toUtf8().constData());
  }
}

void MainWindow::on_gif_btn_clicked() {
  if (!glWidget->modelPath.isEmpty()) {
    timer = new QTimer(this);
    gif = new QGifImage();
    counter = 0;
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(create_gif()));
    ui->record_btn->setText("Recording in progress");
  } else {
    QMessageBox::warning(this, "Warning!", "File not uploaded");
  }
}

void MainWindow::create_gif() {
  gif->setDefaultDelay(100);
  QImage image = glWidget->grabFramebuffer();
  QImage resized_image =
      image.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  gif->addFrame(resized_image);
  counter++;
  if (counter == 50) {
    timer->stop();
    QString filename =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    gif->save(SRCDIR + filename);
    QMessageBox::information(this, "Success!", "Gif saved successfully");
    delete gif;
    ui->record_btn->setText("Start recording");
  }
}

void MainWindow::save_settings() {
  settings->setValue("background", glWidget->get_background());
  //...
}

void MainWindow::load_settings() {
  QColor bg = settings->value("background").value<QColor>();
  if (bg.isValid())
    glWidget->set_background(bg);
  else
    glWidget->set_background(Qt::black);
  //...
}
