//
//  header.hpp
//  Lab2
//
//  Created by Jia Yuan Teoh on 10/10/20.
//

#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include <fstream>

#include "rotation.hpp"
#include "geometric.hpp"
#include "matrix_helper.hpp"
#include "forward_kinematic.hpp"
#include "interpolation.hpp"

// screen size
int g_screenWidth = 0;
int g_screenHeight = 0;

// frame index
int g_frameIndex = 0;

// input control points
std::vector<GLdouble> inputTorso;
std::vector<GLdouble> inputLeftUpperLeg;
std::vector<GLdouble> inputRightUpperLeg;
std::vector<GLdouble> inputLeftLowerLeg;
std::vector<GLdouble> inputRightLowerLeg;

// frames with interpolation control points
std::vector<GLdouble> framesTorso;
std::vector<GLdouble> framesLeftUpperLeg;
std::vector<GLdouble> framesRightUpperLeg;
std::vector<GLdouble> framesLeftLowerLeg;
std::vector<GLdouble> framesRightLowerLeg;

int interpolation_type = 0;     // 0 for unknown, 1 for catmul-rom, 2 for b-spline
GLdouble spacing = 0;           // interpolation spacing (dt)
int data = 0;                   // number of sets of control points

int TORSODATA = 6;              // number of control points for torso (fixed-angles)
int PARTSDATA = 9;              // number of control points for other parts (hierarchy transformation)

// index for frames; keep track of which values to load
int torsoCount = 0;             // will increment by 6 each frame
int partsCount = 0;             // will increment by 9 each frame; shared with all parts
