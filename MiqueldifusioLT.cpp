#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

double r = 0.5;

int difusio(const vector<vector<int>>& G, const vector<int>& S, const vector<int>& resistencia) {
	int n = G.size();
	vector<bool> Activat(n,false); //Cap vertex activat inicialment
	queue<int> Q;
	for (int i=0; i < (int)S.size(); ++i) {
		Activat[S[i]] = true; //Els vertes de S estan activats ja.
		Q.push(S[i]);   //Afegir a la cua per propagar els vertexs de S.
	}
	int res = S.size(); //Aqui guardem quants vertexs diferents estan activats.
	
	vector<int> count(n,0); //Aqui quantes arestes a un vertex activat te cada vertex
	
	
	while (not Q.empty() and res < n) {
		int v = Q.front();
		Q.pop();
		
		for (int i=0; i < (int)G[v].size(); ++i) {
			int u = G[v][i];
			if (not Activat[u]) {
				++count[u];
				if (count[u] >= resistencia[u]) { //Activem
					Activat[u] = true;
					++res;
					Q.push(u);
				}
			}
		}
		
		//Per debug etc, cada instancia de temps.
		
		/* cout << "Propagat el vertex " << v << " i l'estat d'activats es:" << endl;
		for (int i=0; i<n; ++i) cout << "vertex " << i << " " << Activat[i] << " " << endl;
		cout << "-----------------------------------" << endl; */
		
	}
	
	return res;
}
/* 
int main() {
    int n, m;
	readGraphDIMACS(n, m, G);

    vector<int> resistencia(n); 
	for (int i=0; i<n; ++i) resistencia[i] = ceil(r*G[i].size());

	int c = difusio(resistencia);
	cout << "S'han activat " << c << " vèrtexs." << endl;
} */