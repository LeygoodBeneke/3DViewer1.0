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


    void rotation_x(double angle);
    void rotation_y(double angle);
    void rotation_z(double angle);
    void rotation(double angle, double*, double*);

    double angle_x = 0, prev_angle_x = 0;
    double angle_y = 0, prev_angle_y = 0;
    double angle_z = 0, prev_angle_z = 0;

private:
    void drawStar(float fX, float fY);
    void drawStars();
    void drawStripes();
    QColor background;

    GLfloat triangleVertexArray[3][3];
    GLfloat triangleColorArray[3][3];
    GLubyte triangleIndexArray[1][3];
};

#endif // GLWIDGET_H
