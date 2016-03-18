//
//  main.cpp
//  CircleDetection
//
//  Created by Ives on 3/17/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

string filename = "circle.bmp";
double canny_threshold = 0.8;
double circle_threshold = 0.7;
int iterations = 10000;

vector<Vec3f> circles;

void circleRandomSelect(Mat &image, vector<Vec3f> &circles, double canny_threshold, double circle_threshold, int threshold);
void drawCicles(Mat image, vector<Vec3f> circles);
Point2d generateCircle();

int main(int argc, char *argv[]) {
    
    Mat image = imread(filename,0);
    
    circleRandomSelect(image, circles, canny_threshold, circle_threshold, iterations);
    
    cout << "Found " << (int)circles.size() << " Circles." << endl;
    
    drawCicles(image, circles);
    
    return 0;
}

void circleRandomSelect(Mat &image, vector<Vec3f> &circles, double canny_threshold, double circle_threshold, int threshold) {
    
    circles.clear();
    
    Mat verticles;
    Canny(image, verticles, MAX(canny_threshold/2,1), canny_threshold, 3);
    
    vector<Point2d> verticlesCollection;
    for(int i = 0; i < verticles.rows; i++) {
        for(int j = 0; j < verticles.cols; j++)  {
            if(verticles.at<unsigned char>(i,j) == 255) {
                verticlesCollection.push_back(cv::Point2d(j,i));
            }
        }
    }
    
    int x,y;
    Point2d center;
    double radius;
    Point2d point1, point2, point3, point4;
    
    double AB, BC, CA, DC;
    double m_AB, b_AB, m_BC, b_BC;
    double XmidPoint_AB, YmidPoint_AB, XmidPoint_BC, YmidPoint_BC;
    double m2_AB,m2_BC, b2_AB, b2_BC;

    
    RNG rng;
    int min_point_separation = 10;
    int colinear_tolerance = 1;
    int radius_threshold = 3;
    int verticlesCollection_threshold = 10;

    for(int iteration = 0; iteration < threshold; iteration++) {
        
        point1 = verticlesCollection[rng.uniform((int)0, (int)verticlesCollection.size())];
        point2 = verticlesCollection[rng.uniform((int)0, (int)verticlesCollection.size())];
        point3 = verticlesCollection[rng.uniform((int)0, (int)verticlesCollection.size())];
        point4 = verticlesCollection[rng.uniform((int)0, (int)verticlesCollection.size())];
        
        AB = norm(point1 - point2);
        BC = norm(point2 - point3);
        CA = norm(point3 - point1);
        DC = norm(point4 - point3);
        
        if(AB < min_point_separation || BC < min_point_separation || CA < min_point_separation || DC < min_point_separation) continue;
        
        m_AB = (point2.y - point1.y) / (point2.x - point1.x + 0.000000001);
        b_AB = point2.y - m_AB*point2.x;
        
        m_BC = (point3.y - point2.y) / (point3.x - point2.x + 0.000000001);
        b_BC = point3.y - m_BC*point3.x;
        
        
        if(abs(point3.y - (m_AB*point3.x + b_AB + colinear_tolerance)) < colinear_tolerance) continue;
        

        XmidPoint_AB = (point2.x + point1.x) / 2.0;
        YmidPoint_AB = m_AB * XmidPoint_AB + b_AB;
        m2_AB = -1.0 / m_AB;
        b2_AB = YmidPoint_AB - m2_AB*XmidPoint_AB;
        
        XmidPoint_BC = (point3.x + point2.x) / 2.0;
        YmidPoint_BC = m_BC * XmidPoint_BC + b_BC;
        m2_BC = -1.0 / m_BC;
        b2_BC = YmidPoint_BC - m2_BC*XmidPoint_BC;
        
        x = (b2_AB - b2_BC) / (m2_BC - m2_AB);
        y = m2_AB * x + b2_AB;
        center = Point2d(x,y);
        radius = norm(center - point2);
        
        if(abs(norm(point4 - center) - radius) > radius_threshold) continue;
        
        vector<int> votes;
        vector<int> no_votes;
        for(int i = 0; i < (int)verticlesCollection.size(); i++) {
            double vote_radius = norm(verticlesCollection[i] - center);
            
            if(abs(vote_radius - radius) < radius_threshold) {
                votes.push_back(i);
            }
            else {
                no_votes.push_back(i);
            }
        }
        
        if((float)votes.size() / (2.0 * CV_PI * radius) >= circle_threshold) {
            circles.push_back(Vec3f(x,y,radius));
            
            vector<Point2d> new_verticlesCollection;
            for(int i = 0; i < (int)no_votes.size(); i++) {
                new_verticlesCollection.push_back(verticlesCollection[no_votes[i]]);
            }
            verticlesCollection.clear();
            verticlesCollection = new_verticlesCollection;
        }
        
        if((int)verticlesCollection.size() < verticlesCollection_threshold)
            break;
    }
    
    return;
}

void drawCicles(Mat image, vector<Vec3f> circles) {
    cvtColor(image,image,CV_GRAY2RGB);
    for(int i = 0; i < (int)circles.size(); i++) {
        int x = circles[i][0];
        int y = circles[i][1];
        float rad = circles[i][2];
        circle(image, Point(x,y), rad, Scalar(255,0,0));
    }
    
    imshow("circles", image);
    waitKey();
}