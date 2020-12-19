//
//  main.cpp
//  Lab 5
//
//  Created by Jia Yuan Teoh on 12/14/20.
//

#include <GLUT/glut.h>
#include <fstream>
#include <string>

#include "lsystem.hpp"

// frame index
int g_frameIndex = 0;

// L-system variables
int depth_input;
GLdouble angle_input;
std::string axiom_input;
std::string A_input;
std::string B_input;


// ===================================
//              Update
// ===================================
void update( void ){
    replace();
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
    GLfloat LightDiffuse[]    = { 0.3f, 0.3f, 0.5f, 1.0f };
    GLfloat LightSpecular[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat LightPosition[] = { 2.0f, 1.0f, 2.0f, 0.5f };

    glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    // surface material attributes
    GLfloat material_Ka[]    = { 0.1f, 0.18725f, 0.1745f, 1.0f };
    GLfloat material_Kd[]    = { 0.396f, 0.74151f, 0.69102f, 1.0f };
    GLfloat material_Ks[]    = { 0.297254f, 0.30829f, 0.306678f, 1.0f };
    GLfloat material_Ke[]    = { 0.1f , 0.0f , 0.1f , 1.0f };
    GLfloat material_Se      = 10;

    glMaterialfv(GL_FRONT, GL_AMBIENT    , material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE    , material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR    , material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION    , material_Ke);
    glMaterialf (GL_FRONT, GL_SHININESS    , material_Se);
    
    // camera position
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(2, 2, 6.6,
              0, 0, 0,
              0, 1, 0);
    
    
    glPushMatrix();
    draw();
    glPopMatrix();
    
    // disable lighting
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    // swap back and front buffers
    glutSwapBuffers();
}

// ===================================
//              Reshape
// ===================================
void reshape( int w, int h ){

    // viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h );
    
    // projection matrix
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
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
    // 1000 ms per frame
    glutTimerFunc(500, timer, 0);
}

// ===================================
//            Read Data
// ===================================
void readDataFile(std::string file){
    std::ifstream inFile;
    std::string line;
    inFile.open(file);
    
    if (inFile.is_open()){
        inFile >> depth_input;
        inFile >> angle_input;
        inFile >> axiom_input;
        inFile >> A_input;
        inFile >> B_input;
        inFile.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
}

// ===================================
//              Main
// ===================================
int main(int argc, char ** argv) {
    readDataFile("./data2.txt");
    
    lsystem(depth_input, angle_input, A_input, B_input, axiom_input);
    // openGL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 5");
    
    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutTimerFunc( 500, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}
    
