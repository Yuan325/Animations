//
//  behavior.cpp
//  Lab4
//
//  Created by Jia Yuan Teoh on 11/20/20.
//

// x, y, z, vx, vy, vz, dt, energy, radius
// 0, 1, 2,  3,  4,  5,  6,      7,      8

#include "behavior.hpp"

std::vector<GLdouble> datas;
GLdouble max_velocity = 3.0;

// calculate and return distance between 2 boids
GLdouble dist(GLdouble first, GLdouble sec, int e){
    return datas[first+e] - datas[sec+e];
}

std::vector<GLdouble> collision_avoidance(int n, int cur){
    int ind, j = cur/9, count=0;
    GLdouble desire_dist=0, dist_x=0, dist_y=0, dist_z=0;
    std::vector<GLdouble> ca(3,0);
    
    for (int i = 0 ; i < n; i++){
        if (i != j){
            ind = i*9;

            desire_dist = datas[cur+8] + datas[ind+8] + datas[cur+8];
            dist_x = dist(cur, ind, 0);
            dist_y = dist(cur, ind, 1);
            dist_z = dist(cur, ind, 2);

            // add distance of all surrounding boids that are "too close"
            if ( abs(dist_x) < desire_dist && abs(dist_y) < desire_dist && abs(dist_z) < desire_dist ){
                ca[0] += dist_x ;
                ca[1] += dist_y ;
                ca[2] += dist_z ;
                count++;
            }
        }
    }
    
    if (count > 0){
        // calculate average
        ca[0] = ca[0] / count;
        ca[1] = ca[1] / count;
        ca[2] = ca[2] / count;
        
        // if the distance is not 0, calculate difference between current position and desired distance
        // add it to the current boid
        if (ca[0] != 0){
            GLdouble tempx = desire_dist - abs(ca[0]);
            if ( ca[0] <0 ) ca[0] = -tempx; else { ca[0] = tempx; } // for negative distance
        }
        if (ca[1] != 0){
            GLdouble tempy = desire_dist - abs(ca[1]);
            if ( ca[1] <0 ) ca[1] = -tempy; else { ca[1] = tempy; }
        }
        if (ca[2] != 0){
            GLdouble tempz = desire_dist - abs(ca[2]);
            if ( ca[2] <0 ) ca[2] = -tempz; else { ca[2] = tempz; }
        }
    }
    return ca;
}

std::vector<GLdouble> flock_centering( int n, int cur){
    int ind, j = cur / 9, count=0;
    GLdouble desire_dist=0, dist_x=0, dist_y=0, dist_z=0;
    std::vector<GLdouble>  fc(3,0);
    
    for (int i = 0; i < n; i++){
        if(i != j){
            ind = i * 9;
            
            desire_dist = datas[cur+8] + datas[ind+8] + 1; // RADIUS
            dist_x = dist(ind, cur, 0);
            dist_y = dist(ind, cur, 1);
            dist_z = dist(ind, cur, 2);
            
            // add distance of all boids within a distance
            if ( abs(dist_x) < desire_dist && abs(dist_y) < desire_dist && abs(dist_z) < desire_dist ){
                fc[0] += dist_x;
                fc[1] += dist_y;
                fc[2] += dist_z;
                count++;
            }
        }
    }
    
    if (count > 0){
        // get average distance from desired "center" position
        fc[0] = fc[0] / count;
        fc[1] = fc[1] / count;
        fc[2] = fc[2] / count;

        // move the boid towards the desired center distance by 1/80
        fc[0] = (fc[0] - datas[cur + 0]) / 80;
        fc[1] = (fc[1] - datas[cur + 1]) / 80;
        fc[2] = (fc[2] - datas[cur + 2]) / 80;
    }
    return fc;
}

std::vector<GLdouble> velocity_match( int n, int cur, GLdouble total_energy){
    int ind, j = cur/9;
    GLdouble desire_dist=0, dist_x=0, dist_y=0, dist_z=0;
    std::vector<GLdouble> vm(3,0);
    
    for(int i = 0; i < n; i++){
        if (i != j){
            ind = i*9;
            desire_dist = datas[cur+8] + datas[ind+8] + 1; // RADIUS
            dist_x = dist(cur, ind, 0);
            dist_y = dist(cur, ind, 1);
            dist_z = dist(cur, ind, 2);
            
            // if boids are within a distance, add their velocity based on each boid's energy
            // boid with higher energy will affect velocity of neighboring boids more
            if ( abs(dist_x) < desire_dist && abs(dist_y) < desire_dist && abs(dist_z) < desire_dist ){
                // only add velocity of boids coming towards the current boid
                if ( (dist_x < 0 && datas[ind+3] < 0) || (dist_x >= 0 && datas[ind+3] >= 0) )
                    vm[0] += (datas[ind + 3] / total_energy * datas[ind+7]);
                if ( (dist_y < 0 && datas[ind+4] < 0) || (dist_y >= 0 && datas[ind+4] >= 0) )
                    vm[1] += (datas[ind + 4] / total_energy * datas[ind+7]);
                if ( (dist_z < 0 && datas[ind+5] < 0) || (dist_z >= 0 && datas[ind+5] >= 0) )
                    vm[2] += (datas[ind + 5] / total_energy * datas[ind+7]);
            }
        }
    }
    return vm;
}

// check if boids are at the end of window, move it to the other end
void checkPosition(int n, int cur){
    if (abs(datas[cur + 0]) >= 3.8) {
        if (datas[cur + 0] > 0) datas[cur + 0] = -3.8;
        else datas[cur + 0] = 3.8;
    }
    if (abs(datas[cur + 1]) >= 3.8){
        if (datas[cur + 1] > 0) datas[cur + 1] = -3.8;
        else datas[cur + 1] = 3.8;
    }
    
    if (abs(datas[cur + 2]) >= 3.0) {
        if (datas[cur + 2] > 0) datas[cur + 2] = -3.0;
        else  datas[cur + 2] = 3.0;
    }
}

std::vector<GLdouble> new_position(std::vector<GLdouble> obj, int n, GLdouble t_energy){
    std::vector<GLdouble> fc(3,0);
    std::vector<GLdouble> ca(3,0);
    std::vector<GLdouble> vm(3,0);
    
    datas = obj;
    
    for (int i = 0; i < n; i++){
        int cur = i*9;
        
        // calculate the 3 behaviors
        ca = collision_avoidance( n, cur);
        fc = flock_centering( n, cur);
        vm = velocity_match( n, cur, t_energy);
    
        
        // if true, means no value was changed
        GLboolean fir = ca[0] == 0 && ca[1] == 0 && ca[2] == 0;
        GLboolean sec = vm[0] == 0 && vm[1] == 0 && vm[2] == 0;

        // only pick maximum of 2 behaviors to add towards the boid
        // pick either collision avoidance of flock centering
        if (fir != true){
            // collision is the priority behavior
            datas[cur+3] += ca[0]; datas[cur+4] += ca[1]; datas[cur+5] += ca[2];
        }
        else{
            datas[cur+0] += fc[0]; datas[cur+1] += fc[1]; datas[cur+2] += fc[2];
        }
        
        // if there are changes in velocity matching, add that
        if (sec != true){
            datas[cur+3] += vm[0]; datas[cur+4] += vm[1]; datas[cur+5] += vm[2];
        }

        // stop boid from moving faster than max velocity
        if (datas[cur + 3] > max_velocity) datas[cur + 3] = max_velocity;
        if (datas[cur + 4] > max_velocity) datas[cur + 4] = max_velocity;
        if (datas[cur + 5] > max_velocity) datas[cur + 5] = max_velocity;
        
        // calculate position (x, y, z) based on velocity
        datas[cur+0] += datas[cur+3]*datas[cur+6];
        datas[cur+1] += datas[cur+4]*datas[cur+6];
        datas[cur+2] += datas[cur+5]*datas[cur+6];

        // make sure boid that reach the end of window will move to other end of window
        checkPosition(n, cur);
    }
    return datas;
}

// send matrix over to fixedAngle to generate boid
std::vector<GLdouble> getMatrix(std::vector<GLdouble> obj, int cur){
    return fixedAngle(obj[cur+0], obj[cur+1], obj[cur+2], 0, 0, 0);
}
