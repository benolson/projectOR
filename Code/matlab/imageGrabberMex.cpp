#include "imageGrabber.h"

void mexFunction(int output_size, mxArray *output[], int input_size, const mxArray *input[])
{
    const IplImage* img = ImageGrabberGetCameraImage();
    //const IplImage* img = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);  
    // Allocate output variable
    double *Data;
    output[0] = mxCreateDoubleMatrix(img->height, img->width, mxREAL);
    Data = mxGetPr(output[0]); // Get the pointer to output variable
    
    int height     = img->height;
    int width      = img->width;
    int step       = img->widthStep/sizeof(uchar);
    int channels   = img->nChannels;
    uchar* data    = (uchar *)img->imageData;
    for(int i=0; i<img->height; i++) {
        for(int j=0; j<img->width; j++) {           
            Data[i+j*(img->height)] = data[i*step+j*channels+1];
        }
    }
        
}

void ImageGrabberStartLoop()
{
  // Allocate the memory storage for calculations and frame data
  CvMemStorage* storage = cvCreateMemStorage(0);
  CvCapture* capture = cvCaptureFromCAM(0);
  // Images to capture the frame from video or camera or from file
  IplImage *frame = 0;
  IplImage *frame_copy = 0;
  cvNamedWindow( "result", 1 );
  // If loaded succesfully, then:
  if( capture )
  {
    bool breakLoop = false;
    // Capture from the camera.
    for(;;)
    {
      if (breakLoop)
        break;
      // Capture the frame and load it in IplImage
      if( !cvGrabFrame( capture ))
        break;
      frame = cvRetrieveFrame( capture );

      // If the frame does not exist, quit the loop
      if( !frame )
        break;

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

      cvShowImage("result",frame_copy);

      // Wait for a while before proceeding to the next frame
      int key = cvWaitKey(1);
      switch(key)
      {					
      case -1:
        break;
      default:
        breakLoop = true;
      }            
    }			
  }
  // Destroy the window previously created with filename: "result"
  cvDestroyWindow("result");
  // Release the images, and capture memory
  cvReleaseCapture( &capture ); 
  cvReleaseImage( &frame_copy );

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