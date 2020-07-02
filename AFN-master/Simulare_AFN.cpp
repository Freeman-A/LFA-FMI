#include <fstream>
#include <vector>

using std::vector;

int main()
{
    int *starile, n, k;
    std::ifstream fin("afn.in");
    std::ofstream fout("afn.out");
    std::string alfabet;
    fin >> n;
    starile = new int[n+1];
    for(int i = 0; i <= n; i++) fin>>starile[i];
    fin >> alfabet >> k;
    vector <char> graph[k][k];
    for(int i=0; i<k; i++)
    {
        char s;
        int n1, n2;
        fin>>s>>n1>>n2;
        graph[n1][n2].push_back(s);
    }
    int m;
    fin>>m;
    std::string s;
    for(int i=0; i<m; i++)
    {
        fin>>s;
        vector <int> queue_t;
        int exit = 0;
        queue_t.push_back(0);
        queue_t.push_back(-1);
        int e = s.length();
        for(int j=0; j<e; j++)
        {
            int p;
            while(queue_t.front() != -1)
            {
                p = queue_t[0];
                for(int k = 0; k < n+1; k++)
                {
                    int size_2t = graph[p][k].size();
                    for(int x = 0; x < size_2t; x++)
                        if (graph[p][k][x] == s[j]) queue_t.push_back(k);
                }
                if(queue_t.size() >= 1)
                    queue_t.erase(queue_t.begin());
            }
            queue_t.erase(queue_t.begin());
            if(queue_t.empty())
            {
                fout<<0<<"\n";
                exit = 1;
                break;
            }
            queue_t.push_back(-1);
        }
        int ok = 0;
        while(queue_t.size() > 0)
        {
            for (int ep = 0; ep < n+1; ep++)
                if (starile[ep] != 0 && ep == queue_t.front()){
                        ok = 1;
                        break;
                }
            queue_t.erase(queue_t.begin());
        }
        if(ok == 1)
            fout<<1<<"\n";
        else if(exit == 0)
            fout<<0<<"\n";
    }
    return 0;
}
