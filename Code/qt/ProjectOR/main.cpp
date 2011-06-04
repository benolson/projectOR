#include <QApplication>
#include <QDesktopWidget>
#include <QtConcurrentRun>
#include <QMutexLocker>
#include <QMutex>
#include <cv.h>
#include <iostream>
#include <fstream>

#include "imageGrabber.h"
#include "glwidget.h"

int main(int argc, char *argv[])
{
    // set up trigger to control lifetime of thread
    std::ofstream f("shutDownThread.bin", std::ios::binary);
    f << 0;
    f.close();
    // launch camera thread
    QMutex* cameraLock = new QMutex();
    QApplication app(argc, argv);
    IplImage* image;
    QFuture<void> future = QtConcurrent::run(ImageGrabberStartLoop,800,600,&image,cameraLock);
    // run application
    GLWidget window(&image, cameraLock);
    window.showMaximized();    
    app.exec();
    // deliver signal to shut down other thread
    f.open("shutDownThread.bin", std::ios::binary);
    f.seekp(0);
    f << 1;
    f.close();
    return 0;
}
