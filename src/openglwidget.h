#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

class GLWidget: public QOpenGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    QString modelPath;

    QColor get_background() { return background; }
    void set_background(QColor color) { background = color; }

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QColor background;

};

#endif // OPENGLWIDGET_H
