//
//  cramer-rule.h
//  Cirecle-Detection
//
//  Created by Ives on 3/16/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#ifndef cramer_rule_h
#define cramer_rule_h
#include <iostream>
#include <tuple>

using namespace::std;

struct Solution {
    float x;
    float y;
    float z;
    
    Solution (float inx, float iny, float inz) {
        x = inx;
        y = iny;
        z = inz;
    }
};

class CramerRule {
    int matrix[12];
public:
    void initMatrix(int m[12]);
    int determinateOfMatrix(int matrix[9]);
    Solution calculateAns();
};

void initMatrix(int mat[12]);
int determinateOfMatrix(int mat[9]);
Solution calculateAns();


#endif /* cramer_rule_h */
