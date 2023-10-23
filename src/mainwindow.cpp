#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glWidget = ui->openGLWidget;

    connect(ui->background_color_btn,SIGNAL(clicked()),this,SLOT(on_bg_btn_clicked()));
    connect(ui->load_from_file_btn,SIGNAL(clicked()),this,SLOT(on_load_file_btn_clicked()));
    connect(ui->screenshot_btn,SIGNAL(clicked()),this,SLOT(on_snap_btn_clicked()));
    connect(ui->record_btn,SIGNAL(clicked()),this,SLOT(on_gif_btn_clicked()));
}

MainWindow::~MainWindow()
{
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
        QPixmap pixmap (glWidget->size());
        QRect renderRect(QPoint(0, 0), glWidget->size());
        pixmap.fill(Qt::white);
        glWidget->render(&pixmap, QPoint(), renderRect);
        pixmap.save(filepath, extension.toUtf8().constData());
    }
}

//void MainWindow::on_gif_btn_clicked()
//{
//    QTimer timer;
//    timer.setInterval(100);
//    int count = 0;
//    timer.start();
//    if (count == 50) {
//    QGifImage gif(QSize(640, 480));
//    QVector<QImage> img;
//    img.resize(glWidget->width() * glWidget->height());
//    gif.setDefaultDelay(10);
//    for (QVector<QImage>::Iterator it = img.begin(); it != img.end(); ++it) {
//        gif.addFrame(*it);
//    }
//    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
//    QString filter = "GIF files (*.gif);;All Files (*)";
//    QString filepath = QFileDialog::getSaveFileName(this, "Enter the name of screenshot", SRCDIR + filename, filter);
//    gif.save(filepath);
//    img.clear();
//    }
//}

void MainWindow::on_gif_btn_clicked()
{
    if (!glWidget->modelPath.isEmpty()) {
    timer = new QTimer(this);
    counter = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(create_gif()));
    timer->start(100);
    } else {
        QMessageBox::warning(this, "Warning!", "File not uploaded");
    }
}

void MainWindow::create_gif()
{
    qDebug() << "IN";
    gif = new QGifImage(QSize(640, 480));
    QImage image = glWidget->grabFramebuffer().scaled(640, 480);
    gif->addFrame(image);
    if (counter == 50) {
        timer->stop();
        QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
        gif->save(SRCDIR + filename);
        QMessageBox::information(this, "Success!", "Gif saves successfully");
        delete gif;
    }
    counter++;
}



















