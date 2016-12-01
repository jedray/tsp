#include <cstdlib>
#include <cmath>
#include <ctime>


#include "Algorithm.h"




Algorithm::Algorithm(){
}

Algorithm::Algorithm(Construction *c, Optimization *o){
    m_o = o;
    m_c = c;
}

Algorithm::~Algorithm(){
}

void Algorithm::initialize(Solution &s){
    m_s = s;
}

void Algorithm::trivial(){
    int n = m_s.getSize();
    for(int i = 0; i<n; i++)
        m_s.setVal(i,i);
}

Solution& Algorithm::run(){
      
    int n = m_s.getSize();
    if(n<4)
        // trivial solution
        trivial();
    else{
        
        // construct a solution  
        m_c->construct(m_s);
    
        // optimize the solution
        m_o->optimize(m_s);
    }
    
    return m_s;
}
