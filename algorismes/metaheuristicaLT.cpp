#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
//#include <random>

using namespace std;

//Aquests dos valors es poden modificar per provar.
//Les probabilitats com la de mutacio també.
#define Mida_Populacio 40
#define Iteracions_Acaba 10 

vector<vector<int>> G;

vector<int> R;
vector<int> grau;
string model_meta;
double probabilitat;
double interval;

using VI = vector<int>;

class Indv
{
	public:
	vector<float> v;
	int fitness;

	Indv();
	Indv(vector<float> a);
	int calcular_fitness();
	Indv crossover(const Indv& i2, double p_elite);
	void decoder(vector<int>& S);
};

Indv::Indv() {
	this-> v = vector<float> (G.size(),0);
	fitness = G.size()*2 + 1;
}

Indv::Indv(vector<float> a) {
	this-> v = a;
	fitness = calcular_fitness();
}

Indv Indv::crossover(const Indv& i2, double p_elite) {
	
	int n = v.size();
	vector<float> fill(n);
	for (int i=0; i<n; ++i) {
		double p = rand()%101;
		if (p < p_elite*100) fill[i] = v[i];
		else fill[i] = i2.v[i];
	}
	return Indv(fill);
}


bool operator<(const Indv& i1, const Indv& i2) {
	return i1.fitness < i2.fitness;
}

int Indv::calcular_fitness() {
	int fitness = 0;
	vector<int> S;
	this->decoder(S);
	return S.size();
}

void Indv::decoder(vector<int>& S) {
	int n = G.size();
	S = vector<int> (0);
    vector<bool> A(n, false);
	vector<int> act_reb(n, 0);
	int n_act_fix = 0;
	
	if (model_meta == "LTbasic") {
        priority_queue<pair<double, int>> grau_nodes;
        for (int i=0; i<n; ++i){
            double grau = G[i].size();
            grau_nodes.push(pair<double,int>(grau*v[i],i));
        }
        
		while (n_act_fix < n) {
            //cout << n_act_fix << endl;
            
            int imax = grau_nodes.top().second; grau_nodes.pop();
            while (A[imax]) {imax = grau_nodes.top().second; grau_nodes.pop();}
            
			S.push_back(imax);
            vector<int> newi(0); newi.push_back(imax);
			n_act_fix = difusioLTeficient(G, R, newi, n_act_fix, act_reb,A);
		}
	}
	else if (model_meta == "LTexperimental"){
        greedyLTgrauWeighted(G, R, S, v);
    }
    else if (model_meta == "LTlocalsearch"){
        localSearchLTWeighted(G, R, S, v);
    }
	else if (model_meta == "IC") {
        vector<float> aux(n);
        priority_queue<pair<double, int>> grau_nodes;

        for (int i=0; i<n; ++i){
            double grau = G[i].size();
            grau_nodes.push(pair<double,int>(grau,i));
        }
        
		bool cond = true;
        vector<vector<bool>> J(N_JOCS,vector<bool>(G.size(),false));
        vector<int> S_Activats(N_JOCS,0);
		while (cond) {
			int imax = grau_nodes.top().second; grau_nodes.pop();
            
			S.push_back(imax);
			double perc=aprox_esp(G, S, J, interval, probabilitat, S_Activats);
			if(perc>=interval){
				cond=false;
			}
		}
	}
	//cout << "Tamany S: " << S.size() << endl;
}


int metaheuristicaLT(const vector<VI>& graf, const vector<int>& resistencia, vector<int>& S) {
	//cout << "Inici" << endl;
	srand(time(NULL));

	G = graf;
	R = resistencia;
	model_meta = "LTlocalsearch";
	int gener = 0;
	
	vector<Indv> populacio(Mida_Populacio);
	int min = G.size() + 1;
	int comptador = 0;
	//cout << "ini 1.5" << endl;
	grau = vector<int> (G.size());
	for (int i = 0; i < G.size(); ++i) {
		grau[i] = G[i].size();
	}

	//cout << "ini2" << endl;

	 vector<float> first (G.size(), 0.5);
	populacio[0] = Indv(first);
	for (int i=1; i < Mida_Populacio; ++i) { //Populacio Inicial.
		vector<float> aux(G.size());
		for (int j = 0; j < G.size(); ++j) {
			double number = ((double) rand() / (RAND_MAX));
			//cout << number << endl;
			aux[j] = number;
		}
		populacio[i] = Indv(aux);
	}

	//cout << "ini3" << endl;
	
	time_t start, actual, elapsed;
	time(&start);
	elapsed = start-start; //inicialitzar elapsed

	while (comptador < Iteracions_Acaba and elapsed < 500) {
		cout << "Generacio " << gener << ':';
		sort(populacio.begin(),populacio.end());

		if (populacio[0].fitness < min) {
			min = populacio[0].fitness;
			comptador = 0;
		}
		else ++comptador;
		
		vector<Indv> nova_gen;

		//Elitisme
		int elitisme = 24*Mida_Populacio/100;
		for (int i=0; i<elitisme; ++i) nova_gen.push_back(populacio[i]);

		//Mutacio
		int p_mutacions = 13*Mida_Populacio/100;

		for (int i=0; i < p_mutacions; ++i) { //Populacio Inicial.
		vector<float> aux(G.size());
		for (int j = 0; j < G.size(); ++j) {
			float number = ((double) rand() / (RAND_MAX));
			aux[j] = number;
		}
		nova_gen.push_back(Indv(aux));
	}

		//Crossover
		int cross = Mida_Populacio - elitisme - p_mutacions;
		int no_elit = Mida_Populacio-elitisme;
		
		for (int i=0; i<cross; ++i) {
			float p1 =rand()%elitisme;
			float p2 =elitisme + rand()%no_elit;
			Indv i1 = populacio[p1];
			Indv i2 = populacio[p2];
			Indv fill = i1.crossover(i2, 0.69);
			nova_gen.push_back(fill);
		}

		populacio = nova_gen;
		cout << " fitness " << populacio[0].fitness << endl;
		++gener;
		
		time(&actual);
		elapsed = actual - start;
		//cout << "time "<<elapsed << endl;
	}	
	populacio[0].decoder(S);
	return S.size();
}
