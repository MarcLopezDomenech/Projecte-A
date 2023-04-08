#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <map>

#include "readGraph.cpp"
#include "greedyIC.cpp"
#include "greedyLTgrau.cpp"
#include "localSearchLT.cpp"
#include "localSearchIC.cpp"
#include "metaheuristicaLT.cpp"

#define test_mode true
#define show_S false


using namespace std;
using VI = vector<int>;

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

    if (model == "IC") {
        if (test_mode) cout << "Model IC. " << endl;
        if (alg == "greedy") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;

            cout<<"Probabilidad"<<" "<<"Medida del conjunto solución"<<" "<<"Intervalo de confianza"<<endl;
            for(c=0.1;c<1;c+=0.01){
                VI S(0);
                mida_S = greedyIC(G, S, intConf, c);
            }
        }
        else if (alg == "localsearch") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            mida_S = localSearchIC(G, S, intConf, c);
        }
        else if(alg == "metaheuristic") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            //metaheuristicaIC
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
            mida_S = greedyLTgrau(G, resistencia, S);
        }
        else if (alg == "localsearch") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            S = localSearchLT(G, resistencia);
            mida_S = S.size();
        }
        else if(alg == "metaheuristic") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            //metaheuristicaLT(G, resistencia);
        }

        //Comprovacio de que S, és efectivament una solució (amb el test_mode)
        if (test_mode) {
            cout << "Comprovem que la S obtinguda és solucio (executant la difusio amb aquest S fix): ";
            vector<bool> A;
            if (difusioLT(G, resistencia, S, A) == G.size()) cout << "ES SOLUCIO" << endl;
            else cout << "NO ES SOLUCIO" <<endl;
        }
    }

    //SORTIDA
    if (mida_S == S.size()) {
        cout << "Mida_S: " << mida_S << endl;
        if (show_S) {
            cout << "S = [";
            for (auto elem : S) cout << elem << '|';
            cout <<']'<<endl;
        }
    }
    else cout << "ERROR: Retorn de l'algorisme i mida S no concorden" << endl;
}

    //CODIS QUE CRIDA
    /*
        %GREDDY, LOCALSERCH, HEURISTIC
            %APROX_ESPERANÇA_GREEDY(graf G, nou S, Joc de prova J, interval de confiança) -> cond. complerta + EXTRA     //Treball Marc

            %GREEDY_IC()-> varaibles de entrada ( graf G, ja activats S, interval de confiança, probabilitat, interval de confiança) -> S final  //FALTA
            %GREEDY_LT()-> varaibles de entrada ( graf G, ja activats S) -> S final  //Treball Miquel
                %DIFUSIÓ
                    %DIFUSIO_IC() -> variables de entrada( graf G, ja activats S, nous S , probabilitat) -> quins nodes difosos     //CODI KAMIL
                    %AGAFSAS EL NOMBRE DE nodes difosos SI IGUAL AL NOMBRE DE NODES TOTAL -> GRAF COMPLERT

                    %DIFUSIO_LT() -> variables de entrada( graf G, ja activats S, nous S , llindar) -> nombre de nodes difosos      //CODI KAMIL
                    %AGAFSAS EL NOMBRE DE nodes difosos SI IGUAL AL NOMBRE DE NODES TOTAL -> GRAF COMPLERT

                %CODI SEGUIM EXECUTANT
                    %CAS IC SI NOMBRE DE GRAFS COMPLERT >= A INTERVAL DE CONFIANÇA, PARA    //Treball Marc
                    %CAS LT SI COMPLERT, PARA   //Treball Miquel
    */

    //SORTIDA
    /*
        %Retornaria S
        %Tamany S
    */