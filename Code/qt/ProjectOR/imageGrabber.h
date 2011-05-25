#ifndef __IMAGEGRABBER__
#define __IMAGEGRABBER__

// OpenCV includes
#include "cv.h"
#include "highgui.h"

// Starts main loop of reading frame data
void ImageGrabberStartLoop(int imageWidth, int imageHeight, IplImage** image);
// Grabs a single image from the camera
const IplImage* ImageGrabberGetCameraImage();
// Takes a screenshot and saves to file
void ImageGrabberTakeScreenshot(const char* fileName, int imageWidth, int imageHeight);

#endif
