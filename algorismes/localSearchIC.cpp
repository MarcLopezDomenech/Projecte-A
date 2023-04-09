using namespace std;
using VI = vector<int>;


int localSearchIC(const vector<VI>& G, vector<int>& S,const double interval, const double probabilitat){
    greedyIC(G,S,interval,probabilitat);
    cout<<"--------  Localsearch  --------"<<endl;
	bool found = true;
	int tot = G.size();
	int imin = 0;
	vector<bool> A(tot,false);

	int it=(tot/100)+1;
	int nombre=0;

	while (found) {
		int n = S.size();

		found  = false;
		for (int i=imin; not found and i<n; ++i) { 
			VI aux;
			for (int j=0; j<n; ++j) {
				if (j!=i) aux.push_back(S[j]);
			}

            vector<vector<bool>> J(N_JOCS,vector<bool>(tot,false));
            vector<int> S_Activats(N_JOCS,0);
            double perc=aprox_esp(G,aux,J,interval,probabilitat, S_Activats);

			if (perc>=interval) { //Si aux es solucio.
				found = true;
				S.erase(S.begin()+i);
				imin = i;

				if(nombre%it==0){
					cout<<"Amb un conjunt de "<<S.size()<<" nodes, l'interval es: "<<perc<<endl;
				}
				++nombre;
			}
		}
	}
	

	/*
	cout<<"--------  Localsearch 2  --------"<<endl;
	int n = S.size();
	int max= n;
	while(found){
		found  = false;
		for (int i=max-1; not found and i>=0; --i) { 
			VI aux;
			for (int j=0; j<n; ++j) {
				if (j!=i) aux.push_back(S[j]);
			}

            vector<vector<bool>> J(N_JOCS,vector<bool>(tot,false));
            vector<int> S_Activats(N_JOCS,0);
            double perc=aprox_esp(G,aux,J,interval,probabilitat, S_Activats);

			if (perc>=interval) { //Si aux es solucio.
				found = true;
				S.erase(S.begin()+i);
				max = i;

                cout<<"Amb un conjunt de "<<S.size()<<" nodes, l'interval es: "<<perc<<endl;
			}
		}
	}
	*/
	return S.size();
}