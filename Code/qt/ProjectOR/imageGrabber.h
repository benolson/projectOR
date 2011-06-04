#ifndef __IMAGEGRABBER__
#define __IMAGEGRABBER__

#include <QObject>
#include <QMutex>

// OpenCV includes
#include "cv.h"
#include "highgui.h"

// Starts main loop of reading frame data
void ImageGrabberStartLoop(int imageWidth, int imageHeight, IplImage** image, QMutex* cameraLock);

struct Image
{
    char* data;
    int width;
    int height;
};

class ImageGrabber : public QObject
{
public:
    ImageGrabber(IplImage** image, QMutex* cameraLock, QObject* parent = 0);

    void lockCamera() {m_cameraLock->lock();}
    void unlockCamera() {m_cameraLock->unlock();}
    int width() {return (*m_image)->width;}
    int height() {return (*m_image)->height;}
    char* getData() {return (*m_image)->imageData;}
    void saveCameraImage(Image& saveImage);
    IplImage* saveCameraImageIplImage();
    void saveCameraImageToDisk();
    void saveImageToDisk(Image& img, char* fileName);
    void saveImageToDiskIplImage(IplImage* img, char* fileName);

private:
    IplImage** m_image;
    QMutex* m_cameraLock;
};

#endif
