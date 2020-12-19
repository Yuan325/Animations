//
//  main.cpp
//  Lab2
//
//  Created by Jia Yuan Teoh on 10/7/20.
//
#include "header.hpp"

// ===================================
//              Update
// ===================================
// update frame to render the new set of data
void update( void ){
    int last_frame = (data-3)*TORSODATA*(1/spacing); // determine the value of last_frame
    if(torsoCount == last_frame){
        torsoCount = 0;
        partsCount = 0;
    }
    else{
        torsoCount = torsoCount + TORSODATA;
        partsCount = partsCount + PARTSDATA;
    }
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
    gluLookAt(0, 0, 15,
              0, 0, 0,
              0, 1, 0);
    
    // vectors for parts matrix
    std::vector<GLdouble> torso_matrix, parts_matrix;
    std::vector<GLdouble> rul_matrix, lul_matrix, rll_matrix, lll_matrix;
    
    // construct matrix and load parts
    glPushMatrix();
    torso_matrix = fixedAngle(framesTorso[torsoCount], framesTorso[torsoCount+1], framesTorso[torsoCount+2], framesTorso[torsoCount+3], framesTorso[torsoCount+4], framesTorso[torsoCount+5]);
    glMultMatrixd(convertToDoubleAndTranspose(torso_matrix));
    torso();
    glPopMatrix();
    
    glPushMatrix();
    parts_matrix = heirarchyTransformation(framesRightUpperLeg[partsCount], framesRightUpperLeg[partsCount+1], framesRightUpperLeg[partsCount+2], framesRightUpperLeg[partsCount+3], framesRightUpperLeg[partsCount+4], framesRightUpperLeg[partsCount+5], framesRightUpperLeg[partsCount+6], framesRightUpperLeg[partsCount+7], framesRightUpperLeg[partsCount+8]);
    rul_matrix = matrixMultiply(torso_matrix, parts_matrix);
    glMultMatrixd(convertToDoubleAndTranspose(rul_matrix));
    leg();
    glPopMatrix();
    
    glPushMatrix();
    parts_matrix = heirarchyTransformation(framesRightLowerLeg[partsCount], framesRightLowerLeg[partsCount+1], framesRightLowerLeg[partsCount+2], framesRightLowerLeg[partsCount+3], framesRightLowerLeg[partsCount+4], framesRightLowerLeg[partsCount+5], framesRightLowerLeg[partsCount+6], framesRightLowerLeg[partsCount+7], framesRightLowerLeg[partsCount+8]);
    rll_matrix = matrixMultiply(rul_matrix, parts_matrix);
    glMultMatrixd(convertToDoubleAndTranspose(rll_matrix));
    leg();
    glPopMatrix();
    
    glPushMatrix();
    parts_matrix = heirarchyTransformation(framesLeftUpperLeg[partsCount], framesLeftUpperLeg[partsCount+1], framesLeftUpperLeg[partsCount+2], framesLeftUpperLeg[partsCount+3], framesLeftUpperLeg[partsCount+4], framesLeftUpperLeg[partsCount+5], framesLeftUpperLeg[partsCount+6], framesLeftUpperLeg[partsCount+7], framesLeftUpperLeg[partsCount+8]);
    lul_matrix = matrixMultiply(torso_matrix, parts_matrix);
    glMultMatrixd(convertToDoubleAndTranspose(lul_matrix));
    leg();
    glPopMatrix();
    
    glPushMatrix();
    parts_matrix = heirarchyTransformation(framesLeftLowerLeg[partsCount], framesLeftLowerLeg[partsCount+1], framesLeftLowerLeg[partsCount+2], framesLeftLowerLeg[partsCount+3], framesLeftLowerLeg[partsCount+4], framesLeftLowerLeg[partsCount+5], framesLeftLowerLeg[partsCount+6], framesLeftLowerLeg[partsCount+7], framesLeftLowerLeg[partsCount+8]);
    lll_matrix = matrixMultiply(lul_matrix, parts_matrix);
    glMultMatrixd(convertToDoubleAndTranspose(lll_matrix));
    leg();
    glPopMatrix();
    
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
    // 32 ms per frame (about 30 frames per second)
    glutTimerFunc(32, timer, 0);
}

// ===================================
//           Read Data File
// ===================================
// read control point inputs from .txt file
void readDataFile(std::string file){
    std::ifstream inFile;
    std::string line;
    inFile.open(file);
    
    if (inFile.is_open()){
        inFile >> data; // read number of sets of control points
        GLdouble a;
        for(int i = 0; i < data*6; i ++){
            inFile >> a;
            inputTorso.push_back(a); // read torso input data
        }

        for(int i = 0; i < data*9; i++){
            inFile >> a;
            inputRightUpperLeg.push_back(a); // read right upper leg input data
        }
        
        for(int i = 0; i < data*9; i++){
            inFile >> a;
            inputRightLowerLeg.push_back(a); // read right lower leg input data
        }

        for(int i = 0; i < data*9; i++){
            inFile >> a;
            inputLeftUpperLeg.push_back(a); // read left upper leg input data
        }
        
        for(int i = 0; i < data*9; i++){
            inFile >> a;
            inputLeftLowerLeg.push_back(a); // read left lower leg input data
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
    // input variables
    spacing = 0.05;             // interpolation spacing (dt)
    interpolation_type = 2;     // 0 for unknown, 1 for catmull-rom, 2 for b-splines
    
    loadGeometricData("../torso.d.txt", "../leg.d.txt");    // load geometric data for torso and legs
    readDataFile("backflip.txt");                           // load control points
    
    // interpolation for each parts
    framesTorso = interpolation(spacing, interpolation_type, TORSODATA, data, inputTorso);
    framesRightUpperLeg = interpolation(spacing, interpolation_type, PARTSDATA, data, inputRightUpperLeg);
    framesRightLowerLeg = interpolation(spacing, interpolation_type, PARTSDATA, data, inputRightLowerLeg);
    framesLeftUpperLeg = interpolation(spacing, interpolation_type, PARTSDATA, data, inputLeftUpperLeg);
    framesLeftLowerLeg = interpolation(spacing, interpolation_type, PARTSDATA, data, inputLeftLowerLeg);

    // openGL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 2: b spline");
    
    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutTimerFunc( 32, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}
