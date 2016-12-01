#include <ctime>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <iostream>

#include "opt2.h"
#include "solution.h"



void Opt2::find_KNNs(Solution &s, int n){


    // Allocate k-NNs tables
    s.setK(K);

    int node;
    int candidate;
    int KNN[K];
    int tmp;
    for(int i=0; i<n; i++){
        node = s.getVal(i);
        // init K-NN
        for(int l=0; l<K; l++)
            KNN[l] = -1;
        // fill K-NN
        for(int j=0; j<n; j++){
            // node i is not a neighbour to itself
            if(node==j)
                continue;
            
            candidate = j;
            for(int l=0; l<K; l++){
                if (KNN[l] == -1){
                    KNN[l] = candidate;
                    break;
                }
                if(s.getDist(candidate,node) <= s.getDist(KNN[l],node)){
                    tmp = candidate;
                    candidate = KNN[l];
                    KNN[l] = tmp;
                }  
            }
        }
        // set K-NN for node i
        s.setKNN(node, KNN);
    }
    
}


float Opt2::gain(Solution &s,int *tour, std::pair<int,int> i, std::pair<int, int> j){
    
    float a = s.getDist(tour[i.first], tour[i.second]);
    float b = s.getDist(tour[j.first], tour[j.second]);
    float c = s.getDist(tour[i.first], tour[j.first]);
    float d = s.getDist(tour[i.second], tour[j.second]);

    return d+c-a-b;
}

void Opt2::apply_2optmove(int *tour, int n, std::pair<int,int> i, std::pair<int,int> j){
    
    

    int first = i.second;
    int second = j.first;

    // chooes the shortest path to reverse
    if (!((second > first && second-first <n/2 ) || 
            (second < first && second + n - first <n/2))){
        first = j.second;
        second = i.first;
    }

    int temp;
    // for instance if i+1<j and length< n/2
    // reverse the path:  --- i   i+1 ----  j    j+1 --
    //               to:  --- i    j  ---- i+1   j+1 -- 
    for(int k=0; k< ((second + n - first) % n + 1)/2; k++){
        temp = tour[(first + k ) % n];
        tour[(first + k) % n] = tour[(second - k + n) % n];
        tour[(second - k + n) % n] = temp;                        
    } 
    
}

bool Opt2::prune(Solution &s, int *tour, std::pair<int,int> i, std::pair<int,int> j){
    
    if(!prunning)
        return false;
    int d1 = s.getDist(tour[i.first],tour[i.second]);
    int d2 = s.getDist(tour[i.second],tour[j.first]);

    return(d1 < d2 /*or d3 < d4*/);
}


void Opt2::std_2optMove(Solution &s, int *tour, int n, int *G){
     
    std::pair<int,int> i;
    std::pair<int,int> j;
    std::pair<int,int> best_i, best_j;

    int g=0;

    for(int l = 0; l< n; l++){
        i = std::make_pair(l, (l+1)%n);
        for(int k = l; k<n; k++){
            j = std::make_pair(k, (k+1)%n);
            if (i.first == j.first or j.second == i.first 
                    or i.second == j.first)
                continue;
            g = gain(s,tour,i,j);
            if(g < 0 && g < -(*G) ){
                *G = -g;
                best_i = i;
                best_j = j;
            }
        }
    }
    if (*G!=0)
        apply_2optmove(tour,n,best_i,best_j);
    
    // node move
   
    if(*G < 20 && node_insertion){
        //std::cout << "ok \n";
        int best_node,p;
        int best_pos,q;
        int d1,d2,d3,d4,d5,d6;
        g = 0;    
        for(int i = 0; i<n; i++){
            d1 = s.getDist(tour[(n+i-1)%n],tour[(i+1)%n]);
            d2 = s.getDist(tour[(n+i-1)%n],tour[i]);
            d3 = s.getDist(tour[(i+1)%n],tour[i]);
            for(int j =0; j<n; j++){
                if ((n+i-1)%n == j or i == j)
                    continue;
                d4 = s.getDist(tour[j], tour[(j+1)%n]);
                d5 = s.getDist(tour[j], tour[i]);
                d6 = s.getDist(tour[(j+1)%n], tour[i]);

                if(d2+d3+d4 - d1-d5-d6>g){
                    g = d2+d3+d4    -d1-d5-d6;
                    best_node = i;
                    best_pos = j;
                }
            }
        }
        
        if(g>0){
            *G = *G + g;
             p = best_node;
             q = best_pos;
             if (p < q){
                int tmp = tour[p];
                for(int i=p; i< q; i++){
                     tour[i] = tour[i+1];
                }            
                tour[q] = tmp;
             } else {
                int tmp = tour[p];
                 for(int i=p; i>q+1; i--){
                    tour[i] = tour[i-1];
                }
                 tour[q+1] = tmp;
             }
        }  
    }
}

void Opt2::KNN_2optMove(Solution &s, int *tour, int n, int *G){
    

    // initialize rank of nodes in tour
    // tour[rank[node]] = node
    int rank[n];

    for(int i=0; i<n; i++)
        rank[tour[i]] = i;
    
    std::pair<int,int> i;
    std::pair<int,int> j1,j2,j;
    std::pair<int,int> best_i, best_j;

    int g=0;
    int r;
    
    for(int l = 0; l< n; l++){
        i = std::make_pair(l, (l+1)%n);
        for(int k = 0; k<K; k++){
            r = rank[s.getKNN(l,k)];
            j1 = std::make_pair( r , (r+1)%n);
            j2 = std::make_pair( (n+r-1)%n , r);
            if(s.getDist(tour[j1.first], tour[j1.second]) < 
                    s.getDist(tour[j2.first],tour[j2.second]))
                j = j1;
            else 
                j = j2;
            if (i.first == j.first or j.second == i.first 
                    or i.second == j.first)
                continue;
            if (prune(s,tour,i,j))
                continue;
            g = gain(s,tour,i,j);
            if(g < 0 && g < -(*G) ){
                *G = -g;
                best_i = i;
                best_j = j;
            }
        }
        for(int k = 0; k<K; k++){
            r = rank[s.getKNN(i.second,k)];
            j1 = std::make_pair( r , (r+1)%n);
            j2 = std::make_pair( (n+r-1)%n , r);
            if(s.getDist(tour[j1.first], tour[j1.second]) < 
                    s.getDist(tour[j2.first],tour[j2.second]))
                j = j1;
            else 
                j = j2;
            if (i.first == j.first or j.second == i.first 
                    or i.second == j.first)
                continue;
            g = gain(s,tour,i,j);
            if(g < 0 && g < -(*G) ){
                *G = -g;
                best_i = i;
                best_j = j;
            }
        }

    }
    if ((*G)!=0)
        apply_2optmove(tour,n,best_i,best_j);

}

void Opt2::optimize(Solution &s){


    // initialisation 

    int n = s.getSize();
    int tour[n];
    
    for(int i=0; i<n; i++)
        tour[i] = s.getVal(i);
    
    if(KNN_speedup && n>K){
        find_KNNs(s,n);
    }

    // find 2-opt move
    int G;
    for(int h = 0; h< nb_moves; h++){
        G = 0;
        
        if(KNN_speedup && n>K)
            KNN_2optMove(s,tour,n,&G);
        else
            std_2optMove(s,tour,n,&G);    
        if (G==0)
            break;
    }
    
    s.setPath(tour);
}
