#include <iostream>
#include "solution.h"
#include <cstdlib>
#include <cmath>
#include <cfloat>

using namespace std;

/* Constructor */
Solution::Solution(){
}

/**
 * Constructor
 *
 * @param n: number of points
 * @param data: table containing the points
 */
Solution::Solution(int n, float data[][2], int sp):startingPoint(sp) , N(n), distance(FLT_MAX) {
    
    /**
    *  We allocate memory to the different structures we have
    */

    /**
     * input is an array of points coordinates (x,y)  
     * path is an array of points indices
     * distances is a triangular matrix of distances between points
     */
    this->input = (float**) malloc(sizeof(float *)*N);
    this->path = (int*) malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++){
        this->input[i] = (float*) malloc(sizeof(float)*2);
        this->path[i] = -1;
        this->input[i][0] = data[i][0];
        this->input[i][1] = data[i][1];
    }
    this->distances = (float**) malloc(sizeof(float*)*N);
    for(int i = 0; i < N; i++)
        this->distances[i] = (float*)malloc(sizeof(float)*(i+1));
    /**
     * Computed distances are thoes marked with a dot
     * 
     *        0    1    2   ...   N-2  N-1
     *   0    .    x    x          x    x
     *   1    .    .    x          x    x 
     *   2    .    .    .    x          x
     *                       .     x
     *                             .    x
     *  N-1   .    .    .          .    .
     *
     * distance bitween 3 and 2   is distances[3][2]  
     * distance bitween 0 and 5   is distances[5][0]
     *
     */
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i+1; j++){
            this->distances[i][j] = dist(input[i], input[j]);
        }    
    } 
    
}   

/* Destroyer */
Solution::~Solution(){
    //for(int i=0; i<N; i++)
    //    free (input[i]);
    //free(input);
    //free(path);
}

void Solution::setVal(int i, int val){
    path[i] = val;    
}

void Solution::setPath(int *path){
    for(int i=0; i<N ; i++)
        this->path[i] = path[i];
}

void Solution::setK(int K){
    this->K = K;
    K_nearestNeighbours = (int**) malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++)
        K_nearestNeighbours[i] = (int*) malloc(sizeof(int)*K);
}

void Solution::setKNN(int i, int *KNN){
    for(int j=0; j<K; j++)
        this->K_nearestNeighbours[i][j] = KNN[j];
}

void Solution::setDistance(float distance){
    this->distance = distance;
}

void Solution::setStartingPoint(int sp){
    this->startingPoint = sp;
}


/**
 * Displays the resulting path and the distance of it
 */
void Solution::display(bool showDist) {
    if (showDist){
        distance = 0;
        for(int i=0; i<N; i++)
            distance += dist(input[path[i]], input[path[(i+1)% N]]);
        cout << "distance = " << this->distance << "; \n";
    } else {
        for (int i = 0; i < N; i++)
            cout << this->path[i] << "\n";
    }

}

/**
 * Computes the euclidean distance between two points
 *
 * @param a: input 2D point
 * @param b: input 2D point
 * @returns euclidean distance between a and b
 */
float Solution::dist(float a[2], float b[2]) {
    return roundf(sqrt(
            ((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]))));
}

float Solution::getDist(int i, int j){
    if (i > j)
        return distances[i][j];
    else 
        return distances[j][i];
}





