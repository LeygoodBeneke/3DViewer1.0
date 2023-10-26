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

    for (int i = 0; i < 8; i++) {
      currentCubeCoords[i][0] = cubeCoords[i][0];
      currentCubeCoords[i][1] = cubeCoords[i][1];
      currentCubeCoords[i][2] = cubeCoords[i][2];
    }

    // Инициализируем OpenGL

    // Устанавливаем размер окна
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(line_width);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, -100, 100);
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, height, width);
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
        currentCubeCoords[i][0] * scale + position_x,
        currentCubeCoords[i][1] * scale + position_y,
        currentCubeCoords[i][2] * scale + position_z
      );
    }
    glEnd();

    if (edges_type == EdgesType::DASHED) {
      glEnable(GL_LINE_STIPPLE);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineStipple(3, 0xDDDD);

    glLineWidth(line_width);
    glBegin(GL_LINES);

    glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
    for (int i = 0; i < 12; i++) {
      glVertex3f(
        currentCubeCoords[cubeLines[i][0]][0] * scale + position_x,
        currentCubeCoords[cubeLines[i][0]][1] * scale + position_y,
        currentCubeCoords[cubeLines[i][0]][2] * scale + position_z
      );
      glVertex3f(
        currentCubeCoords[cubeLines[i][1]][0] * scale + position_x,
        currentCubeCoords[cubeLines[i][1]][1] * scale + position_y,
        currentCubeCoords[cubeLines[i][1]][2] * scale + position_z
      );
    }
    glEnd();

}

void GLWidget::drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(.5, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, .5, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, .5);
    glEnd();
}

void GLWidget::rotation_x(double angle) {
    current_angle_x = angle * M_PI / 180.0;
    GLfloat abs_angle = current_angle_x - prev_angle_x;
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][0], y = currentCubeCoords[i][1];
        currentCubeCoords[i][0] = x * cos(-prev_angle_x) - y * sin(-prev_angle_x);
        currentCubeCoords[i][1] = x * sin(-prev_angle_x) + y * cos(-prev_angle_x);
    }
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][0], y = currentCubeCoords[i][1];
        currentCubeCoords[i][0] = x * cos(current_angle_x) - y * sin(current_angle_x);
        currentCubeCoords[i][1] = x * sin(current_angle_x) + y * cos(current_angle_x);
    }
    prev_angle_x = current_angle_x;
    update();
}
void GLWidget::rotation_y(double angle) {
    current_angle_y = angle * M_PI / 180.0;
    GLfloat abs_angle = current_angle_y - prev_angle_y;
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][1], y = currentCubeCoords[i][2];
        currentCubeCoords[i][1] = x * cos(-prev_angle_y) - y * sin(-prev_angle_y);
        currentCubeCoords[i][2] = x * sin(-prev_angle_y) + y * cos(-prev_angle_y);
    }
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][1], y = currentCubeCoords[i][2];
        currentCubeCoords[i][1] = x * cos(current_angle_y) - y * sin(current_angle_y);
        currentCubeCoords[i][2] = x * sin(current_angle_y) + y * cos(current_angle_y);
    }
    prev_angle_y = current_angle_y;
    update();
}
void GLWidget::rotation_z(double angle) {
    current_angle_z = angle * M_PI / 180.0;
    GLfloat abs_angle = current_angle_z - prev_angle_z;
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][0], y = currentCubeCoords[i][2];
        currentCubeCoords[i][0] = x * cos(-prev_angle_z) - y * sin(-prev_angle_z);
        currentCubeCoords[i][2] = x * sin(-prev_angle_z) + y * cos(-prev_angle_z);
    }
    for (int i = 0; i < 8; i++) {
        GLfloat x = currentCubeCoords[i][0], y = currentCubeCoords[i][2];
        currentCubeCoords[i][0] = x * cos(current_angle_z) - y * sin(current_angle_z);
        currentCubeCoords[i][2] = x * sin(current_angle_z) + y * cos(current_angle_z);
    }
    prev_angle_z = current_angle_z;
    update();
}
// currentCubeCoords - МОЖНО УДАЛИТЬ

void GLWidget::set_vertices_size(int value) {
    vertices_size = value;
    update();
}

void GLWidget::set_vertices_color(QColor new_color) {
    vertices_color = new_color;
    update();
}

void GLWidget::set_edges_color(QColor new_color) {
    edges_color = new_color;
    update();
}

void GLWidget::set_vertices_method(int value) {
    vetr_method = VerticesDisplayMethod(value);
    update();
}

void GLWidget::set_edges_type(int value) {
    edges_type = EdgesType(value);
    update();
}

void GLWidget::set_line_width(int value)
{
    line_width = value;
    update();
}

void GLWidget::set_position_x(double x) {
    position_x = x;
    update();
}

void GLWidget::set_position_y(double y) {
    position_y = y;
    update();
}

void GLWidget::set_position_z(double z) {
    position_z = z;
    update();
}
void GLWidget::set_scale(int size) {
    scale = size / 100.0;
    update();
}

