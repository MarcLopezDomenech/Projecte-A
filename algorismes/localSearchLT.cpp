
using namespace std;
using VI = vector<int>;



int localSearchLT(const vector<VI>& G, const vector<int>& R, vector<int>& S){ //Presuposa G (graf), R (resistencies).

	greedyLTgrau(G, R, S);
	bool found = true;
	int tot = G.size();
	int imin = 0;
	vector<bool> A(tot,false);
	while (found) {
		int n = S.size();
		found  = false;
		for (int i=imin; not found and i<n; ++i) { 
			VI aux;
			for (int j=0; j<n; ++j) {
				if (j!=i) aux.push_back(S[j]);
			}
			if (tot == difusioLT(G,R,aux,A)) { //Si aux es solucio.
				found = true;
				S.erase(S.begin()+i);
				imin = i;
			}
		}
	}
	return S.size();
}




