//
//  interpolation.cpp
//  Lab1
//
//  Created by Jia Yuan Teoh on 9/19/20.
//  Copyright © 2020 Jia Yuan Teoh. All rights reserved.
//

#include "interpolation.hpp"

std::vector<GLdouble> M;    // store basis matrix

// Prepare the basis matrix for either catmull-rom or b spline
void catmullromBasis(){
    GLdouble a = 0.5;
    M.insert(M.end(), {-a, 2-a, a-2, a, 2*a, a-3, 3-(2*a), -a, -a, 0, a, 0, 0, 1, 0, 0});
}

void bsplineBasis(){
    GLdouble a = 1.0/6;
    M.insert(M.end(),{-a, 3*a, -3*a, a, 3*a, -6*a, 3*a, 0, -3*a, 0, 3*a, 0, a, 4*a, a, 0});
}

// Calculate t matrix
std::vector<GLdouble> calculateTime(GLdouble t){
    std::vector<GLdouble> time_frame(4,0);
    time_frame[0] = t*t*t;
    time_frame[1] = t*t;
    time_frame[2] = t;
    time_frame[3] = 1;
    return time_frame;
}

std::vector<GLdouble> generate_interpolation(int n, int data, GLdouble spacing, std::vector<GLdouble> input){
    int count = 0, number_spacing = 1/spacing;
    std::vector<GLdouble> frames(((data-3)*number_spacing + 1)*n, 0) , tM(4, 0);
    
    for(int line = 0; line < data-3; line++){ // number of in-between "line" we have to generate
        for(int t = 0; t < number_spacing; t++){ // number of frame to generate for each "line"
            // tM = t x M
            std::vector<GLdouble> time_frame = calculateTime(spacing*t) ;
            for(int i = 0; i < 4; i++){
                tM[i] = 0;
                for(int j = 0; j < 4; j++){
                    tM[i] += time_frame[j] * M[4*j+i];
                }
            }
            
            //tM x 4 input data point
            for(int i = 0; i < n; i++){
                for(int j = 0; j < 4; j++){
                    frames[n*(count+t)+i] += tM[j] * input[(n*j)+i+(line*n)];
                }
            }
        }
        count = count + number_spacing; //keep track the number of frames in the 1D vector
    }
    
    // adding final keyframe into the frames as an ending orientation
    for(int i = 0; i<n; i++){
        frames[n*count+i] = input[(data-2)*n+i];
    }
    
    return frames;
}

std::vector<GLdouble> interpolation(GLdouble spacing, int interpolation, int n, int data, std::vector<GLdouble> input){
    if (interpolation == 1) catmullromBasis();
    else if (interpolation == 2) bsplineBasis();
    
    return generate_interpolation(n, data, spacing, input);
}
