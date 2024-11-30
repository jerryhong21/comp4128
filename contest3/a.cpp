#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>

// #include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef tuple<ll, ll, ll> t3l;

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

// we just need to find a path that will visit every vertex

const int N = 200010;
vector<int> edges[N];
vector<int> edges_r[N];
bool seen[N];
bool seen_r[N];
bool active[N];
int scc[N];
vector<int> postorder(N);

int n;
int p = 0;

int numActive = 0;
bool valid = false;

void dfs(int u)
{
    if (seen[u])
        return;
    seen[u] = true;
    for (int v : edges[u])
        dfs(v);
    postorder[p++] = u;
}

void dfs_r(int u, int mark)
{
    if (seen_r[u])
        return;
    seen_r[u] = true;
    scc[u] = mark;
    for (int v : edges_r[u])
        dfs_r(v, mark);
}

int compute_sccs()
{
    int sccs = 0;
    for (int i = 1; i <= n; i++)
        if (!seen[i])
            dfs(i);
    for (int i = p - 1; i >= 0; i--)
    {
        int u = postorder[i];
        if (!seen_r[u]) // ignore seen vertices
            dfs_r(u, sccs++);
    }
    return sccs;
}

bool seen1[N];

void dfsFinal(int u, vector<unordered_set<int>> &condensation, int nScc)
{
    if (seen1[u])
        return;
    numActive++;
    if (numActive == nScc) {
        valid = true;
        cout << "Yes\n";
        exit(0);
    }
    seen1[u] = true;
    for (int v : condensation[u])
    {
        dfsFinal(v, condensation, nScc);
    }
    numActive--;
}

int main(void)
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
            edges[i].push_back(a);
            edges_r[a].push_back(i);
            // player a and b can receive from player i
            edges[i].push_back(b);
            edges_r[b].push_back(i);
    }
    for (int i = 0; i <= n; ++i)
    {
        seen[i] = false;
        seen1[i] = false;
        seen_r[i] = false;
        active[i] = false;
        scc[i] = -1;
    }

    int nSccs = compute_sccs();
    for (int i = 1; i <= n; ++i)
    {
        // cout << "player " << i << " belong to scc " << scc[i] << endl;
    }

    vector<unordered_set<int>> condensation(nSccs);
    for (int u = 1; u <= n; ++u)
    {
        for (int v : edges[u])
        {
            if (scc[u] != scc[v])
            {
                condensation[scc[u]].insert(scc[v]);
                // cout << "added edge from scc " << scc[u] << " to scc " << scc[v] << endl;
            }
        }
    }

    int nSource = 0, nSink = 0;
    vector<int> inDeg(nSccs, 0), outDeg(nSccs, 0);
    for (int i = 0; i < nSccs; ++i)
    {
        for (int v : condensation[i])
        {
            outDeg[i]++;
            inDeg[v]++;
        }
    }
    for (int i = 0; i < nSccs; ++i)
    {
        if (inDeg[i] == 0)
            nSource++;
        if (outDeg[i] == 0)
            nSink++;
    }
    for (int i = 0; i < nSccs; ++i)
    {
        // cout << "scc " << i << " has outdeg " << outDeg[i] << " and inDeg " << inDeg[i] << endl;
    }
    if (inDeg[scc[1]] != 0)
    {
        cout << "No\n";
        return 0;
    }

    if (nSource > 1 || nSink > 1)
    {
        cout << "No\n";
        return 0;
    }
    dfsFinal(scc[1], condensation, nSccs);

    cout << "No\n";
    return 0;
}
