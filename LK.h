#ifndef LK_H
#define LK_H

#include <utility>
#include <list>

#include "Optimization.h"
#include "solution.h"


// node (rank,id)
struct node {
    int rank;
    int id;
};

// an edge (u,v)
struct edge {
    node u;
    node v;
};


class LK: public Optimization{
    private:
        int count; /*< number of k-opt moves to do */
    public:
        LK(int c):count(c){};
        
        // optimize
        void optimize(Solution &s);
        // choose x1 
        bool choose_x1(node *tour, int n, bool *visited, node *t1,
                edge *x1);
        // choose y1
        bool choose_y1(Solution &s, node *tour, int n, bool *visited, 
                edge x1, node *t2, node *t3, edge *y1, int *G1);

        // choose xi
        bool choose_xi(node *tour, int n, bool *visited, node *t3, 
                edge *x2);
       
        // choose yi
        bool choose_yi(Solution &s, node *tour,int n, bool *visited,
                node *t4, edge x2, edge *y2,int *G2);

        // flip construct resulting tour
        void flip(node *tour, int n, std::list<edge> X);
       
        // store tour in tour_
        void store(node *tour_, node *tour, int n);

};


#endif
