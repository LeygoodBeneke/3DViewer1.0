#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glu.h>


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

  void rotation(double angle, double*, double*);

  void set_vertices_color(QColor new_color);

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

  GLfloat vertices_size = 5.0;
  double angle_x = 0, prev_angle_x = 0;
  double angle_y = 0, prev_angle_y = 0;
  double angle_z = 0, prev_angle_z = 0;

  double scale = 1.0;


  double position_x = 0, prev_position_x = 0;
  double position_y = 0, prev_position_y = 0;
  double position_z = 0, prev_position_z = 0;
  QColor vertices_color;

  VerticesDisplayMethod vetr_method = VerticesDisplayMethod::SQUARE;


  const static GLint coords_size = 8;
  // (должен заполнять парсер)
  GLfloat cubeCoords[coords_size][3];
  GLint cubeLines[12][2];

public slots:
  void set_position_x(double);
  void set_position_y(double);
  void set_position_z(double);
  void rotation_x(double angle);
  void rotation_y(double angle);
  void rotation_z(double angle);
  void set_vertices_size(int);
  void set_vertices_method(int);

  void set_scale(int size);


};
#endif // GLWIDGET_H
