//
//  RCDMethod.cpp
//  Cirecle-Detection
//
//  Created by Ives on 3/16/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#include "RCDMethod.hpp"

CirclePoint RCDMethod::findCandidateCircle(VergePoint p1, VergePoint p2, VergePoint p3, VergePoint p4) {
    int cov = (p1.y-p3.y)*(p1.y-p2.y) - (p1.x-p3.x)*(p1.x-p3.x);
    CramerRule cr;
    if (cov == 0) {
        cout << "A line" << endl;
        return CirclePoint(-1, -1, -1);
    } else {
        int mat[12] = {
            2*p1.x, 2*p1.y, 1, static_cast<int>(pow(p1.x, 2)+pow(p1.y, 2)),
            2*p2.x, 2*p2.y, 1, static_cast<int>(pow(p2.x, 2)+pow(p2.y, 2)),
            2*p3.x, 2*p3.y, 1, static_cast<int>(pow(p3.x, 2)+pow(p3.y, 2))
        };
        cr.initMatrix(mat);
        Solution sl = cr.calculateAns();
        if (sl.x != -1 && sl.y != -1 && sl.z != -1) {
            float r = sqrt(pow(sl.x, 2) + pow(sl.y, 2) + sl.z);
            cout << "Get a Circle: (" << sl.x << ", " << sl.y << "), r:" << r << endl;
        }
        
        return CirclePoint(0, 0, 0);
    }
}

void RCDMethod::randomSelectPoint() {
}