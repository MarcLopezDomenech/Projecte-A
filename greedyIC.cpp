#include "aprox_esper.cpp"

using VI = vector<int>;
using namespace std;

#define N_JOCS 100

int greedyLTgrau(const vector<VI>& G, vector<int>& S,const double interval, const double probabilitat) {
    int nodes=G.size();
    vector<vector<bool>> J(N_JOCS,vector<bool>(nodes,false));
    while(not aprox_esp(G,S,J,interval,probabilitat)){

        //ALGORITME GREEDY IC
    }
    return S.size();
}