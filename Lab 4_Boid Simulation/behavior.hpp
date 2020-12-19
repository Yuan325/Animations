//
//  behavior.hpp
//  Lab4
//
//  Created by Jia Yuan Teoh on 11/20/20.
//

#include <GLUT/glut.h>
#include <vector>
#include <stdlib.h>

#include "rotation.hpp"

std::vector<GLdouble> new_position(std::vector<GLdouble> obj, int n, GLdouble t_energy);
std::vector<GLdouble> getMatrix(std::vector<GLdouble> obj, int cur);
void setLeader(std::vector<GLdouble> leader);
