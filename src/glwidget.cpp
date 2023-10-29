#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      // background(QColor(Qt::black)),
      vertices_color(QColor(Qt::white)) {}

GLWidget::~GLWidget() {
  free(point_array);
  free(line_array);
}

void GLWidget::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, height, width);
}

void GLWidget::paintGL() {
  glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  if (projection_type == ProjectionType::CENTRAL) {
    gluPerspective(70.0, 1.5, 0.1, 50);
  } else
    glOrtho(-5, 5, -5, 5, -100, 100);
  gluLookAt(2, 2, 4, 0, 0, 0, 0, 1, 0);

  glEnable(GL_PROGRAM_POINT_SIZE);
  glPointSize(vertices_size);

  if (vetr_method == VerticesDisplayMethod::CIRCLE)
    glEnable(GL_POINT_SMOOTH);
  else {
    glDisable(GL_POINT_SMOOTH);
  }

  glBegin(GL_POINTS);
  for (int i = 0; i < point_array_len; i++) {
    glColor3f(vertices_color.redF(), vertices_color.greenF(),
              vertices_color.blueF());
    glVertex3f(

        point_array[i].x * scale + position_x,
        point_array[i].y * scale + position_y,
        point_array[i].z * scale + position_z);
  }
  glEnd();

  if (edges_type == EdgesType::DASHED) {
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineStipple(3, 0xDDDD);
  glBegin(GL_LINES);
  glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
  for (int i = 0; i < line_array_len; i++) {
    glVertex3f(point_array[line_array[i].a - 1].x * scale + position_x,
               point_array[line_array[i].a - 1].y * scale + position_y,
               point_array[line_array[i].a - 1].z * scale + position_z);
    glVertex3f(point_array[line_array[i].b - 1].x * scale + position_x,
               point_array[line_array[i].b - 1].y * scale + position_y,
               point_array[line_array[i].b - 1].z * scale + position_z);
  }
  glEnd();
  drawAxis();
}

void GLWidget::drawAxis() {
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
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].x, y = point_array[i].y;
    point_array[i].x = x * cos(-prev_angle_x) - y * sin(-prev_angle_x);
    point_array[i].y = x * sin(-prev_angle_x) + y * cos(-prev_angle_x);
  }
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].x, y = point_array[i].y;
    point_array[i].x = x * cos(current_angle_x) - y * sin(current_angle_x);
    point_array[i].y = x * sin(current_angle_x) + y * cos(current_angle_x);
  }
  prev_angle_x = current_angle_x;
  update();
}
void GLWidget::rotation_y(double angle) {
  current_angle_y = angle * M_PI / 180.0;
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].y, y = point_array[i].z;
    point_array[i].y = x * cos(-prev_angle_y) - y * sin(-prev_angle_y);
    point_array[i].z = x * sin(-prev_angle_y) + y * cos(-prev_angle_y);
  }
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].y, y = point_array[i].z;
    point_array[i].y = x * cos(current_angle_y) - y * sin(current_angle_y);
    point_array[i].z = x * sin(current_angle_y) + y * cos(current_angle_y);
  }
  prev_angle_y = current_angle_y;
  update();
}
void GLWidget::rotation_z(double angle) {
  current_angle_z = angle * M_PI / 180.0;
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].x, y = point_array[i].z;
    point_array[i].x = x * cos(-prev_angle_z) - y * sin(-prev_angle_z);
    point_array[i].z = x * sin(-prev_angle_z) + y * cos(-prev_angle_z);
  }
  for (int i = 0; i < point_array_len; i++) {
    GLfloat x = point_array[i].x, y = point_array[i].z;
    point_array[i].x = x * cos(current_angle_z) - y * sin(current_angle_z);
    point_array[i].z = x * sin(current_angle_z) + y * cos(current_angle_z);
  }
  prev_angle_z = current_angle_z;
  update();
}

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

void GLWidget::set_projection_type(int type) {
  projection_type = ProjectionType(type);
  update();
}

void GLWidget::initialize_model() {
  parser((char*)modelPath.toStdString().c_str(), &point_array, &point_array_len,
         &line_array, &line_array_len);

  point gravity_center = {.x = 0, .y = 0, .z = 0};

  for (int i = 0; i < point_array_len; i++) {
    gravity_center.x += point_array[i].x;
    gravity_center.y += point_array[i].y;
    gravity_center.z += point_array[i].z;
  }
  gravity_center.x /= point_array_len;
  gravity_center.y /= point_array_len;
  gravity_center.z /= point_array_len;

  for (int i = 0; i < point_array_len; i++) {
    point_array[i].x -= gravity_center.x;
    point_array[i].y -= gravity_center.y;
    point_array[i].z -= gravity_center.z;
  }
  update();
}
