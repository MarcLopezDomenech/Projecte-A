#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <stdlib.h>

using namespace std;

vector<vector<int>> G;
vector<int> S;
double p;
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
	cin >> p; //Potser comprovar que va entre 0 i 1.
	
	
	
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
	srand(time(NULL));
	vector<bool> Activat(n,false); //Cap vertex activat inicialment
	queue<int> Q;
	for (int i=0; i < (int)S.size(); ++i) {
		Activat[S[i]] = true; //Els vertes de S estan activats ja.
		Q.push(S[i]);   //Afegir a la cua per propagar els vertexs de S.
	}
	int res = S.size(); //Aqui guardem quants vertexs diferents estan activats.
	double aux = p*100;
	
	
	while (not Q.empty() and res < n) {
		int v = Q.front();
		Q.pop();
		
		for (int i=0; i < (int)G[v].size(); ++i) {
			int u = G[v][i];
			if (not Activat[u]) {
				if ((rand() %100)< aux) { //Activem
					Activat[u] = true;
					++res;
					Q.push(u);
				}
			}
		}
		

		
	}
	
	
	return res;
}




int main() {
	llegir();
	int c = difusio();
	cout << "S'han activat " << c << " vèrtexs." << endl;
}
