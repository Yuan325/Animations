//
//  matrix_helper.cpp
//  Lab 5
//
//  Created by Jia Yuan Teoh on 12/14/20.
//

#include "matrix_helper.hpp"

// convert vector to double array and transpose for openGL rendering
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

// multiply 2 input matrix
std::vector<GLdouble> matrixMultiply(std::vector<GLdouble> x, std::vector<GLdouble> y){
    std::vector<GLdouble> res(16,0);
    
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                res[4*i+j] += x[4*i+k]*y[4*k+j];
            }
        }
    }
    
    return res;
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
