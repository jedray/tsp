#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "solution.h"

class Construction {
    
    public: 
        /**
          * \brief Default constructor
          *
          */
        Construction(){};
        /**
          * \brief Destroyer
          *
          */
        ~Construction(){};
        /**
          * \brief virtual method to be implemented be class children
          *
          */
        virtual void  construct(Solution &s) {};
    protected:
         int nearestNeighbour(int point, bool *visited, Solution &s); 
        
};

#endif
