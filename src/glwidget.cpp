#include "glwidget.h"

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
    //some code
}

void GLWidget::paintGL()
{
    glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::resizeGL(int w, int h)
{
    //some code
}
