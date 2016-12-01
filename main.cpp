#include <iostream>
#include <cmath>
#include <fstream>       // for ifstream, ofstream
#include <stdlib.h>
#include <time.h>       /* time */
#include <math.h>


// home packages
#include "Algorithm.h"
#include "solution.h"

// construction packages
#include "Construction.h"
#include "NearestNeighbour.h"
#include "NearestInsertion.h"
#include "Greedy.h"

// optimization packages
#include "Optimization.h"
#include "opt2.h"
#include "opt3.h"
#include "sa_opt2.h"
#include "LK.h"

using namespace std;

int main(int argc, char *argv[]) {

    /* Read input */
    int Npts;
    if (cin >> Npts) {
        float points[Npts][2];
        for (int i = 0; i < Npts; i++) {
            cin >> points[i][0];
            cin >> points[i][1];
        }
        
        // construction algorithm
        //Construction *solver = new NearestNeighbour();
        //Construction *solver = new NearestInsertion();
        Construction *solver = new Greedy();
        
        // optimization algorithm
        //Optimization *optimizer = new Opt2(70,false,false,0,true); // << Opt2(nb_moves, prunning, k-NNs, k, node_insertion)
        Optimization *optimizer = new Sa_opt2(200, Npts, 1);    // << Sa_opt2 (time, temperature length, maximum temperatrue)
        //Optimization *optimizer = new Opt3(10,1); 
        //Optimization *optimizer = new LK(100);                      // << LK(nb_moves)
        //Optimization *optimizer = new Optimization();

        // create a solution
        Solution solution(Npts, points, 0);
        
        // initialize tsp solver
        Algorithm algo(solver, optimizer);
        
        // initialize tsp with solution
        algo.initialize(solution);
        
        // solve tsp and put it in solution
        solution = algo.run();

        solution.display(false); 
    }
    return 0;
}
