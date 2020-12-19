//
//  rotation.cpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/29/20.
//

#include "rotation.hpp"

std::vector<GLdouble> fixedAngle(GLdouble x, GLdouble y, GLdouble z, GLdouble x_rotation, GLdouble y_rotation, GLdouble z_rotation){
    std::vector<GLdouble> matrix_x(16, 0), matrix_y(16, 0), matrix_z(16, 0), matrix_final(16, 0);
    
    matrix_x = x_rotation_matrix(x_rotation);
    matrix_y = y_rotation_matrix(y_rotation);
    matrix_z = z_rotation_matrix(z_rotation);

    // Multiple 3 matrix
    matrix_final = matrixMultiply(matrix_z, matrix_x);
    matrix_final = matrixMultiply(matrix_final, matrix_y);

    // Insert x y z translation
    matrix_final[4*0+3] = x;
    matrix_final[4*1+3] = y;
    matrix_final[4*2+3] = z;
    
    return matrix_final;
}

GLdouble normalized_magnitude(GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw){
    GLdouble a;
    a = sqrt(vx*vx + vy*vy + vz*vz + vw*vw);
    return a;
}

std::vector<GLdouble> quaternion( GLdouble x, GLdouble y, GLdouble z, GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw){
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
    
    return matrix_final;
}

// construct matrix for x_rotation
std::vector<GLdouble> x_rotation_matrix(GLdouble theta){
    std::vector<GLdouble> matrix(16,0);
    matrix[4*0+0] = cos(theta);
    matrix[4*0+1] = -sin(theta);
    matrix[4*1+0] = sin(theta);
    matrix[4*1+1] = cos(theta);
    matrix[4*2+2] = 1;
    matrix[4*3+3] = 1;
    
    return matrix;
}

// construct matrix for y_rotation
std::vector<GLdouble> y_rotation_matrix(GLdouble theta){
    std::vector<GLdouble> matrix(16,0);
    matrix[4*0+0] = cos(theta);
    matrix[4*0+2] = sin(theta);
    matrix[4*1+1] = 1;
    matrix[4*2+0] = -sin(theta);
    matrix[4*2+2] = cos(theta);
    matrix[4*3+3] = 1;
    
    return matrix;
}

// construct matrix for z_rotation
std::vector<GLdouble> z_rotation_matrix(GLdouble theta){
    std::vector<GLdouble> matrix(16,0);
    matrix[4*0+0] = 1;
    matrix[4*1+1] = cos(theta);
    matrix[4*1+2] = -sin(theta);
    matrix[4*2+1] = sin(theta);
    matrix[4*2+2] = cos(theta);
    matrix[4*3+3] = 1;
    
    return matrix;
}
