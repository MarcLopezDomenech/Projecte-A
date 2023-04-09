#include "difusioLT.cpp"

using namespace std;
using VI = vector<int>;

int greedyLTgrauWeighted(const vector<VI>& G, const vector<int>& R, vector<int>& S, const vector<float>& W) {
    int n = G.size();
	S = vector<int> (0);
    vector<bool> A(n, false);
	vector<int> act_reb(n, 0);
	int n_act_fix = 0;
    
    vector<double> w_grau(n);
    int imax = 0;
    for (int i = 0; i < n; ++i) {
        double grau = G[i].size();
        w_grau[i] = grau*W[i];

    }
    
    while (n_act_fix < n) {
        double max = -1;
        
        for(int i = 0; i <n; ++i) {
            if (not A[i] and w_grau[i] > max) {
                max = w_grau[i];
                imax = i;
            }
        }
        
        S.push_back(imax);
        vector<int> newi(0); newi.push_back(imax);
        vector<int> nous_activats;
        n_act_fix = difusioLTeficient2(G, R, newi, n_act_fix, act_reb,A,nous_activats);
        
        for (int node_afegit : nous_activats) { //Traiem les arestes dels vertexs ja activats del grau
            for (int j=0; j<G[node_afegit].size(); ++j) {int vei = G[node_afegit][j]; w_grau[vei] -= W[vei];}
            w_grau[node_afegit] = 0;
        }
    }
    return S.size();
}

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
        
        S.push_back(imax); //L'afegim a S
        VI aux;
        aux.push_back(imax);
        vector<int> nous_activats;
        c = difusioLTeficient2(G, R, aux, c, act_reb_S,ja_activats_S, nous_activats);

		for (int node_afegit : nous_activats) { //Traiem les arestes dels vertexs ja activats del grau
                for (int j=0; j<G[node_afegit].size(); ++j) {int vei = G[node_afegit][j]; --grau[vei];}
                grau[node_afegit] = 0;
            }
    }
    return S.size();
}
 
