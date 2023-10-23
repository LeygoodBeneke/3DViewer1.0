#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>


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

    void set_vertices_size(int value);
    void set_vertices_color(QColor new_color);
    void set_vertices_method(int value);

    double angle_x = 0, prev_angle_x = 0;
    double angle_y = 0, prev_angle_y = 0;
    double angle_z = 0, prev_angle_z = 0;

    enum VerticesDisplayMethod {
      SQUARE,
      CIRCLE
    };

private:
    void drawStar(float fX, float fY);
    void drawStars();
    void drawStripes();
    QColor background;
    void drawAxis();

    GLfloat triangleVertexArray[3][3];
    GLfloat triangleColorArray[3][3];
    GLubyte triangleIndexArray[1][3];

    GLfloat vertices_size = 5.0;
    QColor vertices_color;

    VerticesDisplayMethod vetr_method = VerticesDisplayMethod::SQUARE;


    // (должен заполнять парсер)
    GLfloat cubeCoords[8][3];
    GLint cubeLines[12][2];


};
#endif // GLWIDGET_H
