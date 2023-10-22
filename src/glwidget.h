#ifndef GLWIDGET_H
#define GLWIDGET_H

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
    void drawStar(float fX, float fY);
    void drawStars();
    void drawStripes();
    QColor background;
};

#endif // GLWIDGET_H
