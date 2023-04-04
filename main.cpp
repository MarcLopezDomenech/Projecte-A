#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "readGraph.cpp"
#include "greedyIC.cpp"

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
            cout << "Executant el model " << model << " (interval confiança : " << intConf << ")" << " amb l'algorisme " 
            << alg << " i p: " << c << endl;
        }
        else {
            intConf = -1;
            cout << "Executant el model " << model << " amb l'algorisme " << alg << " i p: " << c << endl;
        }
    }
    else {
        usage1();
        return -1;
    }
    //PARAMATRES ENTRADA //Treball Pol
    /*
        %Entrada llista adyacencia
        %Per defecte S buit

        %Boolea es IC(true) o LT (false)
            %interval de confiança (per IC)
        %probabilitat aresta p o llindar
        %Elecció algoritme
            %Elecció quin greedy o altre corre

        %Modo testeo
    */

    int n, m;
    n = m = 0;
    vector<VI> G;
    readGraphDIMACS(n, m, G);
    VI S(0);

    if (model == "IC") {
        if (alg == "greedy") {
            greedyIC(G, S, intConf, c);
        }
        else if (alg == "localsearch") {

        }
        else if(alg == "metaheuristic") {}
    }
    else if (model == "LT") {
        if (alg == "greedy") {
            //greedyLTgrau(G, S, intConf, c);
        }
        else if (alg == "localsearch") {

        }
        else if(alg == "metaheuristic") {}
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
}
