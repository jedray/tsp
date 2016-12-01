#ifndef GREEDY_H
#define GREEDY_H

#include <utility>

#include "Construction.h"
#include "solution.h"


class Greedy : public Construction {
    public:
        void construct(Solution &s);
};

class EdgeSorter {
    public:
        EdgeSorter(const Solution &s):_s(s){};
        bool operator() (const std::pair<int,int> &e1, const std::pair<int,int> &e2) {
            return (_s.getDist(e1.first, e1.second) < _s.getDist(e2.first,e2.second));
        };
    private: 
        Solution _s;
};

#endif
