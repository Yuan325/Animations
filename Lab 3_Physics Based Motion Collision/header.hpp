//
//  header.h
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/27/20.
//

#include <GLUT/glut.h>
#include <vector>
#include "matrix_helper.hpp"
#include "physics_motion.hpp"
#include "geometric.hpp"

// frame index
int g_frameIndex = 0;

int object_type = 0;    // 1 as same object, 2 as different object
int n = 0;              // number of object

std::vector<GLdouble> load_mat; // used to load object matrix
std::vector<GLdouble> obj;      // information of all objects

// radius of objects
GLdouble rad0 = 0;      // for object_type = 1
GLdouble rad1 = 0;      // for object_type = 2
GLdouble rad2 = 0;      // for object_type = 2
GLdouble rad3 = 0;      // for object_type = 2
