#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "solution.h"
#include "Optimization.h"
#include "Construction.h"


/**
  * \file Algotithm.h  
  */

/**
  * \class Algorithm
  *
  * Algorithm solving tsp problem
  *
  */

class Algorithm {
    private:
        Solution m_s;             /*!< an object solution     */
        Optimization *m_o = NULL; /*!< an object Optimization */
        Construction *m_c = NULL; /*!< an object construction */
    public:
        /*!
         *  \brief Default constructor
         */
        Algorithm();
        /*!
          * \brief Constructor with parameters
          *
          * \param c construction algorithm  
          * \param o optimization algorithm
          *
          */
        Algorithm(Construction *c, Optimization *o);
        
        /*!
          *\brief Destructor
          */
        ~Algorithm();

        /*!
          *
          * \brief Initialize solution m_s
          *
          * \param s solution
          */
        void initialize( Solution &s);
        
        /*!
          *
          * \brief When the instance of tsp 
          *        is trivial (i.e. less then three cities)
          *        the optimial solution is any solution
          *
          */
        void trivial();
        
        
        /*!
          *
          * \brief Runs Algorithm to solve tsp
          *
          * \return Solution to tsp 
          */
        Solution& run();
};


#endif
