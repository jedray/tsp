#ifndef OPT2_H
#define OPT2_H

#include <utility>
#include "Optimization.h"

class Opt2: public Optimization {
    
    private:
        int nb_moves;       //<< maximum number of 2-opt moves 
        bool prunning;      //<< prunning improvement
        bool KNN_speedup;   //<< k-NNs speed up improvement
        int K;              //<< K nearest neighbours 
        bool node_insertion;//<< node insertion improvement
    public:
        Opt2(int nb, bool prune, bool KNN_boost, int k, 
                bool n_insertion):node_insertion(n_insertion), 
        prunning(prune), nb_moves(nb), KNN_speedup(KNN_boost),K(k) {};

        void optimize(Solution &s);

        float gain(Solution &s, int *tour, std::pair<int,int> i, 
                std::pair<int,int> j);

        bool prune(Solution &s, int *tour, std::pair<int,int> i, 
                std::pair<int,int> j);
 
        void apply_2optmove(int *tour, int n, std::pair<int,int> i,
                std::pair<int,int> j);

        void find_KNNs(Solution &s, int n);
        
        void KNN_2optMove(Solution &s, int *tour, int n, int *G);
       
        void std_2optMove(Solution &s, int *tour, int n, int *G);
        

};


#endif
