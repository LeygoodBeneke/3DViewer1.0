#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      background(QColor(Qt::black)),
      vertices_color(QColor(Qt::white)) {}

GLWidget::~GLWidget()
{
   //destructor code
}

void GLWidget::initializeGL()
{
    cubeCoords[0][0] = -0.3;
    cubeCoords[0][1] = -2;
    cubeCoords[0][2] = -0.3;

    cubeCoords[1][0] = -0.3;
    cubeCoords[1][1] = -2;
    cubeCoords[1][2] = 0.3;

    cubeCoords[2][0] = 0.3;
    cubeCoords[2][1] = -0.3;
    cubeCoords[2][2] = 0.3;

    cubeCoords[3][0] = 0.3;
    cubeCoords[3][1] = -0.3;
    cubeCoords[3][2] = -0.3;

    cubeCoords[4][0] = -0.3;
    cubeCoords[4][1] = 0.3;
    cubeCoords[4][2] = -0.3;

    cubeCoords[5][0] = -0.3;
    cubeCoords[5][1] = 0.3;
    cubeCoords[5][2] = 0.3;

    cubeCoords[6][0] = 0.3;
    cubeCoords[6][1] = 0.3;
    cubeCoords[6][2] = 0.3;

    cubeCoords[7][0] = 0.3;
    cubeCoords[7][1] = 0.3;
    cubeCoords[7][2] = -0.3;


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
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();s

  //   gluLookAt(0, 1, 0, 0, 0, 0, 0, 1, 0);
//    glMatrixMode(GL_MODELVIEW);
    glOrtho(-2, 2, -2, 2, -100, 100);

//    gluPerspective(1.22173, 1, 0, 100);

}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    repaint();
//    const float aspect = float(width) / float(height);
//    const float zNear = 0.01f;
//    const float zFar = 100.f;
//    //const glm::mat4 proj = glm::perspective(1.22173, aspect, zNear, zFar);
//    gluPerspective(1.22173, aspect, zNear, zFar);
//    glMatrixMode(GL_PROJECTION);
//    //glLoadMatrixf(glm::value_ptr(proj));
//    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
    glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable( GL_PROGRAM_POINT_SIZE );
    glPointSize(vertices_size);



    if (vetr_method == VerticesDisplayMethod::CIRCLE)
      glEnable(GL_POINT_SMOOTH);
    else {
      glDisable(GL_POINT_SMOOTH);
    }

    glBegin(GL_POINTS);
    for (int i = 0; i < 8; i++) {
      glColor3f(vertices_color.redF(), vertices_color.greenF(), vertices_color.blueF());
      glVertex3f(
        cubeCoords[i][0] * scale,
        cubeCoords[i][1] * scale,
        cubeCoords[i][2] * scale
      );
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.7, 0.7, 0.7);
    for (int i = 0; i < 12; i++) {
        glVertex3f(
          cubeCoords[cubeLines[i][0]][0] * scale,
          cubeCoords[cubeLines[i][0]][1] * scale,
          cubeCoords[cubeLines[i][0]][2] * scale
        );
        glVertex3f(
          cubeCoords[cubeLines[i][1]][0] * scale,
          cubeCoords[cubeLines[i][1]][1] * scale,
          cubeCoords[cubeLines[i][1]][2] * scale
        );
    }
    glEnd();

    drawAxis();

    glRotatef(prev_angle_x - angle_x, 0, 1, 0);
    glRotatef(prev_angle_y - angle_y, 1, 0, 0);
    glRotatef(prev_angle_z - angle_z, 0, 0, 1);
    prev_angle_x = angle_x;
    prev_angle_y = angle_y;
    prev_angle_z = angle_z;


    glTranslatef(
        prev_position_x - position_x,
        prev_position_y - position_y,
        prev_position_z - position_z
    );
    prev_position_x = position_x;
    prev_position_y = position_y;
    prev_position_z = position_z;

//    /glScalef(0.5, 0.5, 0.5);

}

void GLWidget::drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
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
    update();
}

void GLWidget::set_vertices_color(QColor new_color) {
    vertices_color = new_color;
    update();
}

void GLWidget::set_vertices_method(int value) {
    vetr_method = VerticesDisplayMethod(value);
    update();
}

void GLWidget::set_position_x(double x) {
    prev_position_x = position_x;
    position_x = x;
    update();
}

void GLWidget::set_position_y(double y) {
    prev_position_y = position_y;
    position_y = y;
    update();
}

void GLWidget::set_position_z(double z) {
    prev_position_z = position_z;
    position_z = z;
    update();
}
void GLWidget::set_scale(int size) {
    scale = size / 100.0;
    update();
}

