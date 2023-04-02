#include "difusioLT.cpp"

using namespace std;
using VI = vector<int>;

int greedyLTexhaustiu(const vector<VI>& G, const vector<int>& R, vector<int>& S) {
    int n = G.size();
    
    vector<bool> ja_activats_S(n, false);
    vector<int> act_reb_S(n, 0);
    
    int c = difusioLTeficient(G, R, S, 0, act_reb_S, ja_activats_S);
    while (c != n){
        
        int c_max = 0;
        int i_max;
        vector<bool> ja_activats_Smax;
        vector<int> act_reb_Smax;
        
        for (int i = 0; i < n; ++i) if (not ja_activats_S[i]){ 
            vector<bool> ja_activats_Si = ja_activats_S;
            vector<int> act_reb_Si = act_reb_S;
            vector<int> Si = S;
            Si.push_back(i);
        
            int ci = difusioLTeficient(G, R, Si, c, act_reb_Si, ja_activats_Si);
            if (ci > c_max){
                c_max = ci;
                i_max = i;
                ja_activats_Smax = ja_activats_Si;
                act_reb_Smax = act_reb_Si;
            }
        }
        
        c = c_max;
        S.push_back(i_max);
        act_reb_S = act_reb_Smax;
        ja_activats_S = ja_activats_Smax;
    }
    return S.size();
}
    
