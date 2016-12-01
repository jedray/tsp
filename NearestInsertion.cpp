#include <iostream>
#include <list>
#include <iterator>
#include "NearestInsertion.h"
#include "Construction.h"

void NearestInsertion::construct(Solution &s){
    
    int n = s.getSize();
    bool visited[n];    
    int path[n];

    // initialize path
    for(int i=0; i<n; i++){
        //path[i] = i;
        visited[i] = false;
    }
    

    // if n<4 no need to solve tsp  
    if (n<4) {
        s.setPath(path);   
        return; 
    }

    int nearestNeighbour[n];
    std::list<int>::iterator it, it_p, it_n;
    std::list<int> tour;
    int nextCity;

    visited[0] = true;
    nextCity= Construction::nearestNeighbour(0, visited, s);
    visited[nextCity] = true; 
    
    // initialize tour 2 two cities
    tour.push_back(0);
    tour.push_back(nextCity);
    

    // initialize nearest neighbour in tour
    for(int i=0; i<n; i++){
        if (visited[i])
            continue;
        if (s.getDist(i,0) < s.getDist(i,nextCity)) //****
            nearestNeighbour[i] = 0;
        else
            nearestNeighbour[i] = nextCity;
    }

    for(int k=2; k<n; k++){    
        
        // find nearest insertion
        for(int i=0; i<n; i++){
            // if visited ignore it 
            if(visited[i])
                continue;
            // initialize with first unvisited
            if(visited[nextCity]){
                nextCity = i;
                continue;
            }
            // if nearer to the current tour, save. 
            if(s.getDist(i,nearestNeighbour[i]) < s.getDist(nextCity,nearestNeighbour[nextCity])){ //***
                nextCity = i;
            }
        }

        // find nearest node in the tour to nextCity
        it_p = tour.begin();
        for( it=tour.begin(); it!= tour.end(); ++it){

            //std::cout << *it << " ; ";
            if(*it == nearestNeighbour[nextCity]){
                it_n = it; // save next iterator
                break;
            }
            it_p = it; // save previous iterator
        }
         
        ++it_n; 

        // insert nextCity
        if(it_n == tour.end())
            it_n = tour.begin();
        if(it == tour.begin()){
            it_p = tour.begin();
            std::advance(it_p,n);
        }

        if( s.getDist(nextCity,*(it_p)) < s.getDist(nextCity,*(it_n)) ) //***
            tour.insert(it, nextCity);
        else
            tour.insert(it_n, nextCity);

        // mark nextCity
        visited[nextCity] = true;
        
        // update nearest neighbours to unvisited nodes 
        for(int i=0; i<n; i++){
            if(visited[i])
                continue;
            if(s.getDist(i,nextCity) < s.getDist(i, nearestNeighbour[i])) ///***
                nearestNeighbour[i] = nextCity;
        }
    }
    
    // put the tour in an array
    int i = 0;
    for(it = tour.begin(); it != tour.end(); ++it){
        path[i] = *it;
        i++;
    }
    
    // save solution
    s.setPath(path);
}
