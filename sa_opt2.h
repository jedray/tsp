#ifndef SA_OPT2_H
#define SA_OPT2_H

#include <utility>
#include "Optimization.h"

class Sa_opt2: public Optimization {
    
    private:
        int time_;
        int T_Length;
        float T_Max;
    public:
        Sa_opt2(int t, int Tlenght, float Tmax): time_(t), T_Length(Tlenght), T_Max(Tmax){};
        void optimize(Solution &s);
        std::pair<int,int>  random_edge(int *tour,int n,const std::pair<int,int> &i);
        float gain(Solution &s, int *tour, std::pair<int,int> i, std::pair<int,int> j);
        float T(float f, int t);
        bool prune(Solution &s, int *tour, std::pair<int,int> i, std::pair<int,int> j);
 
        void apply_2optmove(int *tour, int n, std::pair<int,int> i, std::pair<int,int> j);



};


#endif
