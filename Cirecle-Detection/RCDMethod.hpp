//
//  RCDMethod.hpp
//  Cirecle-Detection
//
//  Created by Ives on 3/16/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#ifndef RCDMethod_hpp
#define RCDMethod_hpp

#include <iostream>
#include <math.h>
#include <stdio.h>
#include "cramer-rule.hpp"

struct VergePoint {
    int x;
    int y;
    
    VergePoint(int inx, int iny) {
        x = inx;
        y = iny;
    }
};

struct CirclePoint {
    float x;
    float y;
    float r;
    
    CirclePoint(float inx, float iny, float inr) {
        x = inx;
        y = iny;
        r = inr;
    }
};

class RCDMethod {
    
public:
    CirclePoint findCandidateCircle(VergePoint p1, VergePoint p2, VergePoint p3, VergePoint p4);
    void randomSelectPoint();
    void CannyThreshold(int, void*);
};

#endif /* RCDMethod_hpp */
