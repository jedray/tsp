#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

#include "Greedy.h"
#include "Construction.h"



void Greedy::construct( Solution &s ){
    
        
    int n = s.getSize();
    
    if (n == 1){
        int tour[1] = {0};
        s.setPath(tour);
        return;
    }

    // number of edges without repition
    int m = n*(n-1)/2;
    std::vector< std::pair<int,int> > edges(m);
    std::vector< std::pair<int,int> >::iterator it = edges.begin();
    
    // 0, 1 2 ... n-1
    // 1,   2 ... n-1 
    
    // construct edges
    
    for(int i = 0; i<n; i++){
        for(int j=i+1; j<n; j++){
            std::pair<int,int> p(i,j);
            *it = p;
            ++it;
        }
    }
    
    /*for(it = edges.begin(); it!= edges.end(); ++it){
        std::cout << (*it).first << ";" ; 
        std::cout << (*it).second << "\n" ; 
    }*/

    // sort edges
    EdgeSorter comparator(s);
    std::sort (edges.begin(), edges.end(), comparator);


   


    // tour construction

    int edge_counter = 0, path_counter = 0;
    int path_ID[n];
    int endingPoint[n];
    int visited[n];
    int i, j;
    for(int i=0; i<n; i++){
        visited[i] = 0;
        endingPoint[i]=-1;
    }
    
    std::pair<int,int> q;
    std::list< std::pair<int,int> > l;

    for(it = edges.begin(); it != edges.end(); ++it){
        if(visited[(*it).first] < 2 &&  visited[(*it).second] < 2 ){
            

            i = (*it).first;
            j = (*it).second;
            //std::cout << edge_counter <<" : "<< i <<";" << j  << "\n";

            // path_counter is number of disjoint 
            // paths found untill now 
           
            //new path
            if(visited[i] == 0 && visited[j] == 0){
                path_counter++;
                path_ID[i] = path_counter;
                path_ID[j] = path_counter;
                endingPoint[i] = j;
                endingPoint[j] = i;
            // add edge to a path without closing it
            } else if (visited[i] == 1 && visited[j] == 0){
                path_ID[j] = path_ID[i] ;
                endingPoint[j] = endingPoint[i];
                endingPoint[endingPoint[i]] = j;
            // add edge to a path without closing it
            } else if (visited[i] == 0 && visited[j] == 1){
                path_ID[i] = path_ID[j];
                endingPoint[i] = endingPoint[j];
                endingPoint[endingPoint[j]] = i;
            // either closing a path or joining two paths
            } else {
                // we do not want to close a path 
                // untill there is only one edge left
                // to finish the tour
                if(path_ID[i] == path_ID[j] && edge_counter < n-1)
                    continue;
                // we can merge two paths to make
                // a big one or close a path if 
                // we have already added n-1 edge
                else{
                     path_ID[endingPoint[i]] = path_ID[endingPoint[j]];
                     endingPoint[endingPoint[i]] = endingPoint[j];
                     endingPoint[endingPoint[j]] = endingPoint[i];
                }
            }
            visited[i]++;
            visited[j]++;
            edge_counter++;
            q = std::make_pair(i,j);
            l.push_back(q);
        }
    }


   
    int tour[n];
    std::list < std::pair<int,int> >::iterator it_;
    int current = l.front().first;
    
    /*
    for(it_ = l.begin(); it_!= l.end(); ++it_){
        std::cout << (*it_).first << ";" ; 
        std::cout << (*it_).second << "\n" ; 
    }*/
    
    
    
    
    for(int i=0; i<n; i++){

        it_ = l.begin(); 
        while (it_ != l.end()){
            if((*it_).first == current){
                //std::cout << (*it_).first << ";" ; 
                //std::cout << (*it_).second << "\n" ; 
                tour[i] = (*it_).first;
                current = (*it_).second;
                l.erase(it_);
                break;
            }
            
            if ((*it_).second == current) {
                //std::cout << (*it_).first << ";" ; 
                //std::cout << (*it_).second << "\n" ; 
                tour[i] = (*it_).second;
                current = (*it_).first;
                l.erase(it_);
                break;
            }
            ++it_;
        }
    }

    /*for(int i=0; i<n; i++)
        std::cout << tour[i] << "\n";
    */
    s.setPath(tour);
   
}
