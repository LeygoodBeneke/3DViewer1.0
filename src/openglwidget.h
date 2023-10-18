#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QLabel>

class GLWidget: public QOpenGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    QColor get_background() { return background; }
    void set_background(QColor color) { background = color; }

    QImage take_screenshot();
    QLabel filename;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QColor background;
};

#endif // OPENGLWIDGET_H
