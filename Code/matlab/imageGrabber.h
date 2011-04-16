#pragma once

#include "mex.h"

// OpenCV includes
#include "cv.h"
#include "highgui.h"

// Starts main loop of reading frame data
void ImageGrabberStartLoop();
// Grabs a single image from the camera
const IplImage* ImageGrabberGetCameraImage();
