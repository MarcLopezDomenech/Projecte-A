#include "difusioIC.cpp"

using VI = vector<int>;

bool aprox_esp(const vector<VI>& G,const vector<int>& nousS,vector<vector<bool>>& J,double interval, double probabilitat){ //interval en tant per 1
    int n=J.size();
    int nodes_tot=G.size();
    int ii=0;

    int necesaris= interval*n;
    int fallada = n-necesaris;

    int contador=0;

    while(ii<n){
        int nodes=difusioIC(G,nousS,probabilitat,J[ii]);
        if(nodes==nodes_tot){
            contador+=1;
        }

        if(contador>=necesaris){
            return true;
        }
        if((ii-contador)>fallada){
            return false;
        }
        ++ii;
    }
    return false;
    
}