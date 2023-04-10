#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
using namespace std;

using VI = vector<int>;

int difusioICeficient(const vector<VI>& G, const vector<int>& S, double p, int n_act_fix, vector<bool>& A, int ii){ //Presuposa G (graf), S (activats afegits) i p (probabilitat) amb els valors corresponents, n_act_fix te quants activats fixes hi ha, A te qui son els activats fixes. Retorna el size del activats totals finals, i actualitza A i act_reb.
    
    srand((time(NULL)*ii)%1000000); p = 100*p;
    
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
                if (not A[vei_i] and (rand()%100<=p)){
                    
                    A[vei_i] = true;
                    newI.push(vei_i);
                }
            }
        }
        I = newI;
        ++t;
    }
   return c; 
}

int difusioIC(const vector<VI>& G, const vector<int>& S, double p, vector<bool>& A){
    int n = G.size();
    
    A = vector<bool>(n, false);
    
    return difusioICeficient(G, S, p, 0, A, 1);
}

