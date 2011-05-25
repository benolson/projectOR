#include <QtGui>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(IplImage** _image, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    image = _image;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    startTimer(60);
}

GLWidget::~GLWidget()
{
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*image)->width, (*image)->height,
                      0, GL_RGB, GL_UNSIGNED_BYTE, (*image)->imageData);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glBegin (GL_QUADS);
    glTexCoord2f(0.f,0.f); glVertex3i (-1, -1, -1);
    glTexCoord2f(1.f,0.f); glVertex3i (1, -1, -1);
    glTexCoord2f(1.f,1.f); glVertex3i (1, 1, -1);
    glTexCoord2f(0.f,1.f); glVertex3i (-1, 1, -1);
    glEnd ();

    glMatrixMode (GL_MODELVIEW);
}

void GLWidget::resizeGL(int width, int height)
{    
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}
