#include "difusioIC.cpp"

using VI = vector<int>;

double aprox_esp(const vector<VI>& G,const vector<int>& nousS,vector<vector<bool>>& J,const double interval, const double probabilitat, vector<int>&S_Activats){ //interval en tant per 1
    int n=J.size();
    int nodes_tot=G.size();
    int ii=0;

    /*
    int necesaris= interval*n;
    int fallada = n-necesaris;
    */

    //cout<<n<<" "<<necesaris<<" "<<fallada<<endl;

    int contador=0;

    while(ii<n){
        int nodes=difusioICeficient(G,nousS,probabilitat,S_Activats[ii],J[ii],ii);
        S_Activats[ii]=nodes;

        if(nodes==nodes_tot){
            contador+=1;
        }
        /*
        if(contador>=necesaris){
            return true;
        }
        if((ii-contador)>fallada){
            return false;
        }
        */
        ++ii;
    }
    //cout<<contador <<" "<<n<<endl;
    return double(contador)/double(n);
    
}