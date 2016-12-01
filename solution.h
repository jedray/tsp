#ifndef SOLUTIONH
#define SOLUTIONH


class Solution {
    
    protected:
        int N;
        float **input;
        int *path;
        float distance;
        int startingPoint;        
        float **distances;
        
        int K;        
        int **K_nearestNeighbours;          

   
    public:
        Solution();                              // default constructor
        Solution(int n, float data[][2], int sp);// constructor
        ~Solution();                             // destroyer            
        void display(bool showDist = false);  
        virtual void solve(int startingPoint = 0){};
        virtual void opt2(int nbTransformation = 1){};   
        
        // getters
        int getSize() {return N;};
        int getK() {return K;};
        int getKNN(int i, int k){ return K_nearestNeighbours[i][k];}; 
        int getVal(int i){return path[i];};    
        int* getPath() {return path;};
        int getStartingPoint() {return startingPoint;};
        float* getPoint(int i) {return input[i];};        
        float getDistance() {return distance;} ;
    
        // setters
        void setPath(int* path);
        void setKNN(int i, int* KNN);
        void setK(int K);
        void setVal(int i, int val);
        void setDistance(float distance);         
        void setStartingPoint(int sp);
        float dist(float a[2], float b[2]);
        
        float getDist(int i, int j);
};


#endif
