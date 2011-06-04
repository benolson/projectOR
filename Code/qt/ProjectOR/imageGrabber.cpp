#include "imageGrabber.h"
#include <QImage>
#include <windows.h>
#include <fstream>
#include <iostream>

void ImageGrabberStartLoop(int imageWidth, int imageHeight, IplImage** image, QMutex* cameraLock)
{
    // Images to capture the frame from video or camera or from file
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

    // If loaded succesfully, then:
    if( capture )
    {        
        unsigned long iterations = 0;
        // Capture from the camera.
        while (1)
        {
            // check to exit
            if (iterations % 20 == 0)
            {
                char buffer[8];
                std::ifstream f("shutDownThread.bin", std::ios::binary);
                f.read(buffer,1);
                f.close();
                // Release the images, and capture memory
                if (buffer[0] != '0')
                {
                    cvReleaseCapture( &capture);
                    return;
                }
            }

            cameraLock->lock();
            *image = cvQueryFrame(capture);

            // If the frame does not exist, quit the loop
            if( !*image )
                break;
            cvFlip(*image, 0, 0 );
            cvCvtColor(*image,*image,CV_BGR2RGB);
            cameraLock->unlock();
            //cvSaveImage(fileName, frame);
            Sleep(60);
            iterations++;
        }
    }			


}

///////////////////////////////////// ImageGrabber //////////////////////////////////////////////

ImageGrabber::ImageGrabber(IplImage** image, QMutex* cameraLock, QObject* parent)
    : QObject(parent)
{
    m_image = image;
    m_cameraLock = cameraLock;
}

void ImageGrabber::saveCameraImage(Image& image)
{
    image.width = width();
    image.height = height();
    image.data = new char[3*image.width*image.height];
    lockCamera();
    memcpy(image.data, (*m_image)->imageData, image.width*image.height*3);
    unlockCamera();
}

IplImage* ImageGrabber::saveCameraImageIplImage()
{
    IplImage* out = cvCreateImage(cvSize(width(),height()), IPL_DEPTH_8U, 1);
    lockCamera();
    cvCvtColor(*m_image, out, CV_RGB2GRAY);
    unlockCamera();
    return out;
}

void ImageGrabber::saveCameraImageToDisk()
{
    lockCamera();
    cvFlip(*m_image, 0, 0 );
    cvSaveImage("cameraScreenshot.png", *m_image);
    cvFlip(*m_image, 0, 0 );
    unlockCamera();
}

void ImageGrabber::saveImageToDisk(Image& img, char* fileName)
{
    QImage qIMG((unsigned char*)img.data, img.width, img.height, QImage::Format_RGB888);
    qIMG.save(fileName, QString("png").toAscii());
}

void ImageGrabber::saveImageToDiskIplImage(IplImage* img, char* fileName)
{
    cvSaveImage(fileName, img);
}
