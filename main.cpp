#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "readGraph.cpp"
#include "greedyIC.cpp"
#include "greedyLTgrau.cpp"

#define test_mode = false;
#define show_S = false;

using namespace std;
using VI = vector<int>;

void usage1() {
    cout << "Usage: ./main model algorisme c (<Int. Conf.>)" << endl;
    cout << "   model: IC / LT" << endl;
    cout << "       (Int. Conf.): Si el model es IC, escollir interval confiança entre 0 i 1, sino no es tindra en compte" << endl;
    cout << "   algorisme: greedy / localsearch / metaheuristic" << endl;
    cout << "   c (probabilitat si IC, llindar si LT): 0 <= c <= 1"<< endl;
}

int main(int argc, char* argv[]) {
    string model;
    string alg;
    double intConf, c;
    
    if ((argc == 4 or argc == 5) and (string(argv[1]) == "IC" or string(argv[1]) == "LT")) {
        model = argv[1];
        alg = argv[2];
        c = stod(argv[3]);
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
        usage1();
        return -1;
    }

    int n, m;
    n = m = 0;
    vector<VI> G;

    if (test_mode) cout << "Inici lectura graf...";
    readGraphDIMACS(n, m, G);
    if (test_mode) cout << "Final lectura graf";

    VI S(0);

    int mida_S = 0;
    if (model == "IC") {
        if (test_mode) cout << "Model IC. ";
        if (alg == "greedy") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            //greedyIC(G, S, intConf, c);
        }
        else if (alg == "localsearch") {
            if (test_mode) cout << "Executant algorisme: " << alg << endl;
            //localSearchIC;
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
        if (test_mode) cout << "Llindars precalculats correctament";

        if (alg == "greedy") {
            mida_S = greedyLTgrau(G, resistencia, S) << endl;
        }
        else if (alg == "localsearch") {

        }
        else if(alg == "metaheuristic") {}
    }

    if (mida_S == S.size()) {
        cout << "Mida_S: " << mida_S << endl;
        if (show_S) {
            cout << "S = [";
            for (auto elem : S) cout << elem << '|';
            cout <<']'<<endl;
        }
    }
    else cout << "ERROR: Retorn de l'algorisme i mida S no concorden"
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