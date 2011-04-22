
#include "mex.h"
#include "opencv/cv.h" 
#include "opencv2/features2d/features2d.hpp"

#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

IplImage* load_image(mxArray *input) {
    double *vals = mxGetPr(input);
    int n = mxGetN(input);
    int m = mxGetM(input);
    
    IplImage* img = cvCreateImage(cvSize(n, m), IPL_DEPTH_8U, 1);

    for(int i=0;i<n;i++) {
       for(int j=0;j<m;j++) {        
            img->imageData[i*n+i] = vals[(i*m)+j];
        }
    }
    
    return img;
}

void mexFunction(int output_size, mxArray *output[], int input_size, const mxArray *input[])
{    
    IplImage* imag1 = load_image((mxArray*) input[0]);
    //IplImage* imag2 = load_image((mxArray*) input[1]);
    Mat img1(imag1);
    //Mat img2(imag2);
   
	// detecting keypoints
	SurfFeatureDetector detector(400);
	vector<KeyPoint> keypoints1, keypoints2;
	detector.detect(img1, keypoints1);
	//detector.detect(img2, keypoints2);

	// computing descriptors
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(img1, keypoints1, descriptors1);
	//extractor.compute(img2, keypoints2, descriptors2);

	// matching descriptors
	//WindowedMatcher matcher(40,40);
    //vector<DMatch> matches;
    //matcher.match(descriptors1, descriptors2, matches);

    //namedWindow("matches", 1);
	//Mat img_matches;
	//drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
	//imshow("matches", img_matches);
	//waitKey(0);
    
    // Allocate output variable
    double *Data;
    
    // keypoints1[index].pt.x
    
    output[0] = mxCreateDoubleMatrix(keypoints1.size(), 2+128, mxREAL);
    Data = mxGetPr(output[0]); 
    int n = keypoints1.size();
    for(int i = 0; i < n; i++)
    {
        //int a = matches[i].queryIdx;
        //int b = matches[i].trainIdx;        
        Data[i] = keypoints1[i].pt.y;
        Data[i+n] = keypoints1[i].pt.x;
        for(int j=0; j<128; j++) {
            Data[i+n*(j+2)] = descriptors1.at<float>(i,j);   
        }
        //Data[i+2*n] = keypoints2[b].pt.y;
        //Data[i+3*n] = keypoints2[b].pt.x;
        //Data[i+4*n] = matches[i].distance;
        // keypoints1[b]
        
    }
    

    //output[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    //    Data = mxGetPr(output[0]); // Get the pointer to output variable
    //    Data[0] = -1;
    
       
    // Release all the memory
    cvReleaseImage( &imag1 );
    //cvReleaseImage( &imag2 );
    return;
}

