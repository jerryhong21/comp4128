#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int n = 16;
vector<string> words(n);
unordered_map<string, int> wordIndex;
vector<vector<int>> adj(n, vector<int>(n, 0));

vector<int> groups[4];

bool dfs(int idx)
{
    if (idx == n)
    {
        return true;
    }

    for (int g = 0; g < 4; ++g) {
        if (groups[g].size() < 4)
        {
            // Check if word idx can be added to group g
            bool canAdd = true;
            for (int w : groups[g])
            {
                if (adj[idx][w] == 0)
                {
                    canAdd = false;
                    break;
                }
            }
            if (canAdd) {
                groups[g].push_back(idx);
                if (dfs(idx + 1))
                {
                    return true;
                }
                groups[g].pop_back();
            }
        }
    }
    return false;
}

int main()
{

    for (int i = 0; i < n; ++i)
    {
        cin >> words[i];
        wordIndex[words[i]] = i;
    }
    int m;
    cin >> m;


    for (int i = 0; i < m; ++i)
    {
        string u, v;
        cin >> u >> v;
        int ui = wordIndex[u];
        int vi = wordIndex[v];
        adj[ui][vi] = adj[vi][ui] = 1;
    }

    if (dfs(0))
    {
        cout << "Possible\n";
        for (int g = 0; g < 4; ++g)
        {
            for (int idx : groups[g])
            {
                cout << words[idx] << ' ';
            }
            cout << '\n';
        }
    }
    else
    {
        cout << "Impossible\n";
    }
    return 0;
}
