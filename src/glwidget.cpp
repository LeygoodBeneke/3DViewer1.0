#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    background = QColor(Qt::white);
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




    // Инициализируем OpenGL

    // Устанавливаем размер окна
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void GLWidget::paintGL()
{
    glEnable( GL_PROGRAM_POINT_SIZE );
    glPointSize(6.0);

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 8; i++) {
      glVertex3f(cubeCoords[i][0],cubeCoords[i][1],cubeCoords[i][2]);
    }
    glEnd();



    for (int i = 0; i < 4; i++) {
      glBegin(GL_LINES);
        glColor3f(0.7, 0.7, 0.7);
        glVertex3f(cubeCoords[i][0], cubeCoords[i][1], cubeCoords[i][2]);
        glVertex3f(cubeCoords[(i + 1) % 4][0], cubeCoords[(i + 1) % 4][1], cubeCoords[(i + 1) % 4][2]);
      glEnd();
    }

    for (int i = 4; i < 8; i++) {
      glBegin(GL_LINES);
      glColor3f(0.7, 0.7, 0.7);
      glVertex3f(cubeCoords[i][0], cubeCoords[i][1], cubeCoords[i][2]);
      glVertex3f(cubeCoords[(i - 4) % 4][0], cubeCoords[(i + 1) % 4][1], cubeCoords[(i - 4) % 4][2]);
      glEnd();
    }

    for (int i = 4; i < 8; i++) {
      glBegin(GL_LINES);
      glColor3f(0.7, 0.7, 0.7);
      glVertex3f(cubeCoords[i][0], cubeCoords[i][1], cubeCoords[i][2]);
      glVertex3f(cubeCoords[(i + 1) % 4 + 4][0], cubeCoords[(i + 1) % 4 + 4][1], cubeCoords[(i + 1) % 4 + 4][2]);
      glEnd();
    }

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
    glRotatef(prev_angle_x - angle_x, 0, 1, 0);
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
