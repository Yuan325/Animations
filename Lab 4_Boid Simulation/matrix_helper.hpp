//
//  matrix_helper.hpp
//  Lab4
//
//  Created by Jia Yuan Teoh on 11/20/20.
//

#include <math.h>
#include <vector>
#include <iostream>
#include <GLUT/GLUT.h>

GLdouble* convertToDoubleAndTranspose(std::vector<GLdouble> matrix);

std::vector<GLdouble> matrixMultiply(std::vector<GLdouble> x, std::vector<GLdouble> y);

void displayMatrix(std::vector<GLdouble> matrix);
