#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;

class AFD
{
private:
    int n, k, *stari_finale, stari[100][100];
    char automatism[100][100];
    string alfabet;

public:
    AFD();
    AFD(string in_file, string out_file);
    int verificare_alfabet(string cuvant);
};


int AFD::verificare_alfabet(string cuvant)
{
    int stare = 0, ep = 0, ok=1;
    while(ep < cuvant.length() && ok)
    {
        for(int i=0; i<k; i++)
        if(cuvant[ep] == automatism[stare][i]){
                stare = stari[stare][i];
                ok=1;
                break;
        }
        ep++;
    }
    if(stari_finale[stare]==1)
        return 1;
    return 0;

}


AFD::AFD(string in_file, string out_file)
{
    ifstream f(in_file.c_str());
    ofstream g(out_file.c_str());
    f>>n;
    stari_finale = new int[n];
    for(int i=0; i<=n; i++)
    {
        int temp;
        f>>temp;
        stari_finale[i] = temp;
    }
    f>>alfabet>>k;
    for(int i=0; i<k; i++)
    {
        char a;
        int b, c;
        f>>a>>b>>c;
        automatism[b][i] = a;
        stari[b][i] = c;
    }

    int m;
    f>>m;
    for(int i=1; i<=m; i++)
    {
        string verify;
        f>>verify;
        if(verificare_alfabet(verify)==0)
            g<<0;
        else
            g<<1;
    }
}

int main()
{
    AFD g("afd.in","afd.out");
    return 0;
}
