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

bool seen[N];
bool active[N];

vector<int> edges[M];
set<pair<int, int>> seenEdges;

struct color
{
    int u;
    int v;
    int c;
};

bool secondColor = false;

vector<color> coloring;

void dfs(int u, int fromColor)
{
    if (seen[u]) return;
    seen[u] = active[u] = true;
    // cout << "At vertex " << u << endl;
    
    for (int v : edges[u]) {
        // if (seenEdges.find(make_pair(u,v)) != seenEdges.end()) {
        //     continue;
        // }
        if (active[v]) { 
            // cout << u << " to "  << v << " is detected to be a cycle\n";
            // fromColor = (fromColor % 2) + 1;
            secondColor = true;
            // coloring.push_back({u, v, fromColor});
            coloring.push_back({u, v, 2});
            // seenEdges.insert(make_pair(u, v));
        } else {
            // coloring.push_back({u,v,fromColor});
            coloring.push_back({u,v,1});
            // seenEdges.insert(make_pair(u, v));
            dfs(v, fromColor);
        }

    }
    active[u] = false;
}

string tokenise(int u, int v)
{
    string s = "";
    s += to_string(u);
    s += ' ';
    s += to_string(v);
    // cout << s << endl;
    return s;
}

int main(void)
{

    cin >> n >> m;
    // bool seen[n+1], active[n+1];

    // convert uv into string 'uv'
    // store its index

    unordered_map<string, int> edgeIndex;
    // unordered_map<string, vector<inr>> edgeIndex;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edgeIndex[tokenise(u, v)] = i;
    }
    
    for (int i = 1; i <=n;++i) {
        seen[i] = active[i] = false;
    }
    for (int v = 1; v <= n; ++v) {
        if (!seen[v]) {
            dfs(v, 1);
        }
    }
    // dfs from every vertex if that vertex is not seen
    vector<int> res(m);
    for (auto c : coloring) {
        int idx = edgeIndex[tokenise(c.u, c.v)];
        res[idx - 1] = c.c;
    }
    cout << (secondColor ? 2 : 1) << endl;
    for (int i = 0; i < m; ++i) {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}
