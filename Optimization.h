#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "solution.h"

class Optimization {

    public:
        /**
          *\brief Default constructor
          *
          */
        Optimization(){};
        /**
          *\brief Destructor
          *
          */
        ~Optimization(){};
        /**
          *\brief Optimizes a solution. Needs to be 
          *       implemented by children
          *
          *\param sol solution 
          *
          */
        virtual void optimize(Solution &sol){};
};


#endif
