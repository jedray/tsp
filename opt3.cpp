
#include <iostream>
#include <utility>
#include "opt3.h"



void Opt3::apply_3optmove(int *tour, int n, std::pair<int,int> i, 
        std::pair<int,int> j, std::pair<int,int> k, int move){
    
    
        // lentgh of segments
    int seg1 = (n+i.second-j.first)%n + 1;
    int seg2 = (n+j.second-k.first)%n + 1;
    int seg3 = (n+k.second-i.first)%n + 1;
    
    int a,b,c,d,e,f;
    
    a = j.second;
    b = k.first; 
    
    c = k.second;
    d = i.first;
    
    e = i.second;
    f = j.first;

    int temp;
    
    
    for(int l=0; l< ((b + n - a) % n + 1)/2; l++){
            temp = tour[(a + l ) % n];
            tour[(a + l) % n] = tour[(b - l + n) % n];
            tour[(b - l + n) % n] = temp;           
        }
    
    if(move >= 1){
        for(int l=0; l< ((d + n - c) % n + 1)/2; l++){
            temp = tour[(c + l ) % n];
            tour[(c + l) % n] = tour[(d - l + n) % n];
            tour[(d - l + n) % n] = temp;                        
        } 
    }
    if(move == 1)
    {
        for(int l=0; l< ((d + n - a) % n + 1)/2; l++){
            temp = tour[(a + l ) % n];
            tour[(a + l) % n] = tour[(d - l + n) % n];
            tour[(d - l + n) % n] = temp;                        
        }
    }
    
    
   /* 
    if (move == 0){

        a = j.second;
        b = k.first;

        // chooes the shortest path to reverse
        if (!((b > a && b-a <n/2 ) || 
                    (b < a && b + n - a <n/2))){
            a = k.second;
            b = j.first;
        }

        for(int l=0; l< ((b + n - a) % n + 1)/2; l++){
            temp = tour[(a + l ) % n];
            tour[(a + l) % n] = tour[(b - l + n) % n];
            tour[(b - l + n) % n] = temp;           
        }
    } else if(move == 1){

        // finding the shortest segments to reverse
        if (seg1 >= seg2 && seg1 >=seg2){
            a = j.second;
            b = k.first;
            c = k.second;
            d = i.first;
        }
        else if (seg2 >= seg1 && seg2 >= seg3){
            a = k.second;
            b = i.first;
            c = i.second;
            d = j.first;
        }
        else if (seg3 >= seg1 && seg3 >= seg2){
            a = i.second;
            b = j.first;
            c = j.second;
            d = k.first;
        }
    // for instance if i+1<j and length< n/2
    //                          
    // reverse the path:  --- a --- b ---- c ---- d ---
    //               to:  --- b --- a ---- c ---- d ---
    //               to:  --- b --- a ---- d ---- c ---
    //               to:  --- c --- d ---- a ---- b ---

        for(int k=0; k< ((b + n - a) % n + 1)/2; k++){
            temp = tour[(a + k ) % n];
            tour[(a + k) % n] = tour[(b - k + n) % n];
            tour[(b - k + n) % n] = temp;                        
        } 
        for(int k=0; k< ((d + n - c) % n + 1)/2; k++){
            temp = tour[(c + k ) % n];
            tour[(c + k) % n] = tour[(d - k + n) % n];
            tour[(d - k + n) % n] = temp;                        
        } 

        for(int k=0; k< ((d + n - a) % n + 1)/2; k++){
            temp = tour[(a + k ) % n];
            tour[(a + k) % n] = tour[(d - k + n) % n];
            tour[(d - k + n) % n] = temp;                        
        }
    } else {
        if(seg2 <= seg3){
            a = j.second;
            b = k.first;
            if(seg1 + seg2 < seg3){
                c = i.second;
                d = k.first;
            }else{
                c = k.second;
                d = i.first;
            } 
        } else {
            a = k.second;
            b = i.first;
            if(seg1 + seg3 < seg2){
                c = k.second;
                d = j.first;
            } else {
                c = j.second;
                d = k.first;
            }
        }

        for(int k=0; k< ((b + n - a) % n + 1)/2; k++){
            temp = tour[(a + k ) % n];
            tour[(a + k) % n] = tour[(b - k + n) % n];
            tour[(b - k + n) % n] = temp;                        
        }

        for(int k=0; k< ((d + n - c) % n + 1)/2; k++){
            temp = tour[(c + k ) % n];
            tour[(c + k) % n] = tour[(d - k + n) % n];
            tour[(d - k + n) % n] = temp;                        
        }
    } */
}



float Opt3::gain(Solution &s,int *tour, std::pair<int,int> i, 
        std::pair<int, int> j, std::pair<int,int> k, int *type){
    
    
    std::pair<int,int> tmp;
    
    int a = s.getDist(tour[i.first], tour[i.second]);
    int c = s.getDist(tour[k.first], tour[k.second]);

    if (i.first == j.first){
        int x0 = s.getDist(tour[i.first],tour[k.first]);
        int z0 = s.getDist(tour[i.second],tour[k.second]);
        *type = 0;
        return x0+z0 -a-c;
    }

    int b = s.getDist(tour[j.first], tour[j.second]);
    
    // gain of move type 1
    int x1 = s.getDist(tour[i.first], tour[j.second]);
    int y1 = s.getDist(tour[j.first], tour[k.second]);
    int z1 = s.getDist(tour[k.first], tour[i.second]);

    // gain of move type 2
    int x2 = s.getDist(tour[i.first], tour[j.second]);
    int y2 = s.getDist(tour[j.first], tour[k.first]);
    int z2 = s.getDist(tour[k.second], tour[i.second]);

    int g1 = x1 + y1 + z1 - a - b - c;
    int g2 = x2 + y2 + z2 - a - b - c;
    
    if (g1 < g2){
        *type = 1;
        return g1;
    } else {
        *type = 2;
        return g2;
    }
}





void Opt3::std_3optMove(Solution &s, int *tour, int n, int *G){
     
    std::pair<int,int> i;
    std::pair<int,int> j;
    std::pair<int,int> k;
    std::pair<int,int> best_i, best_j, best_k;
    int g=0;
    int move = -1;
    int best_move;
    int count = 0;
    bool stop = false;
    for(int l = 0; l< n; l++){
        i = std::make_pair(l, (l+1)%n);
        for(int r = 0; r<n; r++){
            j = std::make_pair(r, (r+1)%n);
            
            // if i = j than 2-opt possible 
            if (j.second == i.first or i.second == j.first)
                continue;

            for(int d = 0; d<n; d++){

                k = std::make_pair(d, (d+1)%n); 
                
                if (i.first == k.first or i.second == k.first 
                        or j.first == k.first or j.second == k.first
                        or i.first == k.second or j.first == k.second)
                    continue;

                if( i.second < j.first and i.second < k.first 
                        and k.first < j.first)  
                    continue;

                if( i.first > j.second and (k.first > i.first 
                            or k.first < j.second) ) 
                    continue;
                

                
                g = gain(s,tour,i,j,k,&move);
                if (g < 0 && g < -(*G)){
                    count++;
                    (*G) = -g;
                    best_i = i;
                    best_j = j;
                    best_k = k;
                    best_move = move;
                    if (count > limit){
                        stop = true;
                        break;
                    }
                    //std::cout << "move : "<< move;
                    //std::cout << "     ("<< i.first << ","<<i.second <<") ";
                    //std::cout << "     ("<< j.first << ","<<j.second <<") "; 
                    //std::cout << "     ("<< k.first << ","<<k.second <<") \n"; 
                }
            }
            if (stop)
                break;
        }
        if (stop)
            break;
    }
    //std::cout << *G << "\n";
    if (*G!=0)
        apply_3optmove(tour,n,best_i,best_j,best_k, best_move);
}





void Opt3::optimize(Solution &s){
    
    // initialisation 

    int n = s.getSize();
    int tour[n];
    int G;


    for(int i=0; i<n; i++)
        tour[i] = s.getVal(i);
    
    // find 3-opt moves
    for(int h = 0; h< nb_moves; h++){
        G = 0;  
        std_3optMove(s,tour,n,&G);    
        if (G==0)
            break;
    }
   
    s.setPath(tour);
}
