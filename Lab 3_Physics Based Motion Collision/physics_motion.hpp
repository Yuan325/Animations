//
//  physics_motion.hpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/29/20.
//

#include <GLUT/glut.h>
#include <vector>
#include "rotation.hpp"

std::vector<GLdouble> physics_motion(std::vector<GLdouble> obj, int n);

std::vector<GLdouble> getMatrix(std::vector<GLdouble> obj, int cur);
