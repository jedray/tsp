#include <ctime>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <iostream>

#include "sa_opt2.h"
#include "solution.h"

std::pair<int,int>  Sa_opt2::random_edge(int *tour, int n, const std::pair<int,int> &i){
    int a = rand() % n;
    int b = (a+1) % n;
    
    if(i.first == -1 || i.second == -1){
        std::pair<int, int> edge(a,b);
        return edge;
    }

    if(tour[i.first] == tour[b]){
        b = (b+n-1) % n;
        a = (b+n-1) % n;
    } else if (tour[i.first] == tour[a]){
        a = (a+2)%n;
        b = (a+1)%n;
    } else if (tour[i.second] == tour[a]){
        a = (a+1)%n;
        b = (a+1)%n;
    }
    
    std::pair<int,int> edge(a,b);

    return edge;

}

float Sa_opt2::gain(Solution &s,int *tour, std::pair<int,int> i, std::pair<int, int> j){
    
    float a = s.getDist(tour[i.first], tour[i.second]);
    float b = s.getDist(tour[j.first], tour[j.second]);
    float c = s.getDist(tour[i.first], tour[j.first]);
    float d = s.getDist(tour[i.second], tour[j.second]);

    return d+c-a-b;
}

float Sa_opt2::T(float f, int t){
    T_Max = T_Max*f;
}

void Sa_opt2::apply_2optmove(int *tour, int n, std::pair<int,int> i, std::pair<int,int> j){
    
    

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

bool Sa_opt2::prune(Solution &s, int *tour, std::pair<int,int> i, std::pair<int,int> j){
    
    int d1 = s.getDist(tour[i.first],tour[i.second]);
    int d2 = s.getDist(tour[i.second],tour[j.first]);
    return(d1 < d2);
}


void Sa_opt2::optimize(Solution &s){


    // initialisation

    int n = s.getSize();
    int G=0,g=0;    
    // no need for optimization
    if (n<4)
        return;

    int tour[n];
    for(int i=0; i<n; i++)
        tour[i] = s.getVal(i);



    // set randomness
    srand(time(NULL));

    
    // initialise sa (i.e. simulated annealing)

    std::pair<int,int> default_(-1,-1);
    std::pair<int,int> i, i_;
    std::pair<int,int> j, j_;
    int t = 0;
    float gain_; 
    float f = 0.95;
    int g_save = 0;    
   
    while (t < time_){
    
        g_save = 0;        
        // equilibreum reached at k=n
        for(int k = 0; k < T_Length; k++){
        
            // pick at random and edge j != i from tour
            i = random_edge(tour,n,default_);
            j = random_edge(tour,n,i);
                 
            gain_ = gain(s,tour,i,j);
        
            // Simulated annealing algorithm
            // if there is a gain then make a change
            // where:
            //          gain = tour_dist(t+1) - tour_dist(t) 
            if ( gain_ <= g_save){
                g_save = gain_;
                i_ = i;
                j_ = j;
            }
            // else then apply a change with 
            // a probability exp(gain/T(t)) 
            // where:  
            //          T = cooling schedule
            //          T(C,t) = temperature at time t
            else {
                float p = rand()/(float)RAND_MAX;
                 
                if ( p < exp( -gain_/T(f,t)) ){       
                    apply_2optmove(tour,n,i,j);
                }
            }
        }

        if(g_save <= 0 ){
            apply_2optmove(tour,n,i_,j_);
        }

        t++;
           //std::pair<int,int> i;
    //std::pair<int,int> j;
    std::pair<int,int> best_i, best_j;

    int G,g=0;

    /*for(int h=0; h<60;h++){
        G =0;
        for(int l = 0; l< n; l++){
            i = std::make_pair(l, (l+1)%n);
            for(int k = l; k<n; k++){
                j = std::make_pair(k, (k+1)%n);
                if (i.first == j.first or j.second == i.first 
                        or i.second == j.first)
                    continue;
                g = gain(s,tour,i,j);
                if(g < 0 && g < -(G) ){
                    G = -g;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if (G!=0)
            apply_2optmove(tour,n,best_i,best_j);
    */
        /// ------------------------------
        if(G < 10){
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
                G = G + g;
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

        /// -------------------------------
    }
    s.setPath(tour);
}
