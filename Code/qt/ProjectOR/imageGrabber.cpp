#include "imageGrabber.h"
#include <windows.h>
#include <fstream>
#include <iostream>

void ImageGrabberStartLoop(int imageWidth, int imageHeight, IplImage** image)
{
    // Images to capture the frame from video or camera or from file
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

    // If loaded succesfully, then:
    if( capture )
    {        
        // Capture from the camera.
        while (1)
        {
            *image = cvQueryFrame(capture);

            // If the frame does not exist, quit the loop
            if( !*image )
                break;
            cvFlip(*image, 0, 0 );
            cvCvtColor(*image,*image,CV_BGR2RGB);
            //cvSaveImage(fileName, frame);
        }
    }			

    // Release the images, and capture memory
    cvReleaseCapture( &capture );
}

const IplImage* ImageGrabberGetCameraImage()
{
    // Allocate the memory storage for calculations and frame data
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvCapture* capture = cvCaptureFromCAM(0);
    // Images to capture the frame from video or camera or from file
    IplImage *frame = 0;
    IplImage *frame_copy = 0;
    // If loaded succesfully, then:
    if( capture )
    {
        // Capture the frame and load it in IplImage
        if( !cvGrabFrame( capture ))
        {
            // Release the images, and capture memory
            cvReleaseCapture( &capture );
            return 0;
        }
        frame = cvRetrieveFrame( capture );

        // If the frame does not exist, quit
        if( !frame )
        {
            // Release the images, and capture memory
            cvReleaseCapture( &capture );
            return 0;
        }

        // Allocate framecopy as the same size of the frame
        if( !frame_copy )
            frame_copy = cvCreateImage( cvSize(frame->width,frame->height),
                                        IPL_DEPTH_8U, frame->nChannels );

        // Check the origin of image. If top left, copy the image frame to frame_copy.
        if( frame->origin == IPL_ORIGIN_TL )
            cvCopy( frame, frame_copy, 0 );
        // Else flip and copy the image
        else
            cvFlip( frame, frame_copy, 0 );

        // Release the capture but not the image
        cvReleaseCapture( &capture );
        // return final image
        return frame_copy;
    }

    // Release the images, and capture memory
    cvReleaseCapture( &capture );
    cvReleaseImage( &frame_copy );
    return 0;
}

void ImageGrabberTakeScreenshot(const char* fileName, int imageWidth, int imageHeight)
{
    // Allocate the memory storage for calculations and frame data
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvCapture* capture = cvCreateCameraCapture(0);
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, imageWidth );
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, imageHeight );
    // Images to capture the frame from video or camera or from file
    IplImage *frame = 0;
    IplImage *frame_copy = 0;
    // If loaded succesfully, then:
    if( capture )
    {
        // Capture the frame and load it in IplImage
        if( !cvGrabFrame( capture ))
        {
            // Release the images, and capture memory
            cvReleaseCapture( &capture );
            return;
        }
        frame = cvRetrieveFrame( capture );

        // If the frame does not exist, quit
        if( !frame )
        {
            // Release the images, and capture memory
            cvReleaseCapture( &capture );
            return;
        }

        // Allocate framecopy as the same size of the frame
        if( !frame_copy )
            frame_copy = cvCreateImage( cvSize(frame->width,frame->height),
                                        IPL_DEPTH_8U, frame->nChannels );

        // Check the origin of image. If top left, copy the image frame to frame_copy.
        if( frame->origin == IPL_ORIGIN_TL )
            cvCopy( frame, frame_copy, 0 );
        // Else flip and copy the image
        else
            cvFlip( frame, frame_copy, 0 );
        cvSaveImage(fileName, frame_copy);
    }

    // Release the images, and capture memory
    cvReleaseCapture( &capture );
    cvReleaseImage( &frame_copy );
    return;
}
