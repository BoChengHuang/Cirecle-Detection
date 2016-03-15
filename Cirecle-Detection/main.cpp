//
//  main.cpp
//  Cirecle-Detection
//
//  Created by Ives on 3/15/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cramer-rule.hpp"
#include "RCDMethod.hpp"

using namespace::std;
using namespace::cv;

Mat src_img, src_gray;
Mat dst, detected_edges;
int width, height;
int ratio = 3;
int kernel_size = 3;
int lowThreshold;
String window_name = "Result window";

void printMap(Mat img) {
    width = img.size().width;
    height = img.size().height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Scalar intensity = img.at<uchar>(j, i);
            //cout << "(" << i << ", " << j << ")";
            cout << intensity[0] << " ";
            if (j == height - 1) {
                cout << endl;
            }
        }
    }
}

void CannyThreshold(int, void*) {
    blur(src_gray, detected_edges, Size(3,3));
    
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*3,  kernel_size);
    
    dst = Scalar::all(0);
    
    src_img.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int argc, const char * argv[]) {
    
    src_img = imread("circle.bmp");
    
    if (src_img.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    
    dst.create(src_img.size(), src_img.type());
    cvtColor(src_img, src_gray, CV_BGR2GRAY);
    
    CannyThreshold(0, 0);
    
    // print pixels
    //printMap(dst);
    
    RCDMethod rcd;
    rcd.findCandidateCircle(VergePoint(2, 0), VergePoint(0, 2), VergePoint(-2, 0), VergePoint(0, -1));
    
    
    namedWindow(window_name, WINDOW_AUTOSIZE);
    //imshow(window_name, src_img);
    
    waitKey(0);
    
    return 0;
}

