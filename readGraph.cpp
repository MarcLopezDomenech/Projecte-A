using namespace std;
using VI = vector<int>;

// El format DIMACS es "c comment \n p edge n m \n e x y [m cops]". No implemento els comments. Els nodes van de 1 a n, els passo de 0 a n-1.
void readGraphDIMACS(int& n, int&m, vector<VI>& G){
    char p; string format;
    cin >> p >> format >> n >> m;
    G.resize(n, vector<int>(0));
    for (int i = 0; i < m; ++i){
        char e;
        int x, y;
        cin >> e >> x >> y;
        --x; --y;
        G[x].push_back(y); G[y].push_back(x);
    }
}

//El nostre format basic es "n \n m \n x y [m cops]". Nodes de 0 a n-1.
void readGraphBasic(int& n, int& m, vector<VI>& G){
    cin >> n >> m;
    G.resize(n, vector<int>(0));
    for (int i = 0; i < m; ++i){
        int x, y;
        cin >> x >> y;
        G[x].push_back(y); G[y].push_back(x);
    }
}
