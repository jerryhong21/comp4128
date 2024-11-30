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

const int M = 300005;
const int N = 100005;
int n, m;
vector<int> edges[M];

int preorder[N];
int reach[N];
bool seen[N];
int T = 0;
int bridges = 0;

vector<pair<int, int>> signedEdges;
vector<set<int>> visitedEdge(N);

void dfs(int u, int from = -1)
{
    seen[u] = true;

    for (int v : edges[u])
    {
        if (v != u && v != from)
        {
            // edge from u->v
            // cout << "pushed edge e(" << u << "," << v <<')' <<endl;
            if (visitedEdge[u].find(v) != visitedEdge[u].end())
            {
                continue;
            }
            signedEdges.push_back(make_pair(u, v));
            visitedEdge[u].insert(v);
            visitedEdge[v].insert(u);
            if (!seen[v])
            {
                dfs(v, u);
            }
        }
    }
}

void bridgeFinding(int u, int from = -1)
{
    preorder[u] = T++;
    reach[u] = preorder[u];

    for (int v : edges[u])
    {
        if (v != from)
        {
            // if u to v is a tree edge
            if (preorder[v] == -1)
            {
                bridgeFinding(v, u);
                // if v can't reach anytihing earlier than itself then u-v is a bridge
                if (reach[v] == preorder[v])
                {
                    bridges++;
                }
            }
            reach[u] = min(reach[u], reach[v]);
        }
    }
}

// keep a set of vertices covered
int main(void)
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        preorder[i] = -1;
        seen[i] = false;
    }

    // make undirected graph first
    // bridge edge detection
    // dfs

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    // find bridge from first vertex
    bridgeFinding(1);
    if (bridges > 0)
    {
        cout << 0 << endl;
        return 0;
    }

    // start the dfs
    dfs(1);
    // cout << "There are " << signedEdges.size() << " edges assigned\n";
    for (pair<int, int> se : signedEdges)
    {
        cout << se.first << " " << se.second << endl;
    }
}
