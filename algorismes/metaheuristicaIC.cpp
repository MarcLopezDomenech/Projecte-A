#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

//Aquests dos valors es poden modificar per provar.
//Les probabilitats com la de mutacio també.
#define Mida_Populacio 40
#define Iteracions_Acaba 10 

using VI = vector<int>;

int metaheuristicaIC(const vector<VI>& graf, vector<int>& S, const double intconf, const double p) {
	
	srand(time(NULL));
	G = graf;
	probabilitat = p;
	interval = intconf;
	model_meta = "IC";

	int gener = 0;
	
	vector<Indv> populacio(Mida_Populacio);
	int min = G.size() + 1;
	int comptador = 0;
	
	grau = vector<int> (G.size());
	for (int i = 0; i < G.size(); ++i) {
		grau[i] = G[i].size();
	}


	/* vector<float> first (G.size(), 0.5);
	populacio[0] = Indv(first);
	 */
	for (int i=0; i < Mida_Populacio; ++i) { //Populacio Inicial.
		vector<float> aux(G.size());
		for (int j = 0; j < G.size(); ++j) {
			double number = ((double) rand() / (RAND_MAX));
			aux[j] = number;
		}
		populacio[i] = Indv(aux);
	}

	
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
		int elitisme = 23*Mida_Populacio/100;
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
			Indv fill = i1.crossover(i2, 0.7);
			nova_gen.push_back(fill);
		}

		populacio = nova_gen;
		cout << " fitness " << populacio[0].fitness << endl;
		++gener;
		
		time(&actual);
		elapsed = actual - start;
		
	}	
	populacio[0].decoder(S);
	return S.size();
}
