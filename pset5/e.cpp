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

// const ll INF = (1LL << 61);
const int INF = (1LL << 30);
// const int INF = 1e9;


#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()



/*

Algorithm:

1. Run FW
2. Iterate through each source vertex, and each dest vertex. Look at each incoming vertex of the dest vertex and see if that vertex is in the shortest path
3. Go through each pair of source and dest vertex, and iterate through all intermediate vertices. if it is intermediate vertex then add count
*/


const int N = 510;
const int M = N*(N-1) / 2 + 10;
ll dist[N][N];
ll edges[N][N];

int n,m;
int main(void) {

    cin >> n >> m;

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) {
                dist[u][u] = 0;
            } else {
                dist[u][v] = INF;
            }
            edges[u][v] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int u,v,w;
        cin >> u >> v >> w;
        --u; --v;
        dist[u][v] = w;
        dist[v][u] = w;
        edges[u][v] = w;
        edges[v][u] = w;
    }

    // FW
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }
    
    // vector<ll> inDeg(vector<ll>(n,0));
    ll inDeg[n][n];
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inDeg[i][j] = 0;
        }
    }

    // for each source vertex and each dest vertex
    int count = 0;
    for (int s = 0; s < n; ++s) {
        for (int d = 0; d < n; ++d) {
            // loop through every possible neighbour of dest
            for (int i = 0; i < n; ++i) {
                // if (i == d) continue;
                if (edges[i][d] != INF && dist[s][d] == dist[s][i] + edges[i][d]) {
                    count++;
                    inDeg[s][d]++;
                }
            }
        }
    }
    cout << count << endl;

    // do a traversal of every pair, for every intermediate vertex in a shortest path, we count its degrees
    for (int s = 0; s < n; ++s) {
        for (int d = s + 1; d < n; ++d) {
            ll ans = 0;
            for (int i = 0 ; i < n; ++i) {
                if (dist[s][d] == dist[s][i] + dist[i][d]) {
                    ans += inDeg[s][i];
                }
            }
            cout << ans << " ";
        }
    }

    cout << endl;
    return 0;
}
