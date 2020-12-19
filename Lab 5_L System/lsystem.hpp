//
//  lsystem.hpp
//  Lab 5
//
//  Created by Jia Yuan Teoh on 12/14/20.
//

#include <GLUT/GLUT.h>
#include <string>
#include "matrix_helper.hpp"
#include "hierarchy.hpp"

void lsystem(int depth_input, GLdouble angle_input, std::string A_input, std::string B_input, std::string axiom_input);
void draw();
void replace();
