#include "greedyLTgrau.cpp"



using namespace std;
using VI = vector<int>;



VI localSearchLT(const vector<VI>& G, const vector<int>& R){ //Presuposa G (graf), R (resistencies).
	VI S(0);
	greedyLTgrau(G, R, S);
	bool found = true;
	int tot = G.size();
	vector<bool> A(tot,false);
	while (found) {
		int n = S.size();
		found  = false;
		for (int i=0; not found and i<n; ++i) { 
			VI aux;
			for (int j=0; j<n; ++j) {
				if (j!=i) aux.push_back(S[j]);
			}
			int val = S[i];
			if (tot == difusioLT(G,R,aux,A)) { //Si aux es solucio.
				found = true;
				S.erase(S.begin()+i);
			}
		}
	}
	return S;
}




