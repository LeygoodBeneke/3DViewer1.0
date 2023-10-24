#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = ui->openGLWidget;
    settings = new QSettings(this);
    load_settings();

    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(on_bg_btn_clicked()));
    connect(ui->load_from_file_btn,SIGNAL(clicked()),this,SLOT(on_load_file_btn_clicked()));
    connect(ui->screenshot_btn,SIGNAL(clicked()),this,SLOT(on_snap_btn_clicked()));
    connect(ui->record_btn,SIGNAL(clicked()),this,SLOT(on_gif_btn_clicked()));
}

MainWindow::~MainWindow()
{
  save_settings();
  delete ui;
}

void MainWindow::on_load_file_btn_clicked()
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

void MainWindow::on_bg_btn_clicked()
{
    QColor bg = glWidget->get_background();
    QColor new_bg = QColorDialog::getColor(bg, this, tr("Background Color:"));
    if (new_bg.isValid()) {
      glWidget->set_background(new_bg);
      glWidget->update();
    }
}

void MainWindow::on_snap_btn_clicked()
{
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QString filter = "JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";
    QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", SRCDIR + filename, filter);
    if (!filepath.isEmpty()){
      QString extension = "jpg";
        extension = QFileInfo(filepath).suffix().toLower();
        extension = extension.isEmpty() ? "jpg" : extension;
        if (!(extension == "jpeg" || extension == "jpg" || extension == "bmp")) {
            QMessageBox::warning(this, "Warning!", "Invalid file extension. Expected JPG or BMP");
        }
        QImage image = glWidget->grab().toImage();
        image.save(filepath, extension.toUtf8().constData());
    }
}


void MainWindow::on_gif_btn_clicked()
{
    if (!glWidget->modelPath.isEmpty()) {
        timer = new QTimer(this);
        gif = new QGifImage(QSize(640, 480));
        counter = 0;
        connect(timer, SIGNAL(timeout()), this, SLOT(create_gif()));
        timer->start(100);
        ui->record_btn->setText("Recording in progress");
    } else {
        QMessageBox::warning(this, "Warning!", "File not uploaded");
    }
}

void MainWindow::create_gif()
{
    QImage image = glWidget->grabFramebuffer().scaled(640, 480);
    gif->addFrame(image);
    counter++;
    if (counter == 50) {
        timer->stop();
        QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
        gif->save(SRCDIR + filename);
        QMessageBox::information(this, "Success!", "Gif saved successfully");
        delete gif;
        ui->record_btn->setText("Start recording");
    }
}

void MainWindow::save_settings()
{
    settings->setValue("background", glWidget->get_background());
    //...
}

void MainWindow::load_settings()
{
    QColor bg = settings->value("background").value<QColor>();
    if (bg.isValid()) glWidget->set_background(bg);
    else glWidget->set_background(Qt::black);
    //...
}




















