#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMutex>
#include <cv.h>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(IplImage** image, QMutex* cameraLock);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    IplImage** m_image;
    GLWidget *glWidget;
};

#endif
