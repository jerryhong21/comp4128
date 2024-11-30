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

const int N = 200010, M = 300020, K = 100010;

int n,m,k;

ll dist[N];
bool seen[N];

struct edge {
    int v;
    ll w;
    bool train;
    edge(int _v, ll _w, bool _train) : v(_v), w(_w), train(_train) {};
};
vector<edge> edges[N];


struct compareEdges {
    bool operator()(const edge& e1, const edge& e2) {
        if (e1.w != e2.w) {
            return e1.w > e2.w;
        }
        return e1.train > e2.train;
    }
};

priority_queue<edge, vector<edge>, compareEdges> pq;

int dijkstras() {
    fill(seen, seen+N, false);
    // distance to itself is zero
    // capital is 1
    pq.push(edge(1, 0, false));
    int routeSkipped = 0;
    while (!pq.empty()) {
        edge e = pq.top(); pq.pop();
        ll d = e.w; 
        int v = e.v;
        
        if (seen[v]) {
            if (e.train) {
                routeSkipped++;
            }
            continue;
        }

        dist[v] = d;
        seen[v] = true;

        // relax edges
        for (edge &nxt : edges[v]) {
            int u = nxt.v;
            ll weight = nxt.w;
            if (!seen[u]) {
                if (v == 1 && nxt.train) {
                    pq.push(edge(u, d + weight, true));
                } else {
                    pq.push(edge(u, d + weight, false));
                }
            }
        }
    }
    return routeSkipped;
}

// keep a set of vertices covered
int main(void) {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int u,v;
        ll x;
        cin >> u >> v >> x;
        edges[u].emplace_back(v, x, false);
        edges[v].emplace_back(u, x, false);
    }

    for (int i = 1; i <= k; ++i) {
        int s;
        ll y;
        cin >> s >> y;
        edges[1].emplace_back(s, y, true);
        edges[s].emplace_back(1, y, true);
    }

    // run dijkstras
    int res = dijkstras();

    cout << res << endl;

    return 0;
}
