#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
using namespace std;

using VI = vector<int>;

int difusioLTeficient(const vector<VI>& G, const vector<int>& R, const vector<int>& S, int n_act_fix, vector<int>& act_reb, vector<bool>& A){ //Presuposa G (graf), R (resistencies) i S (activats afegits) amb els valors corresponents, n_act_fix te quants activats fixes hi ha, act_reb te l'activacio rebuda ja calculada dels activats fixes, A te qui son els activats fixes. Retorna el size del activats totals finals, i actualitza A i act_reb.
    int n = G.size(); 
    
    int c = n_act_fix;
    queue<int> I; 
    for (int node_afegit : S) { 
        if (not A[node_afegit]) I.push(node_afegit); 
        A[node_afegit] = true;
    }
    
    int t = 0; 
    while (not I.empty()){ //Cada instant de temps evaluem els efectes de tots els nodes activats l'instant anterior
        c += I.size();
        queue<int> newI;
        
        while (not I.empty()){
            int i = I.front(); I.pop();
            
            for (int vei_i : G[i]){
                if (not A[vei_i]){
                    
                    ++act_reb[vei_i];
                    if (act_reb[vei_i] >= R[vei_i]) {
                        A[vei_i] = true;
                        newI.push(vei_i);
                    }
                }
            }
        }
        I = newI;
        ++t;
    }
   return c; 
}

int difusioLT(const vector<VI>& G, const vector<int>& R, const vector<int>& S, vector<bool>& A){
    int n = G.size();
    
    A = vector<bool>(n, false);
    vector<int> act_reb_buit(n, 0);
    
    return difusioLTeficient(G, R, S, 0, act_reb_buit, A);
}
