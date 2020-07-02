#include <fstream>
#include <vector>
#include <algorithm>
 
using std::vector;
using std::pair;
using std::string;
using std::make_pair;
 
std::ifstream fin("date.in");
std::ofstream fout("date.out");
 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#define forp(i, n) for(int i=0; i<n; i++)
#define forpc(i, k, n) for(int i=k; i<n; i++)
#define tri vector< pair<char, pair<int, int> > >
#define mp(a, b, c) make_pair(a, make_pair(b, c))
 
namespace allocator_type
{
    template <class T>
    T* single_allocate(int cols, T type)
    {
        T *vector1d = new T[cols];
        forp(i, cols) vector1d[i] = type;
        return vector1d;
    }
 
    template <class T>
    T** matrix_allocate(int rows, int cols, T type)
    {
        T **matrix = new T*[rows];
        forp(i, rows) matrix[i] = new T[cols];
        forp(i, rows) forp(j, cols) matrix[i][j] = type;
        return matrix;
    }
};
 
void interchange(vector <pair<char, pair<int, int> > >& inter, int poz, int temp, int& n)
{
    forpc(j, poz+1, temp) if((inter[poz].first == inter[j].first) && (inter[poz].second.first == inter[j].second.first) && (inter[poz].second.second == inter[j].second.second))
    {
        inter[j].second.first = n;
        n--;
    }
}
 
int main()
{
    int n;
    string s;
    fin>>n>>s;
    int *stari_finale = new int[n+1];
    forp(i, n+1) fin>>stari_finale[i];
    vector <char> Tranzitii[n+1][n+1];
    int k;
    fin>>k;
    forp(i, k)
    {
        int x, y;
        char c;
        fin>>c>>x>>y;
        Tranzitii[x][y].push_back(c);
    }
    int **X = allocator_type::matrix_allocate<int>(n+1, n+1, 0);
    forpc(i, 1, n+1) forp(j, i)
    if((stari_finale[i] == 0 && stari_finale[j] == 1) || (stari_finale[i] == 1 && stari_finale[j] == 0))
        X[i][j] = 1;
    while(true)
    {
        bool ok = false;
        forpc(i, 1, n+1) forp(j, i)
        if(X[i][j] == 0)
        {
            forp(l, s.length())
            {
                int ci, cj;
                forp(k, n+1){
                    forp(z, Tranzitii[i][k].size()) if(Tranzitii[i][k][z] == s[l]) ci = k;
                    forp(z, Tranzitii[j][k].size()) if(Tranzitii[j][k][z] == s[l]) cj = k;
                }
                if(X[ci][cj] == 1 || X[cj][ci] == 1){
                    X[j][i] = 1; X[i][j] = 1; ok = true;
                }
            }
        }
        if(!ok) break;
    }
    vector <int> Clsechiv[n];
    forp(j, n)
    {
        Clsechiv[j].push_back(j);
        forpc(i, j+1, n+1) if(X[i][j] == 0)
            Clsechiv[j].push_back(i);
    }
    int *T = allocator_type::single_allocate<int>(n+1, -1);
    if(T[n] == -1) T[n] = n;
    forp(i, n) forp(j, Clsechiv[i].size()) if(T[Clsechiv[i][j]] == -1) T[Clsechiv[i][j]] = i;
    tri perechi, perechi_finale;
    forp(i, n+1) forp(j, n+1) forp(k, Tranzitii[i][j].size()) perechi.push_back(mp(Tranzitii[i][j][k], T[i], T[j]));
    int nr = -1;
    forp(i, perechi.size())
    {
        interchange(perechi, i, perechi.size(), nr);
        if(perechi[i].second.first >= 0)
            perechi_finale.push_back(mp(perechi[i].first, perechi[i].second.first, perechi[i].second.second));
    }
    std::sort(T, T + n + 1);
    int count = std::distance(T, std::unique(T, T + n + 1));
    fout<<"Numarul de stari: "<<count<<"\nStari finale: ";
    forp(i, count + 1)
    {
        forp(j, count + 1) if(T[i] == T[j] && stari_finale[T[i]] == 1)
            fout<<1<<" ";
        fout<<0<<" ";
    }
    fout<<"\nNumar tranzitii: "<<perechi_finale.size()<<"\nTranzitii: \n";
    for(tri::iterator it = perechi_finale.begin(); it < perechi_finale.end(); it++) fout<<it->first<<" "<<it->second.first<<" "<<it->second.second<<"\n";
    return 0;
}
#pragma GCC diagnostic pop
