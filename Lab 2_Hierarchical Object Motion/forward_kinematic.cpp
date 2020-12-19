//
//  forward_kinematic.cpp
//  Lab2
//
//  Created by Jia Yuan Teoh on 10/10/20.
//

#include "forward_kinematic.hpp"

std::vector<GLdouble> heirarchyTransformation(GLdouble l1_x, GLdouble l1_y, GLdouble l1_z, GLdouble r_x, GLdouble r_y, GLdouble r_z, GLdouble l2_x, GLdouble l2_y, GLdouble l2_z){
    std::vector<GLdouble> translate1(16, 0), rotate(16,0), translate2(16, 0), matrix_final(16, 0);
    
    // construct T1
    translate1[4*0+0] = 1;
    translate1[4*1+1] = 1;
    translate1[4*2+2] = 1;
    translate1[4*3+3] = 1;
    translate1[4*0+3] = l1_x;
    translate1[4*1+3] = l1_y;
    translate1[4*2+3] = l1_z;

    // construct R
    rotate = matrixMultiply(z_rotation_matrix(r_z), y_rotation_matrix(r_y));
    rotate = matrixMultiply(rotate, x_rotation_matrix(r_x));
    
    // construct T2
    translate2[4*0+0] = 1;
    translate2[4*1+1] = 1;
    translate2[4*2+2] = 1;
    translate2[4*3+3] = 1;
    translate2[4*0+3] = l2_x;
    translate2[4*1+3] = l2_y;
    translate2[4*2+3] = l2_z;
    
    // construct TRT forward kinematic matrix
    matrix_final = matrixMultiply(rotate, translate1);
    matrix_final = matrixMultiply(translate2, matrix_final);

    return matrix_final;
}
