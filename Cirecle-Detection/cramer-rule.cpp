//
//  cramer-rule.cpp
//  Cirecle-Detection
//
//  Created by Ives on 3/15/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

/*
 Demonstrating Cramer's Rule.
 Order of matrix representation:
 0 1 2
 3 4 5
 6 7 8
 */

// Note: Uses the + - + sign pattern for the terms in the expansion.
// Find the determinate of a 3x3 Matrix.

#include <iostream>
#include <tuple>
#include "cramer-rule.hpp"

using namespace::std;

void CramerRule::initMatrix(int mat[12]) {
    for (int i = 0; i < 12; i++) {
        matrix[i] = mat[i];
    }
}

int CramerRule::determinateOfMatrix(int mat[9]) {
    return mat[0] * ((mat[4] * mat[8]) - (mat[5] * mat[7])) -
    mat[3] * ((mat[1] * mat[8]) - (mat[2] * mat[7])) +
    mat[6] * ((mat[1] * mat[5]) - (mat[2] * mat[4]));
}

Solution CramerRule::calculateAns() {
    
    int matrix_D[9]{ matrix[0], matrix[1] , matrix[2],
        matrix[4] , matrix[5] , matrix[6] ,
        matrix[8] , matrix[9] , matrix[10] };
    int deter_D = determinateOfMatrix(matrix_D);
    
    int matrix_Dx[9]{ matrix[3], matrix[1] , matrix[2],
        matrix[7] , matrix[5] , matrix[6] ,
        matrix[11] , matrix[9] , matrix[10] };
    int deter_Dx = determinateOfMatrix(matrix_Dx);
    
    int matrix_Dy[9]{ matrix[0], matrix[3] , matrix[2],
        matrix[4] , matrix[7] , matrix[6] ,
        matrix[8] , matrix[11] , matrix[10] };
    int deter_Dy = determinateOfMatrix(matrix_Dy);
    
    int matrix_Dz[9]{ matrix[0], matrix[1] , matrix[3],
        matrix[4] , matrix[5] , matrix[7] ,
        matrix[8] , matrix[9] , matrix[11] };
    int deter_Dz = determinateOfMatrix(matrix_Dz);
    
    /*
    cout << "determinate D = " << deter_D << endl;
    cout << "determinate Dx = " << deter_Dx << endl;
    cout << "determinate Dy = " << deter_Dy << endl;
    cout << "determinate Dz = " << deter_Dz << "\n" << endl;*/
    
    if (deter_D != 0) {
        int x = deter_Dx / deter_D;
        int y = deter_Dy / deter_D;
        int z = deter_Dz / deter_D;
        
        cout << "Solution is (" << x << "," << y << "," << z << ")" << endl;
        return Solution(x, y, z);
    }
    else {
        cout << "Your equation can not be solved with Cramer's Rule\n" << endl;
        return Solution(0, 0, 0);
    }
    
}
