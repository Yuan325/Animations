//
//  rotation.hpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/29/20.
//

#include <vector>
#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
#include "matrix_helper.hpp"

std::vector<GLdouble> fixedAngle(GLdouble x, GLdouble y, GLdouble z, GLdouble x_rotation, GLdouble y_rotation, GLdouble z_rotation);

std::vector<GLdouble> quaternion( GLdouble x, GLdouble y, GLdouble z, GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw);

std::vector<GLdouble> x_rotation_matrix(GLdouble theta);

std::vector<GLdouble> y_rotation_matrix(GLdouble theta);

std::vector<GLdouble> z_rotation_matrix(GLdouble theta);
