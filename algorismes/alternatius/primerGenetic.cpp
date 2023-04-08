#include <iostream>
#include "difusioLT.cpp"
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

//Aquests dos valors es poden modificar per provar.
//Les probabilitats com la de mutacio també.
#define Mida_Populacio 100
#define Iteracions_Acaba 20 

vector<vector<int>> G;

vector<int> R;

using VI = vector<int>;

void readGraphDIMACS(int& n, int&m, vector<VI>& Gr){
    char p; string format;
    cin >> p >> format >> n >> m;
    Gr.resize(n, vector<int>(0));
    for (int i = 0; i < m; ++i){
        char e;
        int x, y;
        cin >> e >> x >> y;
        --x; --y;
        Gr[x].push_back(y); Gr[y].push_back(x);
    }
}

class Indv
{
	public:
	vector<bool> esta;
	int fitness;
	int calcular_fitness();
	Indv(vector<bool> a);
	Indv crossover(Indv i2);
	void mutacio(int index);
};

void Indv::mutacio(int index) {
	esta[index] = not esta[index];
}

Indv::Indv(vector<bool> a) {
	this-> esta = a;
	fitness = calcular_fitness();
}

Indv Indv::crossover(Indv i2) {
	
	
	int n = esta.size();
	vector<bool> fill(n);
	for (int i=0; i<n; ++i) {
		float p = rand()%101;
		if (p < 50) fill[i] = esta[i];
		else fill[i] = i2.esta[i];
	}
	return Indv(fill);
}


bool operator<(const Indv& i1, const Indv& i2) {
	return i1.fitness < i2.fitness;
}

int Indv::calcular_fitness() {
	int fitness = 0;
	int n = esta.size();
	vector<bool> A(n,false);
	vector<int> S;
	for (int i=0; i<n; ++i) {
		if (esta[i]) {
			++fitness;
			S.push_back(i);
		}
	}
	if (n != difusioLT(G,R,S,A)) fitness += (n+1); //Si no es solucio, es pitjor que qualsevol que ho sigui independent de la longitud.
	
	return fitness;
}



VI metaheuristicaLT(const vector<VI>& graf, const vector<int>& resistencia) {
	cout << "Inici" << endl;
	srand(time(NULL));
	
	G = graf;
	R = resistencia;
	
	int gener = 0;
	
	vector<Indv> populacio;
	int min = G.size() + 1;
	int comptador = 0;
	
	for (int i=0; i<Mida_Populacio; ++i) { //Populacio Inicial.
		vector<bool> aux(G.size());
		for (int i=0; i<G.size(); ++i) {
			float p =rand()%101;
			if (p < 50) aux[i] = true;
			else aux[i] = false;
		}
		populacio.push_back(Indv(aux));
	}
	while (comptador < Iteracions_Acaba) {
		cout << "Generacio " << gener << ':';
		sort(populacio.begin(),populacio.end());
		
		if (populacio[0].fitness < min) {
			min = populacio[0].fitness;
			comptador = 0;
		}
		else ++comptador;
		
		vector<Indv> nova_gen;
		//Elitisme
		int elitisme = 10*Mida_Populacio/100;
		for (int i=0; i<elitisme; ++i) nova_gen.push_back(populacio[i]);
		//Crossover
		int cross = Mida_Populacio - elitisme;
		
		for (int i=0; i<cross; ++i) {
			float p1 =rand()%51;
			float p2 =rand()%51;
			Indv i1 = populacio[p1];
			Indv i2 = populacio[p2];
			Indv fill = i1.crossover(i2);
			nova_gen.push_back(fill);
		}
		//Mutacio
		for (int i=0; i<Mida_Populacio; ++i) {
			float p =rand()%101;
			if (p <= 1) {
				float r = rand()%(G.size()+1);
				populacio[i].mutacio(r);
			}
		}
		
		
		
		populacio = nova_gen;
		cout << " fitness " << populacio[0].fitness << endl;
		++gener;
		
	}
	
	VI S;
	for (int i=0; i<populacio[0].esta.size(); ++i) {
	if (populacio[0].esta[i]) S.push_back(i);
	}	
	
	return S;
}


int main() {
	
	    int n, m;
    n = m = 0;
    vector<VI> Gr;
    readGraphDIMACS(n, m, Gr);
		double c;
    cin >> c;
	
	vector<int> resistencia(n); 
	for (int i=0; i<n; ++i) {
		resistencia[i] = ceil(c*Gr[i].size());
		
	}
	
	
	VI S = metaheuristicaLT(Gr,resistencia);
	cout << S.size() << endl;
	for (auto elem: S) cout << elem <<' ';
	cout << endl;
}


