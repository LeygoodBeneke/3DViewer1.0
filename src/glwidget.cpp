#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      background(QColor(Qt::black)),
      vertices_color(QColor(Qt::white)) {}

GLWidget::~GLWidget() {
  if (point_array) free(point_array);
  if (line_array) free(line_array);
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

  if (vetr_method == VerticesDisplayMethod::CIRCLE) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(vertices_size);
  } else if (vetr_method == VerticesDisplayMethod::BLANK) {
    glPointSize(1);
    glDisable(GL_POINT_SMOOTH);
  } else {
    glPointSize(vertices_size);
    glDisable(GL_POINT_SMOOTH);
  }

  point *current_point_array = (point *)malloc(point_array_len * sizeof(point));
  for (int i = 0; i < point_array_len; i++) {
    current_point_array[i] = point_array[i];
    rotate_around_axis(&current_point_array[i].x, &current_point_array[i].y,
                       current_angle_x);
    rotate_around_axis(&current_point_array[i].y, &current_point_array[i].z,
                       current_angle_y);
    rotate_around_axis(&current_point_array[i].x, &current_point_array[i].z,
                       current_angle_z);
  }

  glBegin(GL_POINTS);
  for (int i = 0; i < point_array_len; i++) {
    glColor3f(vertices_color.redF(), vertices_color.greenF(),
              vertices_color.blueF());
    glVertex3f(

        current_point_array[i].x * scale + position_x,
        current_point_array[i].y * scale + position_y,
        current_point_array[i].z * scale + position_z);
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
  for (int i = 0; i < line_array_len; i++) {
    glVertex3f(current_point_array[line_array[i].a - 1].x * scale + position_x,
               current_point_array[line_array[i].a - 1].y * scale + position_y,
               current_point_array[line_array[i].a - 1].z * scale + position_z);
    glVertex3f(current_point_array[line_array[i].b - 1].x * scale + position_x,
               current_point_array[line_array[i].b - 1].y * scale + position_y,
               current_point_array[line_array[i].b - 1].z * scale + position_z);
  }
  glEnd();
  drawAxis();
  free(current_point_array);
}

void GLWidget::rotate_around_axis(double *first_coord, double *second_coord,
                                  const double angle) {
  GLfloat x = *first_coord, y = *second_coord;
  *first_coord = x * cos(angle) - y * sin(angle);
  *second_coord = x * sin(angle) + y * cos(angle);
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
  update();
}
void GLWidget::rotation_y(double angle) {
  current_angle_y = angle * M_PI / 180.0;
  update();
}
void GLWidget::rotation_z(double angle) {
  current_angle_z = angle * M_PI / 180.0;
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

void GLWidget::set_line_width(int value) {
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

void GLWidget::set_projection_type(int type) {
  projection_type = ProjectionType(type);
  update();
}

void GLWidget::initialize_model() {
  parser((char *)modelPath.toStdString().c_str(), &point_array,
         &point_array_len, &line_array, &line_array_len);

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
