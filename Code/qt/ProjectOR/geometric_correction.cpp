    #include <stdio.h>
    #include "cv.h"
    #include "highgui.h"
    #include "cxcore.hpp"
    #include "highgui.hpp"
            
//    CvPoint sub(CvPoint a, CvPoint b) {
//      return cvPoint(a.x-b.x,a.y-b.y);
//    }
    
//    double cp2d(CvPoint a, CvPoint b) {
//      return double(a.x*b.y - b.x*a.y);
//    }
    
//    int main2(int argc, char** argv) {
//      // Tunable parameters
//      int mask_threshold = 50;  // set higher for brighter scenes
//      double quad_fit = .9999;  // proportion of image that fits in quad
//      int corner_offset = 20;   // how far inward the corner dots are
//      int blur_amount = 75;     // should not need much tuning
        
//      // Load calibration images (projecting black + projecting corners)
//      IplImage* black_img = cvLoadImage("black.png", CV_LOAD_IMAGE_GRAYSCALE);
//      IplImage* white_img = cvLoadImage("white.png", CV_LOAD_IMAGE_GRAYSCALE);
//      IplImage* corners_img = cvLoadImage("corners.png", CV_LOAD_IMAGE_GRAYSCALE);
      
//      // Background subtraction + blurring
//      IplImage* out = cvCreateImage(cvSize(800, 600), IPL_DEPTH_8U, 1);
//      cvSub(corners_img, black_img, out);
//      cvSmooth(out, out, CV_GAUSSIAN, blur_amount, blur_amount);

//      // Find corners
//      CvPoint corners[4];
//      CvRect ROIs[4] = {cvRect(blur_amount, blur_amount, 400, 300),
//                        cvRect(400, blur_amount, 800, 300),
//                        cvRect(blur_amount, 300, 400, 600),
//                        cvRect(400, 300, 800, 600)};
//      double minVal, maxVal;
//      CvPoint minLoc, maxLoc;
//      for(int i=0; i<4; i++) {
//        cvSetImageROI(out, ROIs[i]);
//        cvMinMaxLoc(out, &minVal, &maxVal, &minLoc, &maxLoc);
//        corners[i] = CvPoint(maxLoc);
//        corners[i].x += ROIs[i].x;
//        corners[i].y += ROIs[i].y;
//      }

//      // Compute mask
//      IplImage* mask = cvCreateImage(cvSize(800, 600), IPL_DEPTH_8U, 1);
//      cvSub(white_img, black_img, mask);
//      cvCmpS(mask, mask_threshold, mask, CV_CMP_GE);
      
//      // Fit quad to mask
//      CvPoint center = cvPoint(400, 300);
//      int size = 1;
//      bool done = false;
//      while (!done) {
//        done = true;
//        cvSetImageROI(mask, cvRect(center.x - 4*size, center.y - 3*size,
//                                   8*size, 6*size));
//        double threshold = quad_fit*255*8*6*size*size;
//        if (cvSum(mask).val[0] >= threshold) { // grow quad while possible
//          size++;
//          done = false;
//        }
//        else { // see if moving the center helps
//          int dx = 0;
//          int dy = 0;
//          double best_sum = cvSum(mask).val[0];
//          for(int i=-1; i<=1; i++) {
//            for(int j=-1; j<=1; j++) {
//                cvSetImageROI(mask, cvRect(center.x - 4*size + i,
//                                           center.y - 3*size + j,
//                                           8*size, 6*size));
//                double sum = cvSum(mask).val[0];
//                if (sum > best_sum) {
//                  dx = i;
//                  dy = j;
//                  best_sum = sum;
//                }
//            }
//          }
//          if (dx != 0 || dy != 0) { // if it helped, keep growing
//            center.x += dx;
//            center.y += dy;
//            size--;
//            done = false;
//          }
//        }
//      }
//      size-=2;
//      CvPoint quad[4] = {cvPoint(center.x - 4*size, center.y - 3*size),
//                         cvPoint(center.x + 4*size, center.y - 3*size),
//                         cvPoint(center.x - 4*size, center.y + 3*size),
//                         cvPoint(center.x + 4*size, center.y + 3*size)};

//      // Infer transformation
//      CvPoint img_corners[4] = {cvPoint(corner_offset, corner_offset),
//                                cvPoint(1024 - corner_offset, corner_offset),
//                                cvPoint(corner_offset, 768 - corner_offset),
//                                cvPoint(1024 - corner_offset, 768 - corner_offset)};
//      CvPoint new_corners[4];
      
//      for(int i=0; i<4; i++) {
//        CvPoint p0p = sub(corners[0], quad[i]);
//        CvPoint p1p = sub(corners[1], quad[i]);
//        CvPoint p02 = sub(corners[0], corners[2]);
//        CvPoint p13 = sub(corners[1], corners[3]);

//        double a = cp2d(p0p, p02);
//        double b = .5*cp2d(p0p, p13) + .5*cp2d(p1p, p02);
//        double c = cp2d(p1p, p13);
//        double s = (a-b + sqrt(b*b - a*c)) / (a - 2*b + c);
//        double t = ((1-s)*(corners[0].x-quad[i].x) + s*(corners[1].x-quad[i].x))/
//                   ((1-s)*(corners[0].x-corners[2].x) + s*(corners[1].x-corners[3].x));
      
//        double x = (1-s)*((1-t)*img_corners[0].x + t*img_corners[2].x) +
//                       s*((1-t)*img_corners[1].x + t*img_corners[3].x);
//        double y = (1-s)*((1-t)*img_corners[0].y + t*img_corners[2].y) +
//                       s*((1-t)*img_corners[1].y + t*img_corners[3].y);
//        new_corners[i] = cvPoint(int(x), int(y));
//      }
      
//      // new_corners contains the coordinates the corners should be moved
//      // to, in order top-left top-right bottom-left bottom-right
      
//        return 0;
//    }
    
 
    
