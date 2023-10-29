#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glu.h>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
extern "C" {
#include "parser/parser.h"
};

class GLWidget : public QOpenGLWidget {
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

  void rotation(double angle, double *, double *);

  void set_vertices_color(QColor new_color);
  void set_edges_color(QColor new_color);

  void initialize_model();

  enum VerticesDisplayMethod { SQUARE, CIRCLE };

  enum EdgesType { SOLID, DASHED };

  enum ProjectionType { PARALLEL, CENTRAL };

  int get_edges_count() { return line_array_len; }
  int get_points_count() { return point_array_len; }

 private:
  void drawStar(float fX, float fY);
  void drawStars();
  void drawStripes();
  QColor background;
  void drawAxis();

  GLfloat vertices_size = 5.0;
  double prev_angle_x = 0;
  double prev_angle_y = 0;
  double prev_angle_z = 0;

  double current_angle_x = 0.0;
  double current_angle_y = 0.0;
  double current_angle_z = 0.0;

  double scale = 1.0;

  double position_x = 0;
  double position_y = 0;
  double position_z = 0;
  QColor vertices_color = Qt::white;
  QColor edges_color = Qt::white;

  point *point_array;
  int point_array_len = 0;
  line *line_array;
  int line_array_len = 0;

  VerticesDisplayMethod vetr_method = VerticesDisplayMethod::SQUARE;
  EdgesType edges_type = EdgesType::SOLID;
  ProjectionType projection_type = ProjectionType::PARALLEL;

 public slots:
  void set_position_x(double);
  void set_position_y(double);
  void set_position_z(double);
  void rotation_x(double angle);
  void rotation_y(double angle);
  void rotation_z(double angle);
  void set_vertices_size(int);
  void set_vertices_method(int);
  void set_edges_type(int);
  void set_scale(int size);
  void set_projection_type(int);
};
#endif  // GLWIDGET_H
