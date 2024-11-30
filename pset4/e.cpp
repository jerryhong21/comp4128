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


// approach
/*
    form the original MST

    for every edge - if the edge is in the MST, then easy
    for that edge is NOT in the MST, you can add the edge
    adding the edge will form a simple cycle in the MST, 

    any edge between the mst will form a simple cycle
    binary lifting, keep track of maximum edge betwee u to v
*/
const int N = 300010;
const int M = 300010;
ll totalWeight = 0;

int n,m;

struct edge {
    int u;
    int v;
    ll w;
};

vector<edge> edges;
unordered_set<int> mstEdges[N];
vector<int> allEdges[N];

unordered_map<string, ll> edgeWeights;
unordered_map<string, int> edgeIdx;

int dsuParent[N];
int subtreeSize[N];
void init(int n) {
    for (int i = 0; i < n; ++i) {
        dsuParent[i] = i;
        subtreeSize[i] = 1;
    }
}

// path compression
int root(int x) {
    return dsuParent[x] == x ? x : dsuParent[x] = root(dsuParent[x]);
}

void join(int x, int y) {
    x = root(x), y = root(y);
    if (x == y) return;

    if (subtreeSize[x] < subtreeSize[y]) {
        dsuParent[x] = y;
        subtreeSize[y] += subtreeSize[x]; 
    } else {
        dsuParent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }
    return;
}

// parent[u][k] = 2^k th parent of node u
int parent[N][20];
// maxEdge[u][k] = the maximum edge from node u, to the 2^k parent of u
ll maxEdge[N][20];

// log2s[i] holds the largest k such that 2^k <= i
int log2s[N];

void preprocess() {
    // log2s table
    log2s[0] = -1;
    log2s[1] = 0;
    for (int i = 2; i <= n; ++i) {
        log2s[i] = log2s[i/2] + 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; (1 << j) < n; ++j) {
            parent[i][j] = -1;
            maxEdge[i][j] = -1;
        }
    }

    // fill parent for each power of 2 up to n
    for (int j = 1; (1<<j) < n; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][j-1] != -1) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
                maxEdge[i][j] = max(maxEdge[i][j-1], maxEdge[parent[i][j-1]][j-1]);
            }
        }
    }
}

string tokenise(int u, int v) {
    if (u > v) swap(u,v);
    string s = to_string(u) + ' ' + to_string(v);
    return s;
}

bool seen[N];
int depth[N];

ll maxWeightInPath(int u, int v) {
    if (depth[u] < depth[v]) swap(u,v);

    ll currMaxEdge = -1;
    for (int i = log2s[depth[u]]; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            currMaxEdge = max(currMaxEdge, maxEdge[u][i]);
            u = parent[u][i];
        }
    }

    if (u == v) return currMaxEdge;
    for (int i = log2s[depth[u]]; i >= 0; i--) {
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            currMaxEdge = max(currMaxEdge, maxEdge[u][i]);
            currMaxEdge = max(currMaxEdge, maxEdge[v][i]);
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    currMaxEdge = max(currMaxEdge, maxEdge[u][0]);
    currMaxEdge = max(currMaxEdge, maxEdge[v][0]);

    return currMaxEdge;
}


void dfsMst(int u, int from = -1, int currDepth = 0) {
    if (u == -1) return;
    if (seen[u]) return;
    // cout << "node " << u << " from node " << from << endl;
    parent[u][0] = from;
    depth[u] = currDepth;
    if (from == -1) maxEdge[u][0] = -1;
    else {
        maxEdge[u][0] = edgeWeights[tokenise(u, from)];
    }
    seen[u] = true;
    for (int v : mstEdges[u]) {
        if (v == u) continue;
        dfsMst(v, u, currDepth + 1);
    }
}

void dfs(int u, int from, vector<ll> &res, vector<bool> &dfsSeen) {
    if (dfsSeen[u]) return;
    dfsSeen[u] = true;
    // explore every edge to vertices that are SEEN
    // this means it is a backedge, and therefore we can calculate the stuff
    for (int v : allEdges[u]) {
        // if parent, or 
        if (v == u || v == from || !dfsSeen[v]) {
            continue;   
        }
        // if we get to this point that means it is a backedge
        int currEdgeIdx = edgeIdx[tokenise(u, v)];
        ll maxMstPath = maxWeightInPath(u, v);
        res[currEdgeIdx] = totalWeight + (edgeWeights[tokenise(u, v)] - maxMstPath);
    }
    
    for (int v : mstEdges[u]) {
        if (v == u || v == from) continue;
        dfs(v, u, res, dfsSeen);
    }

}

int main(void) {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >>u>>v >>w;
        edges.push_back({u,v,w});
        allEdges[u].push_back(v);
        allEdges[v].push_back(u);
        edgeWeights[tokenise(u, v)] = w;
        edgeIdx[tokenise(u,v)] = i;
    }

    // sort edges in increasing weight
    sort(edges.begin(), edges.end(), [&](const edge e1, const edge e2) {
        return e1.w < e2.w;
    });
    int mstRoot = -1;
    init(n);
    for (int i = 0; i < m; ++i) {
        edge &e = edges[i];
        if (root(e.u) != root(e.v)) {
            if (mstRoot == -1) mstRoot = e.u;
            mstEdges[e.u].insert(e.v);
            mstEdges[e.v].insert(e.u);
            join(e.v, e.u);
            totalWeight += e.w;
        }
    }

    for (int i = 0; i < N; ++i) {
        seen[i] = false;
    }
    if (mstRoot == -1) return 0;

    // dfs through mstEdges, look for back edges
    // initialises the binary lift parent table, and maxEdges table
    dfsMst(mstRoot);
    preprocess();

    // now we can start querying
    // dfs through the tree, everytime we find a back edge e(u,v)
    // query for the max path between u and v and add the difference to total weight
    vector<ll> res(m + 1, totalWeight);
    vector<bool> dfsSeen(n + 1);
    for (int i = 0; i <= n; ++i) dfsSeen[i] = false;
    
    dfs(mstRoot, -1, res, dfsSeen);

    for (int i = 0; i < m; ++i) {
        cout << res[i] << endl;
    }

    return 0;
}

