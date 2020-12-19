//
//  rotation.cpp
//  Lab1
//
//  Created by Jia Yuan Teoh on 9/19/20.
//  Copyright © 2020 Jia Yuan Teoh. All rights reserved.
//

#include <vector>
#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
#include "rotation.h"

GLdouble* fixedAngle(GLdouble x, GLdouble y, GLdouble z, GLdouble x_rotation, GLdouble y_rotation, GLdouble z_rotation){
    std::vector<GLdouble> matrix_x(16, 0),matrix_y(16, 0),matrix_z(16, 0),matrix_multiple(16, 0),matrix_final(16, 0);
    
    // Construct matrix for x_rotation
    matrix_x[4*0+0] = cos(x_rotation);
    matrix_x[4*0+1] = -sin(x_rotation);
    matrix_x[4*1+0] = sin(x_rotation);
    matrix_x[4*1+1] = cos(x_rotation);
    matrix_x[4*2+2] = 1;
    matrix_x[4*3+3] = 1;
    // Construct matrix for y_rotation
    matrix_y[4*0+0] = cos(y_rotation);
    matrix_y[4*0+2] = sin(y_rotation);
    matrix_y[4*1+1] = 1;
    matrix_y[4*2+0] = -sin(y_rotation);
    matrix_y[4*2+2] = cos(y_rotation);
    matrix_y[4*3+3] = 1;
    // Construct matrix for z_rotation
    matrix_z[4*0+0] = 1;
    matrix_z[4*1+1] = cos(z_rotation);
    matrix_z[4*1+2] = -sin(z_rotation);
    matrix_z[4*2+1] = sin(z_rotation);
    matrix_z[4*2+2] = cos(z_rotation);
    matrix_z[4*3+3] = 1;

    // Multiple 3 matrix
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                matrix_multiple[4*i+j] += matrix_z[4*i+k]*matrix_y[4*k+j];
            }
        }
    }
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                matrix_final[4*i+j] += matrix_multiple[4*i+k]*matrix_x[4*k+j];
            }
        }
    }
    
    // Insert x y z translation
    matrix_final[4*0+3] = x;
    matrix_final[4*1+3] = y;
    matrix_final[4*2+3] = z-2;
    
    return convertToDoubleAndTranspose(matrix_final);
}

GLdouble normalized_magnitude(GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw){
    GLdouble a;
    a = sqrt(vx*vx + vy*vy + vz*vz + vw*vw);
    return a;
}

GLdouble* quaternion( GLdouble x, GLdouble y, GLdouble z, GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw){
    std::vector<GLdouble> matrix_final(16, 0);
    std::cout<< vx << " "<< vy << " "<< vz << " " << vw<< std::endl;
    GLdouble norm = normalized_magnitude(vx, vy, vz, vw);
    vx = vx/norm;
    vy = vy/norm;
    vz = vz/norm;
    vw = vw/norm;
    if(norm == 0){
        vx = 0;
        vy = 0;
        vz = 0;
        vw = 0;
    }
    
    // Construct 16 values for quaternion
    matrix_final[4*0+0] = 1 - (2*vy*vy) - (2*vz*vz);
    matrix_final[4*0+1] = (2*vx*vy) - (2*vw*vz);
    matrix_final[4*0+2] = (2*vx*vz) + (2*vw*vy);
    matrix_final[4*1+0] = (2*vx*vy) + (2*vw*vz);
    matrix_final[4*1+1] = 1 - (2*vx*vx) - (2*vz*vz);
    matrix_final[4*1+2] = (2*vy*vz) - (2*vw*vx);
    matrix_final[4*2+0] = (2*vx*vz) - (2*vw*vy);
    matrix_final[4*2+1] = (2*vy*vz) + (2*vw*vx);
    matrix_final[4*2+2] = 1 - (2*vx*vx) - (2*vy*vy);
    matrix_final[4*3+3] = 1;
    
    // Insert x y z translation
    matrix_final[4*0+3] = x;
    matrix_final[4*1+3] = y;
    matrix_final[4*2+3] = z-2;
    
    return convertToDoubleAndTranspose(matrix_final);
}

// Display 1-D vector as 2-D
// For sanity checking, not a required method
void displayMatrix(std::vector<GLdouble> matrix){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << matrix[4*i+j] << " ";
        }
        std::cout << std::endl;
    }
}

// Converting vector into an array (to fit glLoadMatrix's input parameter format)
GLdouble* convertToDoubleAndTranspose(std::vector<GLdouble> matrix){
    GLdouble* a = new GLdouble[16];
    int k = 0;
    std::cout << std::endl;
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            a[k] = matrix[4*j+i];
            k++;
        }
    }
    return a;
}
