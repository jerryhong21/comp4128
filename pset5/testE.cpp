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
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef pair<char, int> pci;
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define fork(n) for (int k = 0; k < n; k++)
#define for1i(n) for (int i = 1; i <= n; i++)
#define for1j(n) for (int j = 1; j <= n; j++)
#define for1k(n) for (int k = 1; k <= n; k++)


#define pb push_back

#define all(x) x.begin(), x.end()
#define sortAll(x) sort(all(x))

const int INF = INT_MAX;
// const int INF = (1LL << 16);

int n, m;
const int N = 505;
const int M = N * (N-1) / 2;
int edges[N][N], dist[N][N], numEdges[N][N];

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    cin >> n >> m;

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) {
                dist[u][u] = 0;
            }
            else {
                dist[u][v] = INF;
            }
            edges[u][v] = INF;
        }
    }

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        edges[u][v] = w;
        edges[v][u] = w;
        dist[v][u] = w;
        dist[u][v] = w;
    }

    // every vertex can reach itself
    for (int u = 0; u < n; ++u) dist[u][u] = 0;

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            numEdges[i][j] = 0;
        }
    }
    // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
    // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
    int count = 0;
    for (int s = 0; s < n; ++s) {
        // cout << s << " ";
        for (int t = 0; t < n; ++t) {
            // cout << t << " ";
            for (int interm = 0; interm < n; ++interm) {
                // if (interm == t) continue;
                if (edges[interm][t] != INF && dist[s][interm] + edges[interm][t] == dist[s][t]) {
                    numEdges[s][t]++;
                    count++;
                    // cout << "NumEdges[s][t] == " << numEdges[s][t] << endl; 
                }
            }
        }
    }
    cout << count << endl;
    
    fori(n)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int res = 0;
            fork(n)
            {
                if (dist[i][k] + dist[k][j] == dist[i][j])
                {
                    res += numEdges[i][k];
                }
            }
            cout << res << ' ';
        }
    }
    cout << endl;
    // create an inShortest array for all vertices
    // and for all edges and set them initially to false
    // for each edge check if either of the endpoints
    // e_0, e_1 are such that dist[s][e_i] + dist[e_i][t] = dist[s][t]
    // if so set inShortest[e] to true and inShortest[e_i]++

    // loop over every source and every destination (pair)
    // and for each of these pairs of source and destination
    // loop over every other vertex v to check if inShortest[v] is true
    // if it is true check all the
    return 0;
}