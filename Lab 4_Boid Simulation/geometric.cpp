//
//  geometric.cpp
//  Lab4
//
//  Created by Jia Yuan Teoh on 11/26/20.
//

#include "geometric.hpp"

// object
double* vertexData0;
std::vector<int> faceList0;
int faceCount0 = 0;

// load geometrics
void geometric0(){
    int i,j;
    j = 0;
    for(i = 0; i < faceCount0; i++){
        glBegin(GL_POLYGON);
        while ( faceList0[j] != -1){
            int vertexNum = faceList0[j]-1;
            glNormal3dv(&vertexData0[vertexNum*3]);
            glVertex3dv(&vertexData0[vertexNum*3]);
            j++;
        }
        j++;
        glEnd();
    }
}

// read geometric data into their own vertexData and faceList
// this function will also get the maximum radius of object from 0,0,0 for bounding sphere
void readObjectData(std::string file, double* &vertexData, std::vector<int> &faceList, int &faceCount, GLdouble &rad){
    int vertexCount = 0;
    std::ifstream inFile;
    inFile.open(file);
    GLdouble temp;

    if (inFile.is_open()){
        std::string data;
        inFile >> data >>vertexCount >> faceCount;
        vertexData = new double[vertexCount*3];
        int count = 0;
        for(int i = 0; i < vertexCount; i++){
            inFile >> vertexData[count] >> vertexData[count+1] >> vertexData[count+2];
            temp = sqrt( (vertexData[count]*vertexData[count]) + (vertexData[count+1]* vertexData[count+1]) + (vertexData[count+2]*vertexData[count+2])); // calculate radius
            rad = temp > rad ? temp : rad; // replace if its larger
            count += 3;
        }
        
        int num_vertice = 0;
        int d;
        for(int i = 0; i < faceCount; i++){
            inFile >> num_vertice;
            while(num_vertice != 0){
                inFile >> d;
                faceList.push_back(d);
                num_vertice--;
            }
            faceList.push_back(-1);
        }
        
        inFile.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
    
}

// called from the main method and pass in geometric data file (for 1 geometric object)
void loadGeometricData(std::string geometric0, GLdouble &rad0){
    readObjectData(geometric0, vertexData0, faceList0, faceCount0, rad0);
}
