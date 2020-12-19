//
//  Lab1
//
//  Created by Jia Yuan Teoh on 9/12/20.
//  Copyright © 2020 Jia Yuan Teoh. All rights reserved.
//

// ===================================
//              Note
// ===================================
// 2D data is being stored as 1D vector for faster speed and better memory locality
// Sample data for fixed angle and quaternion provided at the bototm of main.cpp

#include "rotation.h"
#include "interpolation.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <GLUT/GLUT.h>
#include <vector>

// ===================================
//          global variables
// ===================================
int orientation = 0;            // 0 for unknown, 1 for Fixed angles, 2 for Quaternions
int interpolation_type = 0;     // 0 for unknown, 1 for catmull-rom, 2 for b-splines
std::vector<GLdouble> input ;   // input data values
std::vector<GLdouble> frames;   // all data after interpolation
int count = 0;                  // keep track of which value to load for rotation and allowing animation to repeat
int data = 0;                   // number of sets of input data
int n = 0;                      // 0 for unknown, 6 for Fixed angles, 7 for Quaternions
GLdouble spacing = 0;           // dt value

// screen size
int g_screenWidth = 0;
int g_screenHeight = 0;

// frame index
int g_frameIndex = 0;

// ===================================
//              Update
// ===================================
// update frame to render the new set of data
void update( void ){
    int last_frame = (data-3)*n*(1/spacing); // determine the value of last_frame
    if(count == last_frame)
        count = 0;
    else
        count = count + n;
}

// ===================================
//              Render
// ===================================
void render( void ){
    // clear buffer
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth (1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render state
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // light source attributes
    GLfloat LightAmbient[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightDiffuse[]    = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat LightSpecular[]    = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    // surface material attributes
    GLfloat material_Ka[]    = { 0.11f, 0.06f, 0.11f, 1.0f };
    GLfloat material_Kd[]    = { 0.43f, 0.47f, 0.54f, 1.0f };
    GLfloat material_Ks[]    = { 0.33f, 0.33f, 0.52f, 1.0f };
    GLfloat material_Ke[]    = { 0.1f , 0.0f , 0.1f , 1.0f };
    GLfloat material_Se      = 10;

    glMaterialfv(GL_FRONT, GL_AMBIENT    , material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE    , material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR    , material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION    , material_Ke);
    glMaterialf (GL_FRONT, GL_SHININESS    , material_Se);

    // render object
    GLdouble* matrix_orientation;
    
    if (orientation == 1){
        matrix_orientation = fixedAngle(frames[count], frames[count+1], frames[count+2], frames[count+3], frames[count+4], frames[count+5]);
    }
    else if (orientation == 2){
        matrix_orientation = quaternion(frames[count], frames[count+1], frames[count+2], frames[count+3], frames[count+4], frames[count+5], frames[count+6]);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixd(matrix_orientation);

    // solid teapot
    glutSolidTeapot(0.2);
    
    // swap back and front buffers
    glutSwapBuffers();
}

// ===================================
//              Reshape
// ===================================
void reshape( int w, int h ){
    // screen size
    g_screenWidth = w;
    g_screenHeight = h;
    
    // viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h );
    
    // projection matrix
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 10.0);
}

// ===================================
//              Timer
// ===================================
void timer ( int value ){
    // increase frame index
    g_frameIndex++;
    
    update();
    
    // render
    glutPostRedisplay();
    
    // reset timer
    // 32 ms per frame (about 30 frames per second)
    glutTimerFunc(32, timer, 0);
}

// ===================================
//              Read File
// ===================================
// read input from .txt file
int readFile(){
    std::ifstream inFile;
    std::string line;
    inFile.open("inputData.txt");
    int numbers = 0;
    
    if (inFile.is_open()){
        GLdouble a;
        while(inFile >> a){
            input.insert(input.end(), a);
            numbers++;
        }
        inFile.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    return numbers;
}

// ===================================
//              Main
// ===================================
int main(int argc, char ** argv) {
    // input variables
    spacing = 0.05;              // interpolation spacing (dt)
    interpolation_type = 2;     // 0 for unknown, 1 for catmull-rom, 2 for b splines
    orientation = 1;            // 0 for unknown, 1 for FixedAngle, 2 for Quaternions
    
    if (orientation == 1) n = 6;
    else if (orientation == 2) n = 7;
    
    int numbers = readFile();
    data = numbers/n; // number of dataset provided
    
    frames = interpolation(spacing, interpolation_type, n, data, input);
    
    // openGL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 1");
    
    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutTimerFunc( 32, timer, 0);
    
    // main loop
    glutMainLoop();
    
    return 0;
}

/*
 == SAMPLE DATA FOR FIXED ANGLE ==
 0 0 0 0 0 0
 -1 0.5 0.5 0 0 0
 -0.5 0 0 1 2 0
 0 -0.5 -0.5 2 3 0
 0.5 0 0 3 2 0
 0.75 0.5 0 3 1 0
 0.5 0 -0.5 2 2 1
 0 -0.5 -1 2 3 2
 0 -0.75 -0.5 1 4 3
 -0.5 -0.5 0 0 3 2
 -0.25 0 0.5 0 2 1
 0 0.5 0.75 0 1 0
 0 0 0.5 1 0 1
 0 0 0 0 0 0
 0 0 0 0 0 0
 
 == SAMPLE DATA FOR QUATERNIONS ==
0 0 0 0 0 0 0
-1 0.5 0.5 0 0 0 0
-0.5 0 0 1 5 0 0
0 -0.5 -0.5 2 9 0 0
0.5 0 0 3 5 0 1
0.75 0.5 0 3 2 0 2
0.5 0 -0.5 2 2 1 1
0 -0.5 -1 2 3 8 2
0 -0.75 -0.5 1 4 5 4
-0.5 -0.5 0 0 3 7 5
-0.25 0 0.5 0 2 7 3
0 0.5 0.75 0 1 0 2
0 0 0.5 1 0 1 1
0 0 0 0 0 0 0
*/
