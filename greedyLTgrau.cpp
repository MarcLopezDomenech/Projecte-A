#include "NewdifusioLT.cpp"

using namespace std;
using VI = vector<int>;

int greedyLTgrau(const vector<VI>& G, const vector<int>& R, vector<int>& S) {
    int n = G.size();
    
    vector<bool> ja_activats_S(n, false);
    vector<int> act_reb_S(n, 0);
    
    vector<int> grau(n,0);
    
    for (int i=0; i < n; ++i) grau[i] = G[i].size();  //Graus del graf amb els vèrtexs no activats.
    
    int c = 0;
    while (c != n){
        
        int graumax = -1;
        int imax = -1;

        
        for (int i = 0; i < n; ++i) {//Agafem el vertex de grau màxim
			if (not ja_activats_S[i]) {
				if (grau[i] > graumax) {
					graumax = grau[i];
					imax = i;
				}
			}
        }
        
        vector<bool> nous_activats = ja_activats_S;
        S.push_back(imax); //L'afegim a S
        VI aux;
        aux.push_back(imax);
        c = difusioLTeficient(G, R, aux, c, act_reb_S, nous_activats);

		for (int i=0; i<n; ++i) {
			if (nous_activats[i] and not ja_activats_S[i]) { //Traiem les arestes dels vertexs ja activats del grau
				for (int j=0; j<G[i].size(); ++j) --grau[G[i][j]];
				grau[i] = 0;
			}
		}
		ja_activats_S = nous_activats; //Nous conjunt vertexs activats (al difondre imax)

    }
    return S.size();
}
 
