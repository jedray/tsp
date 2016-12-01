

#include <utility>   //  pair
#include <list>      //  list
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "LK.h"





bool LK::choose_x1(node *tour, int n, bool *visited, node *t1,
        edge *x1){
    
    // conditions in LK: 
    //        - x1 in tour  

    int i1 = (*t1).rank;
    int i2 = (i1+1)%n;
    node t2 = tour[i2];

    x1->u = *t1; // this means: 
    x1->v = t2; //     x1 = (t1,t2)

    // mark us visited
    visited[(*t1).id] = true;
    visited[t2.id] = true;
    
    // update t_i
    *t1 = t2;

    // this operation is always possible
    return true;
}

bool LK::choose_y1(Solution &s, node *tour, int n, bool *visited, 
        edge x1, node *t2, node *t3, edge *y1, int *G1){
    
    // conditios in LK:
    //      - y1 not in tour
    //      - G1 > 0

    // not in tour
    if (((t2->rank + 1)%n == t3->rank) && (t2->rank != (t3->rank+1)%n))
        return false;

    // not visited
    if(visited[t3->id])
        return false;

    int d1 = s.getDist((x1.u).id, (x1.v).id);
    int d2 = s.getDist(t2->id,t3->id); 

    // G1 > 0
    if(d1-d2 <= 0)
        return false;


    visited[t3->id] = true;
    // update gain
    *G1 = *G1 + d1 - d2;
    // update t2
    y1->u = *t2;
    y1->v = *t3;
    *t2 = *t3;

    return true;
}

bool LK::choose_xi(node *tour, int n, bool *visited, node *t3,
        edge *x2){
    //Conditions LK:
    //    1. x in T
    //    2. xi != yi
    //    3. if t is joined to t1 the resulting tour is a tour. 
    
    // find x limited to one choice 
    
    node t4 = tour[(n+(t3->rank)-1)%n];
    if(visited[t4.id])
        return false;
    
    x2->u = *t3;
    x2->v = t4;
    visited[t4.id] = true;
    *t3 = t4;
    return true;
}

bool LK::choose_yi(Solution &s, node *tour,int n, bool *visited,
        node *t4,edge x2, edge *y2,int *Gi){
    // conditions LK: 
    //     1. y not in T
    //     3. yi != xi
    //     2. G > 0

    for (int i=0;i<n;i++){
    
        node t5 = tour[i];
        
        // if visited skip
        if (visited[t5.id])
            continue;

        // (t4,t5) must not be in the tour
        if((((*t4).rank+1)%n == t5.rank ) && ((*t4).rank == (t5.rank +1)%n))
            continue;

        
        int d1 = s.getDist((x2.u).id, (x2.v).id);
        int d2 = s.getDist((*t4).id,t5.id); 
        // Gi > 0
        if((*Gi)+ d1-d2 <= 0)
            continue;

        // update gain
        (*Gi) = (*Gi) + d1 - d2;
        // update visited
        visited[t5.id] = true;
        // init y2
        y2->u = *t4;
        y2->v = t5;
        // update ti
        (*t4) = t5;
        return true;
    }

    return false;
   
}



// store 
void LK::store(node *tour_, node *tour, int n){
    for(int i=0; i<n; i++)
        tour_[i] = tour[i];
}


void LK::flip(node *tour, int n, std::list<edge> X){
    
    node t1 = (X.front()).u;
    //X.pop_front();

    int r = 1;
    int i, j;
    node ti;
    //while (!X.empty()){
        ti = (X.back()).u;
        //X.pop_front();
        i = (t1.rank+1)%n;   // r = 1 => next(t1) else prev(t1) 
        j = (n+ti.rank-1)%n; // r = 1 => prev(ti) else next(ti)
    
        /*if (!( (j>i && j-i< n/2) || (j<i && i-j<n/2)) ){
            i = ti.rank;
            j = t1.rank;
            r= (-1)*r;
        }*/
        node tmp;
        for(int k=0; k< ((n + j-i ) %n +1)/2 ; k++){
            tmp = tour[(i+k)%n];
            tour[(i+k)%n] = tour[(n+j-k)%n];
            tour[(n+j-k)%n] = tmp;

            tour[(i+k)%n].rank = (i+k)%n;
            tour[(n+j-k)%n].rank =(n+j-k)%n;
        }
    //}
}


void LK::optimize(Solution &s){

    int n = s.getSize();// size of instance
    node T[n];       // tour of nodes
    bool visited[n];    // visited nodes

    for(int i=0; i<n; i++){
        node u = {i,s.getVal(i)}; // node (rank, ID)
        T[i] = u;
        visited[T[i].id] = false;
    }

//    std::cout << "-----Greedy solution \n";
/*    for(int i=0;i<n; i++)
        std::cout << T[i].rank <<  ";" << T[i].id << "\n";
    std::cout << "-------------------- \n"; 
  */  
    int nb_moves = 0;
    edge x1,y1,x2,y2;
    std::list<edge> X,Y;
    node tour[n];
    node tour_b[n];
    node t,t_next;
    int G = 0;
    int g = 0;
    bool stop = false;
    while (nb_moves < count){
        
        store(tour,T,n);
        /*if(nb_moves == 0){
            for(int i=0;i<n; i++)
                std::cout << tour[i].rank <<  ";" << tour[i].id << "\n";
        }*/
        for(int i=0; i<n; i++){
            stop = false;

            t = tour[i];
            
            // 1. choose x1 in Tour
            if (!choose_x1(tour,n,visited,&t,&x1))
                continue;
            X.push_back(x1);
            
            G = 0; 
            g = 0;            
            for(int j=0; j<n; j++){
                
                stop = false;
                t_next = tour[j];
                
                // 2. choose y1 such that y1 not in Tour & G > 0
                if ( !choose_y1(s,tour,n,visited,x1,&t,&t_next,&y1,&G) )
                    continue;
                Y.push_back(y1);

                // 3. loop
                
                for(int l = 2; l<n; l++){
                    // 4. choose xi
                    if( !choose_xi(tour,n,visited,&t,  &x2)){
                        //store(tour,tour_,n); // undo changes
                        break;
                    }
                    // 4.a resulting tour
                    // flip((t1,t4) (t2,t3))
                    int d1 = s.getDist((x2.u).id, (x2.v).id);
                    int d2 = s.getDist(t.id,(x1.u).id);
                    X.push_back(x2);
                    // resulting tour better
                    
                    //std::cout<< nb_moves << ".";
                    if( G + d1-d2 > 0){
                        /*std::cout << "----------------\n";
                        std::list<edge>::iterator it_ = Y.begin();
                        for(std::list<edge>::iterator it = X.begin(); it != X.end(); ++it){
                            std::cout << "("<<(*it).u.id <<";"<<(*it).v.id <<")   ";  
                            if(it_ != Y.end()){
                                std::cout << "("<<(*it_).u.id <<";"<<(*it_).v.id <<")   ";  
                                ++it_; 
                            }
                        }
                        std::cout << "\n";*/
                        G= G + d1-d2;
                            
                        //std::cout << "  gain " << G <<"\n before :";
                        //for(int r=0;r<n;r++)
                          //  std::cout << tour[r].rank << ";"<<tour[r].id << " __ ";
                        flip(tour,n,X);
                        //std::cout << " \n after :";
                        /*for(int r=0;r<n;r++)
                            std::cout << tour[r].id << " : ";
                        std::cout << "\n";*/
                        store(T,tour,n);
                        /*if(G > g){
                            store(tour_b,tour,n);
                            g = G;
                        }*/
                        // stop search for move
                        stop = true;
                        break;
                    }
                    

                    flip(tour,n,X); 
                    
                    // 5. choose yi
                    if( !choose_yi(s,tour,n, visited, &t,x2,&y2,&G)){
                        //store(tour,tour_,n); // undo changes
                        break;
                    }
                    Y.push_back(y2);
                
                } // end loop 3
       
                // if LK-move done!! stop!!
                if(stop){
                    nb_moves++;
                    //store(T,tour_b,n); 
                    //g = 0;
                    break;
                // else jump to loop y1 & undo changes
                } else {
                    store(tour,T,n);
                    X.clear();
                    Y.clear();
                    X.push_back(x1);
                    for(int l=0; l<n; l++)
                        visited[l] = false;
                    visited[(x1.u).id] = true;
                    visited[(x1.v).id] = true;
                    G = 0; 
                    t = x1.v;
                }                   
            } // end loop y1        
            
            // if LK-move done stop
            if(stop)
                break;
            else {
                X.clear();
                Y.clear();
                for(int l=0; l<n; l++)
                    visited[l] = false;
                G = 0;
                g = 0;
                store(tour,T,n);
            }
        } //end loop x1

        //std::cout << "nb moves: " << nb_moves << "\n";
        // no possible LK-move
        if(!stop)
            break;
    } // end while            

    int tour_[n];
    for(int i=0; i<n; i++){
        tour_[i] = T[i].id;
    }
    //std::cout << "nb of moves : " << nb_moves << "\n";
    s.setPath(tour_);
}


