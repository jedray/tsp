#include "NearestNeighbour.h"
#include "Construction.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


void NearestNeighbour::construct(Solution &s){

    // Find k-NN (i.e. nearest neighbours) for all nodes

    // Initialize visited vector and temporary path_ vector
    int startingPoint = 0;//s.getStartingPoint();
    int N = s.getSize();
    bool visited[N];
    int path[N];
    for (int i = 0; i < N; i++){
        visited[i] = false;
        path[i] = -1;
    }

    // Add starting point to path and visited vectors
    path[0] = startingPoint;
    float distance = 0;
    visited[startingPoint] = true;

    /* Loop to select the next N-1 points to visit */
    for (int i = 1; i < N; i++) {
        // Find the nearest neighbour to point path[i-1] and save it in path
        path[i] = Construction::nearestNeighbour(path[i - 1], visited, s);
        //path[i] = randomKNN(path[i-1], visited, distance, s, 3);
        visited[path[i]] = true;
        distance += s.getDist(path[i-1], path[i]);
    }

    // Close the circular graph
    distance += s.getDist(path[N-1], path[0]);
    if (distance <= s.getDistance()){
        s.setDistance(distance);
        s.setPath(path);
    }
}


void NearestNeighbour::set_KNN(Solution &s ){
    int N = s.getSize();
    int K = s.getK();
    int KNN[K];
    int candidate, temp;
    for(int i=0; i<N; i++){

        // initialize K-NNs (i.e. K nearest neighbours) to i 
        // with a different number from i
        for(int l=0; l<K; l++)
            KNN[l] = -1;    
        
        // find K-NNs to i
        for(int j=0; j<N; j++){
            
            // i can not be neighbour to itself
            if(i == j)
                continue;
            // is j within the K-NNs of i ?
            candidate = j;
            for(int l=0; l<K; l++){
            // if yes shift (i.e. new candidate is KNN[l]) 
                if(KNN[l] == -1){
                    KNN[l] = candidate;
                    break;
                }
                if(s.getDist(i,candidate) <= s.getDist(i,KNN[l])){
                    temp = KNN[l];
                    KNN[l] = candidate;
                    candidate = temp;       
                }
            }
        }

        // save k-NNs of i  
        s.setKNN(i,KNN);
    }
}


/*int NearestNeighbour::nearestNeighbour(int point, bool *visited, float dist, Solution &s){
    int next_point = -1;
    for (int j = 0; j < s.getSize(); j++) {
        if ((visited[j] == false) and
            ( next_point == -1 or s.getDist(point, j) <
             s.getDist(point, next_point))) {
            next_point = j;
        }
    }
    dist += s.getDist(point, next_point);
    return next_point;
}
*/
int NearestNeighbour::randomKNN(int point, bool *visited, float dist, Solution &s, int k){
   

    /* k nearest neighbour array */
    int KNN[k];
    for(int i=0; i <k; i++)
        KNN[i] = -1;

    /* candidate is the shifting variable */
    int candidate, temp; 
    
    /* finding the k nearest neighbours */
    for (int j = 0; j < s.getSize(); j++) {
        candidate = j;
        for (int l = 0; l < k; l++){
            if ((visited[candidate] == false) and
                ( KNN[l] == -1 or s.getDist(point, candidate) <
                    s.getDist(point, KNN[l]))) {
                temp = KNN[l];
                KNN[l] = candidate;
                candidate = temp;
            }
        }
    }
    for(int i=0; i<k; i++)
        if(KNN[i] == -1) 
            KNN[i] = KNN[0];
             
    /* Pick randomly from the k nearest neighbour*/
    srand(time(NULL));
    int next_point = KNN[ rand() % k ];
     
    dist += s.getDist(point, next_point);
    
    return next_point;
}



