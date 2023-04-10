
using namespace std;
using VI = vector<int>;


int localSearchLTWeighted(const vector<VI>& G, const vector<int>& R, vector<int>& S, const vector<float>& W){ //Presuposa G (graf), R (resistencies).

	greedyLTgrauWeighted(G, R, S, W);
	bool found = true;
	int tot = G.size();
	int imin = 0;
	vector<bool> A(tot,false);
	while (found) {
		int s = S.size();
		found  = false;
		for (int i=imin; not found and i<s; ++i) { 
            int node = S[i];
			S.erase(S.begin()+i);
			if (tot == difusioLT(G,R,S,A)) { //Si S\i es solucio.
				found = true;
				imin = i;
			}
			else S.insert(S.begin()+i,node);
		}
	}
	return S.size();
}

int initRand(const vector<VI>& G, const vector<int>& R, vector<int>& S) {
	    int n = G.size();
    
    vector<bool> ja_activats_S(n, false);
    vector<int> act_reb_S(n, 0);
    int i = 0;
    int c = 0;
    while (c != n){

        
		while (ja_activats_S[i]) ++i;
		S.push_back(i);

        vector<int> nous_activats;
        c = difusioLTeficient2(G, R, S, c, act_reb_S,ja_activats_S, nous_activats);
		
    }
	return S.size();
}


int localSearchLT(const vector<VI>& G, const vector<int>& R, vector<int>& S){ //Presuposa G (graf), R (resistencies).
	//cout << "Rand: " << initRand(G, R, S) << endl;;
	greedyLTgrau(G, R, S);
	//cout << "MidaS_inicial: " << S.size() << endl;
	cout<<"--------  Localsearch  --------"<<endl;
	bool found = true;
	int tot = G.size();
	int imin = 0;
	vector<bool> A(tot,false);
	while (found) {
		int n = S.size();
		found  = false;
		for (int i=imin; not found and i<n; ++i) { 
			int node = S[i];
			S.erase(S.begin()+i);
			if (tot == difusioLT(G,R,S,A)) { //Si S\i es solucio.
				found = true;
				imin = i;
			}
			else S.insert(S.begin()+i,node);
		}
	}
	return S.size();
}




