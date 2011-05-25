#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <cv.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(IplImage** _image, QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void timerEvent(QTimerEvent *event);
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);    

private:
    IplImage** image;
    GLuint texture;
    QColor qtGreen;
    QColor qtPurple;
};

#endif
