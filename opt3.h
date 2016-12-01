#ifndef OPT3_H
#define OPT3_H

#include <utility>
#include "Optimization.h"


class Opt3: public Optimization{

    private:
        int nb_moves;
        int limit;
    public:
        Opt3(int nb, int l): nb_moves(nb), limit(l){}; 

        // apply the 3-opt move
        void apply_3optmove(int *tour, int n, std::pair<int,int> i, 
                std::pair<int,int> j, std::pair<int,int> k,
                int move);
        // compute the gain
        float gain(Solution &s,int *tour, std::pair<int,int> i, 
                std::pair<int, int> j, std::pair<int,int> k,
                int *type);

        // stadard 3-opt move
        void std_3optMove(Solution &s, int *tour, int n, int *G);
        
        // optimize with 3-opt
        void optimize(Solution &s);
   

};



#endif
