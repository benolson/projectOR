#include <QApplication>
#include <QDesktopWidget>
#include <QtConcurrentRun>
#include <cv.h>

#include "mainwindow.h"
#include "imageGrabber.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    IplImage* image;
    QFuture<void> future = QtConcurrent::run(ImageGrabberStartLoop,800,600,&image);

    Window window(&image);
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();
}
