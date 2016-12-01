#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "solution.h"
#include "Construction.h"
class NearestNeighbour : public Construction {
    public:
        /**
         * construct a solution for tsp
         * @param s is a solution 
         */
        void construct(Solution &s);
        void set_KNN(Solution &s);
    private: 
        //int nearestNeighbour(int point, bool *visited, float dist, Solution &s); 
        int randomKNN(int Point, bool *visited, float dist, Solution &s, int k);
};

#endif
