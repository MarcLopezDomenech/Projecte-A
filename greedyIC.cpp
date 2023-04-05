#include "aprox_esper.cpp"

using VI = vector<int>;
using namespace std;

#define N_JOCS 100000

int greedyIC(const vector<VI>& G, vector<int>& S,const double interval, const double probabilitat) {
    int nodes=G.size();

    vector<vector<bool>> J(N_JOCS,vector<bool>(nodes,false));

    priority_queue<pair<int, int>> grau_nodes;

    for (int i=0; i<nodes; ++i){
        int grau = G[i].size();
        grau_nodes.push(pair<int,int>(grau,i));
    }
    while(not aprox_esp(G,S,J,interval,probabilitat)){
        pair<int,int> p=grau_nodes.top();
        grau_nodes.pop();

        S.push_back(p.second);
    }
    return S.size();
}