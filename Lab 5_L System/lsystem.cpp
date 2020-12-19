//
//  lsystem.cpp
//  Lab 5
//
//  Created by Jia Yuan Teoh on 12/14/20.
//

#include "lsystem.hpp"

// variables
int cur;                        // current iteration
int depth;                      // numbers of iterations
GLdouble angle;                 // angle for l-system expansion
std::string system_s;           // current l-system
std::string ruleA;              // rule A
std::string ruleB;              // rule B

std::vector<GLdouble> load_mat; // use for matrix

void lsystem(int depth_input, GLdouble angle_input, std::string A_input, std::string B_input, std::string axiom_input){
    depth = depth_input;
    angle = angle_input;
    system_s = axiom_input;
    ruleA = A_input;
    ruleB = B_input;
}

// draw line
void drawLine(){
    glBegin(GL_LINES);
        glVertex3d(-0.1, 0, 0);
        glVertex3d(0.1, 0, 0);
    glEnd();
}

void base(){
    load_mat = fixedAngle(0, -3, 0, 1, 0, 0);
    glMultMatrixd(convertToDoubleAndTranspose(load_mat));
    glBegin(GL_LINES);
        glVertex3d(-0.3, 0, 0);
        glVertex3d(0.3, 0, 0);
    glEnd();
}

void straight_line(){
    load_mat = heirarchyTransformation(0.1, 0, 0, 0, 0, 0, 0.1, 0, 0);
    glMultMatrixd(convertToDoubleAndTranspose(load_mat));
    drawLine();
}

void left_turn(){
    load_mat = heirarchyTransformation(-0.1, 0, 0, angle, 0, 0, 0.1, 0, 0);
    glMultMatrixd(convertToDoubleAndTranspose(load_mat));
}

void right_turn(){
    load_mat = heirarchyTransformation(-0.1, 0, 0, -angle, 0, 0, 0.1, 0, 0);
    glMultMatrixd(convertToDoubleAndTranspose(load_mat));
}

void rotate(){
    load_mat = heirarchyTransformation(0, 0, 0, 0, 0, angle, 0, 0, 0);
    glMultMatrixd(convertToDoubleAndTranspose(load_mat));
}

// update every iteration, replacing alphabets by rules A and B
void replace(){
    cur++;
    if (cur >= depth) return;
    
    std::string temp = "";
    
    for (int i = 0; i < system_s.length(); i++){
        if (system_s.at(i) == 'A') temp += ruleA;
        else if (system_s.at(i) == 'B') temp += ruleB;
        else temp += system_s.at(i);
    }
    system_s = temp;
}

// draw current L-system
void draw(){
    base();
    for (int i=0; i < system_s.length(); i++){
        if (system_s.at(i) == '+') left_turn();
        else if(system_s.at(i) == '-') right_turn();
        else if(system_s.at(i) == 'F') straight_line();
        else if(system_s.at(i) == '[') glPushMatrix();
        else if(system_s.at(i) == ']') glPopMatrix();
        else if(system_s.at(i) == '>') rotate();
    }
}
