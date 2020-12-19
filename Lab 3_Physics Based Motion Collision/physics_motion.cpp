//
//  physics_motion.cpp
//  Lab 3
//
//  Created by Jia Yuan Teoh on 10/29/20.
//

#include "physics_motion.hpp"

const float g = -9.8; // gravitational force

// generates random number between 0.3 to 0.7
GLdouble randomNumber(){
    GLdouble smallnum = 0.3;
    GLdouble bignum = 0.7;
    GLdouble diff = bignum-smallnum;
    return (((GLdouble) rand() / RAND_MAX) * diff) + smallnum;
}

// checking for object's collision and distribute the velocity randomly across 2 objects
std::vector<GLdouble> checkObjCollision(std::vector<GLdouble> obj, int n){
    int cur, compare;
    GLdouble dist, x_dist, y_dist, z_dist;
    GLdouble big, small;
    GLdouble total, r_total;
    GLdouble ratio, r_ratio;
    
    for (int j = 0; j < n; j++){
        cur = j*14;
        for (int i = j+1; i < n; i++){
            compare = i*14;
            if (cur == compare) continue;
            
            dist = obj[cur+13] + obj[compare+13];
            x_dist = std::abs(obj[cur+0] - obj[compare+0]);
            y_dist = std::abs(obj[cur+1] - obj[compare+1]);
            z_dist = std::abs(obj[cur+2] - obj[compare+2]);
            
            // collision happened
            if(x_dist <= dist && y_dist <= dist && z_dist <= dist){
                std::cout << "collide! " << std::endl;
                
                // get a total velocity and return it back to the 2 objects in a random ratio
                // check x
                big = obj[cur+0] > obj[compare+0] ? cur : compare;  // determine if the position is at the negative (small) or positive (big) side
                small = big == cur ? compare : cur;
                total = std::abs(obj[big+6]) + std::abs(obj[small+6]);
                ratio = total * randomNumber();             // get random ratio
                obj[big+6] = ratio;                         // update velocity
                obj[small+6] = -(total-ratio);              // update velocity
                obj[big+0] += obj[big+6]*obj[big+12];       // update position
                obj[small+0] += obj[small+6]*obj[small+12]; // update position
                
                // x rotation
                r_total = std::abs(obj[big+9]) + std::abs(obj[small+9]);
                r_ratio = r_total * randomNumber();
                obj[big+9] = r_ratio;
                obj[small+9] = -(r_total-r_ratio);
                obj[big+3] += obj[big+9]*obj[big+12];
                obj[small+3] += obj[small+9]*obj[small+12];
                
                // check y
                big = obj[cur+1] > obj[compare+1] ? cur : compare;
                small = big == cur ? compare : cur;
                total = std::abs(obj[big+7]) + std::abs(obj[small+7]);
                ratio = total * randomNumber();
                obj[big+7] = ratio;
                obj[small+7] = -(total-ratio);
                obj[big+1] += obj[big+7]*obj[big+12];
                obj[small+1] += obj[small+7]*obj[small+12];
                
                // y rotation
                r_total = std::abs(obj[big+10]) + std::abs(obj[small+10]);
                r_ratio = r_total * randomNumber();
                obj[big+10] = r_ratio;
                obj[small+10] = -(r_total-r_ratio);
                obj[big+4] += obj[big+10]*obj[big+12];
                obj[small+4] += obj[small+10]*obj[small+12];

                // check z
                big = obj[cur+2] > obj[compare+2] ? cur : compare;
                small = big == cur ? compare : cur;
                total = std::abs(obj[big+8]) + std::abs(obj[small+8]);
                ratio = total * randomNumber();
                obj[big+8] = ratio;
                obj[small+8] = -(total-ratio);
                obj[big+2] += obj[big+8]*obj[big+12];
                obj[small+2] += obj[small+8]*obj[small+12];
                
                // z rotation
                r_total = std::abs(obj[big+11]) + std::abs(obj[small+11]);
                r_ratio = r_total * randomNumber();
                obj[big+11] = r_ratio;
                obj[small+11] = -(r_total-r_ratio);
                obj[big+5] += obj[big+11]*obj[big+12];
                obj[small+5] += obj[small+11]*obj[small+12];
            }

        }
    }
    
    return obj;
}

// updaate state vector
std::vector<GLdouble> physics_motion(std::vector<GLdouble> obj, int n){
    // x, y, z, rx, ry, rz, vx, vy, vz, vrx, vry, vrz, dt, radius
    // 0, 1, 2,  3,  4,  5,  6,  7,  8,   9,  10,  11, 12,     13
    
    for (int i = 0; i < n; i++){
        int cur = i*14;
        
        // calculate
        obj[cur+7] += g*obj[cur+12];
        obj[cur+0] += obj[cur+6]*obj[cur+12];
        obj[cur+1] += obj[cur+7]*obj[cur+12];
        obj[cur+2] += obj[cur+8]*obj[cur+12];
        
        obj[cur+3] += obj[cur+9]*obj[cur+12];
        obj[cur+4] += obj[cur+10]*obj[cur+12];
        obj[cur+5] += obj[cur+11]*obj[cur+12];
        
        // if collide with walls of the box, reflect the velocity
        if (obj[cur+0] - obj[cur+13] < -2.5 || obj[cur+0] + obj[cur+13] > 2.5){     // x axis walls
            obj[cur+6] = -obj[cur+6];
            obj[cur+0] += obj[cur+6]*obj[cur+12];
            obj[cur+9] = -obj[cur+9];
            obj[cur+3] += obj[cur+9]*obj[cur+12];
        }
        if (obj[cur+1] - obj[cur+13] < 0 || obj[cur+1] + obj[cur+13] > 4.0) {   // y axis walls
            obj[cur+7] = -obj[cur+7];
            obj[cur+1] += obj[cur+7]*obj[cur+12];
            obj[cur+10] = -obj[cur+10];
            obj[cur+4] += obj[cur+10]*obj[cur+12];
        }
        if(obj[cur+2] - obj[cur+13] < -2.5 || obj[cur+2] + obj[cur+13] > 2.5){  // z axis walls
            obj[cur+8] = -obj[cur+8];
            obj[cur+2] += obj[cur+8]*obj[cur+12];
            obj[cur+11] = -obj[cur+11];
            obj[cur+5] += obj[cur+11]*obj[cur+12];
        }
    }
    
    // check for collision and handle it
    obj = checkObjCollision(obj, n);
    return obj;
}

std::vector<GLdouble> getMatrix(std::vector<GLdouble> obj, int cur){
    return fixedAngle(obj[cur+0], obj[cur+1], obj[cur+2], obj[cur+3], obj[cur+4], obj[cur+5]);
}
