#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

vector<vector<int>> G;
vector<int> S;
double r;
//Potser al llegir ja guardar el grau de cada vertex, una mica més eficient.

void llegir() {
	
	//Llegim G, n num vertexs i m num arestes.
	int n,m,u,v;
	cin >> n >> m;
	
	G = vector<vector<int>>(n);
	
	for (int i=0; i<m; ++i) {
		cin >> u >> v; //Llegim la aresta
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	//Llegim r
	cin >> r; //Potser comprovar que va entre 0 i 1.
	
	
	
	//Llegim S
	int s;
	cin >> s;
	S = vector<int>(s);
	for (int i=0; i<s; ++i) {
		cin >> u;
		S[i] = u;
	}
}



int difusio() {
	int n = G.size();
	vector<bool> Activat(n,false); //Cap vertex activat inicialment
	queue<int> Q;
	for (int i=0; i < (int)S.size(); ++i) {
		Activat[S[i]] = true; //Els vertes de S estan activats ja.
		Q.push(S[i]);   //Afegir a la cua per propagar els vertexs de S.
	}
	int res = S.size(); //Aqui guardem quants vertexs diferents estan activats.
	vector<int> resistencia(n); 
	for (int i=0; i<n; ++i) resistencia[i] = ceil(r*G[i].size());
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
		
		cout << "Propagat el vertex " << v << " i l'estat d'activats es:" << endl;
		for (int i=0; i<n; ++i) cout << "vertex " << i << " " << Activat[i] << " " << endl;
		cout << "-----------------------------------" << endl;
		
	}
	
	
	return res;
}




int main() {
	llegir();
	int c = difusio();
	cout << "S'han activat " << c << " vèrtexs." << endl;
}
