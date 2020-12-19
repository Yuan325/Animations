//
//  main.cpp
//  Lab4
//
//  Created by Jia Yuan Teoh on 11/11/20.
//

//
//  main.cpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/27/20.
//

#include <GLUT/glut.h>
#include <vector>
#include <fstream>
#include "matrix_helper.hpp"
#include "behavior.hpp"
#include "geometric.hpp"


// frame index
int g_frameIndex = 0;

int n = 0;              // number of object
GLdouble t_energy;      // total energy of all boids
GLdouble rad0;          // radius of geometric object

std::vector<GLdouble> load_mat; // used to load object matrix
std::vector<GLdouble> obj;      // information of all objects

// ===================================
//              Update
// ===================================
void update( void ){
    // get new position of all boids
    obj = new_position(obj,  n, t_energy);
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
    gluLookAt(0, 0, 6.6,
              0, 0, 0,
              0, 1, 0);
    
    // load boids
    int cur;
    for(int i = 0; i < n; i++){
        cur = i*9;
        glPushMatrix();
        load_mat = getMatrix(obj, cur);
        glMultMatrixd(convertToDoubleAndTranspose(load_mat));
        geometric0();
        glPopMatrix();
    }
    
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
    // 40 ms per frame
    glutTimerFunc(40, timer, 0);
}

// ===================================
//           Read Data File
// ===================================
// read initial conditions from .txt file
void readDataFile(std::string file){
    std::ifstream inFile;
    std::string line;
    inFile.open(file);

    if (inFile.is_open()){
        inFile >> n;            // get number of objects
        
        GLdouble a;
        for(int i = 0; i < n; i ++){
            for (int j = 0; j < 9; j++){
                inFile >> a;
                if (j == 8) obj.push_back(rad0);
                else obj.push_back(a);       // get initial conditions of all objects
                if (j == 7) t_energy += a;
            }
        }

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
    // x, y, z, vx, vy, vz, dt, energy, radius
    // 0, 1, 2,  3,  4,  5,  6,      7,      8
    
    n = 22;
    loadGeometricData("./cube.d.txt", rad0);
    readDataFile("./data.txt");

    // openGL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 4");
    
    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutTimerFunc( 40, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}
