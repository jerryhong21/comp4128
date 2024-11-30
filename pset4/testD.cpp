#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
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

const int M = 5005;
const int N = 5005;

int n, m;
int p = 0;
bool secondColorUsed = false;

int seen[N];
int rSeen[N];
int scc[N];
int postorder[N];
int validColorSeen[N + 1];


vector<int> edges[M];
vector<int> rEdges[M];

void dfs(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : edges[u]) {
        dfs(v);
    }
    postorder[p++] = u;
}

// sccs start at 1
void rDfs(int u, int mark, int *sccStart) {
    if (rSeen[u]) return;
    rSeen[u] = true;
    scc[u] = mark;
    if (sccStart[mark] == -1) sccStart[mark] = u;
    for (int v : rEdges[u]) {
        rDfs(v, mark, sccStart);
    }
}

int computeSccs(int *sccStart) {
    int sccs = 1;
    for (int i = 1; i <=n;++i) {
        if (!seen[i]) dfs(i);
    }
    for (int i = p-1; i >= 0;--i) {
        int u = postorder[i];
        if (!rSeen[u]) {
            rDfs(u, sccs++, sccStart);
        }
    }
    return sccs - 1;
}

struct color {
    int u;
    int v;
    int c;
};

set<pair<int, int>> seenEdges;

bool switchColor = false;

void dfsColor(int u, int sccNumber, vector<color> &res) {
    validColorSeen[u] = true;
    // dfs and assign alternate colors to every outgoing edge
    
    // for every neighbour, check if that neighbour belongs in the scc
    // if true, then check if seen, if seen, dont recurse, but assign that edge color
    for (int v : edges[u]) {
        // edges has been seen
        if (seenEdges.find(make_pair(u,v)) != seenEdges.end()) {
            continue;
        }
        seenEdges.insert(make_pair(u,v));
        // cout << "Exploring neighbour vertex " << v << " of vertex " << u << endl;
        if (scc[v] != scc[u]) {
            // assign color 1 cus it doesn't matter for bridge edges
            res.push_back({u, v, (switchColor + 1)});
        } else {
            // if the neighbour belongs in the scc
            if (validColorSeen[v]) {
                // if it forms a cycle
                switchColor = !switchColor;
                res.push_back({u,v, (switchColor + 1)});
                secondColorUsed = true;
            } else {
                res.push_back({u,v, (switchColor + 1)});
                dfsColor(v, sccNumber, res);
            }
        }
    }
}

// function that validates that k colorings valid in this SCC
vector<color> validColor(int nSccs, int *sccStart) {
    vector<color> res;
    // color every scc
    for (int i = 1; i <= n; ++i) {
        validColorSeen[i] = false;
    }

    for (int i = 1; i <= nSccs;++i) {
        dfsColor(sccStart[i], i, res);
    }
    return res;
}

string tokenise(int u, int v) {
    string s = "";
    s += to_string(u);
    s+= ' ';
    s += to_string(v);
    // cout << s << endl;
    return s;
}

int main(void)
{

    cin >>n>>m;

    // convert uv into string 'uv'
    // store its index

    unordered_map<string, int> edgeIndex;

    for (int i = 1; i <=m ;++i) {
        int u,v;
        cin >> u >>v;
        edges[u].push_back(v);
        rEdges[v].push_back(u);
 
        edgeIndex[tokenise(u,v)] = i;
    }

    for (int i = 0; i<=n;++i) {
        seen[i] = false;
        rSeen[i] = false;
    }

    int sccStart[n + 1];
    for (int i = 1; i <= n; ++i) {
        sccStart[i] = -1;
    }
    // find SCCs
    int nSccs = computeSccs(sccStart);
    // cout << "There are " << nSccs << " CCs\n";
    // for (int i = 0 ; i < nSccs; ++i) {
    //     cout << "Start of scc " << i + 1 << " is vertex " << sccStart[i + 1] << endl;
    // }
    // starting vertex at every scc

    // stores every edge, u, v, color
    vector<color> res = validColor(nSccs, sccStart);
    // output the color of each vertex
    
    cout << (secondColorUsed ? 2 : 1) << endl;
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
        ans[i] = -1;
    }
    for (auto c : res) {
        int idx = edgeIndex[tokenise(c.u, c.v)];
        ans[idx - 1] = c.c;
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}
