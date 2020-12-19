//
//  geometric.hpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/30/20.
//

#include <GLUT/glut.h>
#include <vector>
#include <fstream>
#include <iostream>

void geometric0();
void geometric1();
void geometric2();
void geometric3();

void loadGeometricData(std::string geometric1, std::string geometric2, std::string geometric3, GLdouble &rad1, GLdouble &rad2, GLdouble &rad3);
void loadGeometricData(std::string geometric0, GLdouble &rad0);
