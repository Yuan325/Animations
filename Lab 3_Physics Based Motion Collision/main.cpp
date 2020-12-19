//
//  main.cpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/27/20.
//

#include "header.hpp"

// ===================================
//              Update
// ===================================
void update( void ){
    // update the current orientation and velocity of objects
    obj = physics_motion(obj, n);
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
    gluLookAt(2.3, 4, 6.6,
              0, 0, 0,
              0, 1, 0);

    // draw floor grid
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
      glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
      glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
    }
    glEnd();
    
    
    int cur;
    if (object_type == 1){
        // draw all objects
        for(int i = 0; i < n; i++){
            cur = i*14;
            glPushMatrix();
            load_mat = getMatrix(obj, cur); // get the matrix
            glMultMatrixd(convertToDoubleAndTranspose(load_mat));
            geometric0();
            glPopMatrix();
        }
    }
    else{
        // draw 3 different objects
        glPushMatrix();
        cur = 0;
        load_mat = getMatrix(obj, cur);
        glMultMatrixd(convertToDoubleAndTranspose(load_mat));
        geometric1();
        glPopMatrix();
        
        glPushMatrix();
        cur = 14;
        load_mat = getMatrix(obj, cur);
        glMultMatrixd(convertToDoubleAndTranspose(load_mat));
        geometric2();
        glPopMatrix();
        
        glPushMatrix();
        cur = 28;
        load_mat = getMatrix(obj, cur);
        glMultMatrixd(convertToDoubleAndTranspose(load_mat));
        geometric3();
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
    // 32 ms per frame (about 30 frames per second)
    glutTimerFunc(32, timer, 0);
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
        inFile >> object_type;  // get object_type
        
        GLdouble a;
        for(int i = 0; i < n*14; i ++){
            inFile >> a;
            obj.push_back(a);       // get initial conditions of all objects
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
    readDataFile("./data2.txt");
    
    if (object_type == 1){
        loadGeometricData("./geometric/cube.d.txt", rad0);
        for (int i = 0; i < n; i++){
            obj[(i*14)+13] = rad0;      // set radius of the object
        }
    }
    else{
        loadGeometricData("./geometric/cube.d.txt", "./geometric/cube.d.txt", "./geometric/donut.d.txt", rad1, rad2, rad3);
        obj[13] = rad1;        // set radius for each of the different objects
        obj[27] = rad2;
        obj[41] = rad3;
    }

    // openGL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab 3 - 1 object");
    
    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutTimerFunc( 32, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}
