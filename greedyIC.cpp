#include "aprox_esper.cpp"

using VI = vector<int>;
using namespace std;

#define N_JOCS 100

int greedyIC(const vector<VI>& G, vector<int>& S,const double interval, const double probabilitat) {
    int nodes=G.size();
    vector<vector<bool>> J(N_JOCS,vector<bool>(nodes,false));

    vector<int> grau(nodes,0);
    map<int,int> grau_nodes;
    for (int i=0; i<nodes; ++i){
        grau[i] = G[i].size();
        grau_nodes.insert(pair<int,int>(grau[i],i));
    }

    while(not aprox_esp(G,S,J,interval,probabilitat)){
        map<int,int>::iterator it=grau_nodes.begin();
        S.push_back(it->second);
        grau_nodes.erase(it);
    }
    return S.size();
}