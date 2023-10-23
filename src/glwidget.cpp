#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    background = QColor(Qt::black);
}

GLWidget::~GLWidget()
{
   //destructor code
}

void GLWidget::initializeGL()
{
    cubeCoords[0][0] = -0.5;
    cubeCoords[0][1] = -0.5;
    cubeCoords[0][2] = -0.5;

    cubeCoords[1][0] = -0.5;
    cubeCoords[1][1] = -0.5;
    cubeCoords[1][2] = 0.5;

    cubeCoords[2][0] = 0.5;
    cubeCoords[2][1] = -0.5;
    cubeCoords[2][2] = 0.5;

    cubeCoords[3][0] = 0.5;
    cubeCoords[3][1] = -0.5;
    cubeCoords[3][2] = -0.5;

    cubeCoords[4][0] = -0.5;
    cubeCoords[4][1] = 0.5;
    cubeCoords[4][2] = -0.5;

    cubeCoords[5][0] = -0.5;
    cubeCoords[5][1] = 0.5;
    cubeCoords[5][2] = 0.5;

    cubeCoords[6][0] = 0.5;
    cubeCoords[6][1] = 0.5;
    cubeCoords[6][2] = 0.5;

    cubeCoords[7][0] = 0.5;
    cubeCoords[7][1] = 0.5;
    cubeCoords[7][2] = -0.5;


    cubeLines[0][0] = 0;
    cubeLines[0][1] = 1;

    cubeLines[1][0] = 1;
    cubeLines[1][1] = 2;

    cubeLines[2][0] = 2;
    cubeLines[2][1] = 3;

    cubeLines[3][0] = 3;
    cubeLines[3][1] = 0;

    cubeLines[4][0] = 4;
    cubeLines[4][1] = 5;

    cubeLines[5][0] = 5;
    cubeLines[5][1] = 6;

    cubeLines[6][0] = 6;
    cubeLines[6][1] = 7;

    cubeLines[7][0] = 7;
    cubeLines[7][1] = 4;

    cubeLines[8][0] = 0;
    cubeLines[8][1] = 4;

    cubeLines[9][0] = 1;
    cubeLines[9][1] = 5;

    cubeLines[10][0] = 2;
    cubeLines[10][1] = 6;

    cubeLines[11][0] = 3;
    cubeLines[11][1] = 7;

    // Инициализируем OpenGL

    // Устанавливаем размер окна
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GLWidget::resizeGL(int width, int height)
{
    const float aspectRatio = ((float)width) / height;
    float xSpan = 1; // Feel free to change this to any xSpan you need.
    float ySpan = 1; // Feel free to change this to any ySpan you need.

    if (aspectRatio > 1){
      // Width > Height, so scale xSpan accordinly.
      xSpan *= aspectRatio;
    }
    else{
      // Height >= Width, so scale ySpan accordingly.
      ySpan = xSpan / aspectRatio;
    }

    glOrtho(1, 1, 1, 1, -1, 1);
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void GLWidget::paintGL()
{
    glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable( GL_PROGRAM_POINT_SIZE );
    glPointSize(vertices_size);

    glBegin(GL_POINTS);
    glColor3f(0, 1.0, 1.0);
    for (int i = 0; i < 8; i++) {
      glVertex3f(cubeCoords[i][0],cubeCoords[i][1],cubeCoords[i][2]);
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.7, 0.7, 0.7);
    for (int i = 0; i < 12; i++) {
        glVertex3f(
          cubeCoords[cubeLines[i][0]][0],
          cubeCoords[cubeLines[i][0]][1],
          cubeCoords[cubeLines[i][0]][2]
        );
        glVertex3f(
          cubeCoords[cubeLines[i][1]][0],
          cubeCoords[cubeLines[i][1]][1],
          cubeCoords[cubeLines[i][1]][2]
        );
    }
    glEnd();

    drawAxis();

    glRotatef(prev_angle_x - angle_x, 0, 1, 0);
    glRotatef(prev_angle_y - angle_y, 1, 0, 0);
    glRotatef(prev_angle_z - angle_z, 0, 0, 1);

}

void GLWidget::drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -1);
    glEnd();
}

void GLWidget::rotation(double angle, double *prev_value, double *new_value) {
    *prev_value = *new_value;
    *new_value = angle;
    repaint();
}

void GLWidget::rotation_x(double angle) {
    prev_angle_y = angle_y;
    prev_angle_z = angle_z;
    rotation(angle, &prev_angle_x, &angle_x);
}
void GLWidget::rotation_y(double angle) {
    prev_angle_x = angle_x;
    prev_angle_z = angle_z;
    rotation(angle, &prev_angle_y, &angle_y);
}
void GLWidget::rotation_z(double angle) {
    prev_angle_y = angle_y;
    prev_angle_x = angle_x;
    rotation(angle, &prev_angle_z, &angle_z);
}

void GLWidget::set_vertices_size(int value) {
    vertices_size = value;
    std:: cout << "YES";
    update();
    repaint();
}
