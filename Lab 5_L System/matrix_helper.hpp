//
//  matrix_helper.hpp
//  Lab 5
//
//  Created by Jia Yuan Teoh on 12/14/20.
//

#include <math.h>
#include <vector>
#include <iostream>
#include <GLUT/GLUT.h>

GLdouble* convertToDoubleAndTranspose(std::vector<GLdouble> matrix);

std::vector<GLdouble> matrixMultiply(std::vector<GLdouble> x, std::vector<GLdouble> y);

void displayMatrix(std::vector<GLdouble> matrix);
