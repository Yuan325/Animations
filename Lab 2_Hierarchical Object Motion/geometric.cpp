//
//  skeleton.cpp
//  Lab2
//
//  Created by Jia Yuan Teoh on 10/7/20.
//
#include "geometric.hpp"

// object
double* torsoVertexData;
std::vector<int> torsoFaceList;
int torsoFaceCount = 0;

double* legVertexData;
std::vector<int> legFaceList;
int legFaceCount = 0;


// drawing torso
void torso(){
    int i,j;
    j = 0;
    for(i = 0; i < torsoFaceCount; i++){
        glBegin(GL_POLYGON);
        while ( torsoFaceList[j] != -1){
            int vertexNum = torsoFaceList[j]-1;
            glNormal3dv(&torsoVertexData[vertexNum*3]);
            glVertex3dv(&torsoVertexData[vertexNum*3]);
            j++;
        }
        j++;
        glEnd();
    }
}

// drawing leg
void leg(){
    int i,j;
    j = 0;
    for(i = 0; i < legFaceCount; i++){
        glBegin(GL_POLYGON);
        while ( legFaceList[j] != -1){
            int vertexNum = legFaceList[j]-1;
            glNormal3dv(&legVertexData[vertexNum*3]);
            glVertex3dv(&legVertexData[vertexNum*3]);
            j++;
        }
        j++;
        glEnd();
    }
}

// read geometric data for object into their own vertexData and faceList
int readObjectData(std::string file, double* &vertexData, std::vector<int> &faceList){
    int vertexCount = 0, faceCount = 0;
    std::ifstream inFile;
    inFile.open(file);

    if (inFile.is_open()){
        std::string data;
        inFile >> data >>vertexCount >> faceCount;
        vertexData = new double[vertexCount*3];
        int count = 0;
        for(int i = 0; i < vertexCount; i++){
            inFile >> vertexData[count++] >> vertexData[count++] >> vertexData[count++];
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
    
    return faceCount;
}

// called from the main method and pass in torso and leg geometric data file
void loadGeometricData(std::string torsofile, std::string legfile){
    torsoFaceCount = readObjectData(torsofile, torsoVertexData, torsoFaceList);
    legFaceCount = readObjectData(legfile, legVertexData, legFaceList);
}
