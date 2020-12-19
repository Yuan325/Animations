//
//  rotation.hpp
//  Lab1
//
//  Created by Jia Yuan Teoh on 9/19/20.
//  Copyright © 2020 Jia Yuan Teoh. All rights reserved.
//

#include <vector>
#include <GLUT/GLUT.h>

GLdouble* fixedAngle(GLdouble x, GLdouble y, GLdouble z, GLdouble x_rotation, GLdouble y_rotation, GLdouble z_rotation);

GLdouble* quaternion( GLdouble x, GLdouble y, GLdouble z, GLdouble vx, GLdouble vy, GLdouble vz, GLdouble vw);

void displayMatrix(std::vector<GLdouble> matrix);

GLdouble* convertToDoubleAndTranspose(std::vector<GLdouble> matrix);
