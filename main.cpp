#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <map>
#include <chrono>

#include "algorismes/readGraph.cpp"
#include "algorismes/greedyIC.cpp"
#include "algorismes/greedyLTgrau.cpp"
#include "algorismes/localSearchLT.cpp"
#include "algorismes/localSearchIC.cpp"
#include "algorismes/metaheuristicaLT.cpp"
#include "algorismes/metaheuristicaIC.cpp"

#define test_mode true
#define show_S false


using namespace std;
using VI = vector<int>;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

void Usage() {
    cout << "Usage: ./main model algorisme c (<Int. Conf.>)" << endl;
    cout << "   model: IC / LT" << endl;
    cout << "   algorisme: greedy | localsearch | metaheuristic (no MAYUS)" << endl;
    cout << "   c (probabilitat si IC, resistencia si LT): 0 <= c <= 1  (p.ex 0.85)"<< endl;
    cout << "       (Int. Conf.): Si el model es IC, llavors  0 <= Int.Conf. <= 1  (p.ex 0.5)" << endl;
    cout << "                     Sino no es tindra en compte" << endl;
}

int main(int argc, char* argv[]) {
    string model;
    string alg;
    double intConf, c;
    
    if ((argc == 4 or argc == 5) and (string(argv[1]) == "IC" or string(argv[1]) == "LT")) {
        model = argv[1];
        alg = argv[2];
        c = stod(argv[3]);

        if (alg != "greedy" and alg != "localsearch" and alg != "metaheuristic") {
            cout << "Algorisme no reconegut" << endl;
            Usage();
            return -1;
        }

        if (model == "IC") {
            intConf = stod(argv[4]);
            if (test_mode) {
                cout << "PARAMETRES: Model " << model << " (interval confiança : " << intConf << "), Algorisme " 
                << alg << ", Probabilitat: " << c << endl;
            }
        }
        else {
            intConf = -1;
            if (test_mode) {
                cout << "PARAMETRES: Model " << model << ", Algorisme " << alg << ", Resistencia: " << c << endl;
            }
        }
    }
    else {
        Usage();
        return -1;
    }

    int n, m;
    n = m = 0;
    vector<VI> G;

    if (test_mode) cout << "Inici lectura graf..." << endl;
    readGraphDIMACS(n, m, G);
    if (test_mode) cout << "Final lectura graf" << endl;

    VI S(0);
    int mida_S = 0;

    
    std::chrono::high_resolution_clock::time_point start, end;
    
    if (model == "IC") {
        if (test_mode) cout << "Model IC. " << endl;
        if (alg == "greedy") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = greedyIC(G, S, intConf, c);
            end = high_resolution_clock::now();
        }
        else if (alg == "localsearch") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = localSearchIC(G, S, intConf, c);
            end = high_resolution_clock::now();
        }
        else if(alg == "metaheuristic") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = metaheuristicaIC(G, S, intConf, c);
            end = high_resolution_clock::now();
        }
        
    }

    else if (model == "LT") {
        if (test_mode) cout << "Model LT. ";

        //Precalculat dels llindars de cada vertex
        vector<int> resistencia(n); 
	    for (int i=0; i<n; ++i) resistencia[i] = ceil(c*G[i].size());

        if (test_mode) cout << "(Llindars precalculats correctament)" << endl;

        if (alg == "greedy") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = greedyLTgrau(G, resistencia, S);
            end = high_resolution_clock::now();
        }
        else if (alg == "localsearch") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = localSearchLT(G, resistencia, S);
            end = high_resolution_clock::now();
        }
        else if(alg == "metaheuristic") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            start = high_resolution_clock::now();
            mida_S = metaheuristicaLT(G, resistencia, S);
            end = high_resolution_clock::now();
        }

        //Comprovacio de que S, és efectivament una solució (amb el test_mode)
        if (test_mode) {
            cout << "Comprovem que la S obtinguda és solucio (executant la difusio amb aquest S fix): ";
            vector<bool> A;
            if (difusioLT(G, resistencia, S, A) == G.size()) cout << "ES SOLUCIO" << endl;
            else cout << "NO ES SOLUCIO" <<endl;
        }
    }
    
    auto total_ms = duration_cast<milliseconds>(end - start);

    //SORTIDA
    if (mida_S == S.size()) {
        cout << "Mida_S: " << mida_S << " |Temps(ms): "<< total_ms.count() <<endl;
        
        if (show_S) {
            cout << "S = [";
            for (auto elem : S) cout << elem << '|';
            cout <<']'<<endl;
        }
    }
    else cout << "ERROR: Retorn de l'algorisme i mida S no concorden" << endl;
}
