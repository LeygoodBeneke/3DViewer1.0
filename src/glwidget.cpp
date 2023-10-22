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
    triangleVertexArray[0][0] = 0.0;
    triangleVertexArray[0][1] = 0.0;
    triangleVertexArray[0][2] = 0.0;
    triangleVertexArray[1][0] = 1.0;
    triangleVertexArray[1][1] = 1.0;
    triangleVertexArray[1][2] = 0.0;
    triangleVertexArray[2][0] = 1.0;
    triangleVertexArray[2][1] = 0.0;
    triangleVertexArray[2][2] = 0.0;
    triangleColorArray[0][0] = 0.25;
    triangleColorArray[0][1] = 0.87;
    triangleColorArray[0][2] = 0.81;
    triangleColorArray[1][0] = 0.25;
    triangleColorArray[1][1] = 0.87;
    triangleColorArray[1][2] = 0.81;
    triangleColorArray[2][0] = 0.25;
    triangleColorArray[2][1] = 0.87;
    triangleColorArray[2][2] = 0.81;
    triangleIndexArray[0][0] = 0;
    triangleIndexArray[0][1] = 1;
    triangleIndexArray[0][2] = 2;

    glVertexPointer(3, GL_FLOAT, 0, triangleVertexArray);
    glColorPointer(3, GL_FLOAT, 0, triangleColorArray);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndexArray);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);


    // Инициализируем OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

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

//     Белая сторона — ЗАДНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // Фиолетовая сторона — ПРАВАЯ
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // Зеленая сторона — ЛЕВАЯ
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // Синяя сторона — ВЕРХНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // Красная сторона — НИЖНЯЯ
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    glRotatef(prev_angle_x - angle_x, 0, 1, 0);
    glRotatef(prev_angle_y - angle_y, 1, 0, 0);
    glRotatef(prev_angle_z - angle_z, 0, 0, 1);`
}

void GLWidget::drawStar(float fX, float fY)
{
    const float kfPi = 3.1415926535897932384626433832795;
    // draw ten triangles
    const float kfRadius = 0.0616/2.0;
    const float kfInnerRadius = kfRadius*(1.0/(sin((2.0*kfPi)/5.0)*2.0*cos(kfPi/10.0) + sin((3.0*kfPi)/10.0)));
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(fX, fY, 0.0);
    for (int iVertIndex = 0; iVertIndex < 10; ++iVertIndex)
    {
      float fAngleStart    = kfPi/2.0 + (iVertIndex*2.0*kfPi)/10.0;
      float fAngleEnd        = fAngleStart + kfPi/5.0;
      if (iVertIndex % 2 == 0)
      {
        glVertex3f(fX + kfRadius*cos(fAngleStart)/1.9, fY + kfRadius*sin(fAngleStart), 0.0);
        glVertex3f(fX + kfInnerRadius*cos(fAngleEnd)/1.9, fY + kfInnerRadius*sin(fAngleEnd), 0.0);
      } else
      {
        glVertex3f(fX + kfInnerRadius*cos(fAngleStart)/1.9, fY + kfInnerRadius*sin(fAngleStart), 0.0);
        glVertex3f(fX + kfRadius*cos(fAngleEnd)/1.9, fY + kfRadius*sin(fAngleEnd), 0.0);
      }
    }
    glEnd();
}

void GLWidget::drawStars()
{
    for (int iStarRow = 0; iStarRow < 9; ++iStarRow)
    {
      float fY = 6.0/13.0 + (iStarRow + 1)*((7.0/13.0)/10);
      // alternate between rows of five or six stars
      if (iStarRow % 2 == 0)
      {
        for (int iStarCol = 0; iStarCol < 6; ++iStarCol)
        {
          drawStar(iStarCol*((0.76/1.9)/6.0) + (0.76/1.9)/12.0, fY);
        }
      } else
      {
        for (int iStarCol = 0; iStarCol < 5; ++iStarCol)
        {
          drawStar((iStarCol + 1)*((0.76/1.9)/6.0), fY);
        }
      }
    }
}

void GLWidget::drawStripes()
{
    for (int iStripeIndex = 0; iStripeIndex < 13; ++iStripeIndex)
    {
      // Alternate stripe colors
      if (iStripeIndex % 2 == 0)
      {
        glColor3f(204.0/255.0, 0.0, 0.0);
      } else
      {
        glColor3f(1.0, 1.0, 1.0);
      }

      float fStartX    = 0.0;
      float fEndX    = 1.0;
      float fStartY    = iStripeIndex*(1.0/13.0);
      float fEndY    = (iStripeIndex + 1)*(1.0/13.0);

              // the last seven stripes are shorter
      if (iStripeIndex > 5)
      {
        fStartX = 0.76/1.9;
      }

      glBegin(GL_QUADS);
      glVertex3f(fStartX, fStartY, 0.0);
      glVertex3f(fEndX, fStartY, 0.0);
      glVertex3f(fEndX, fEndY, 0.0);
      glVertex3f(fStartX, fEndY, 0.0);
      glEnd();
    }
}
void GLWidget::rotation(double angle, double *prev_value, double *new_value) {
    *prev_value = *new_value;
    *new_value = angle;
    repaint();
}

void GLWidget::rotation_x(double angle) {
    rotation(angle, &prev_angle_x, &angle_x);
}
void GLWidget::rotation_y(double angle) {
    rotation(angle, &prev_angle_y, &angle_y);
}
void GLWidget::rotation_z(double angle) {
    rotation(angle, &prev_angle_z, &angle_z);
}
