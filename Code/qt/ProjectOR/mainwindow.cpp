
#include <QtGui>

#include "glwidget.h"
#include "mainwindow.h"

Window::Window(IplImage** image, QMutex* cameraLock)
{
    setWindowFlags(Qt::FramelessWindowHint);
    m_image = image;
    glWidget = new GLWidget(image, cameraLock);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    setLayout(mainLayout);    
    setWindowTitle(tr("ProjectOR"));
    QRect screenres = QApplication::desktop()->screenGeometry(1);
    move(QPoint(screenres.x(), screenres.y()));
    resize(screenres.width(), screenres.height());
    showFullScreen();
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
