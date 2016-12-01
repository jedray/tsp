#include "Construction.h"


int Construction::nearestNeighbour(int point, bool *visited, Solution &s){
    int next_point = -1;
    for (int j = 0; j < s.getSize(); j++) {
        if ((visited[j] == false) and
            ( next_point == -1 or s.getDist(point, j) <
             s.getDist(point, next_point))) {
            next_point = j;
        }
    }
    return next_point;
}

