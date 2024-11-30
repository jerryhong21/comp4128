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

const ll INF = (1LL << 59);
// const int INF = (1LL << 30);
// const int INF = 1e9;

int n;

//To solve the problem, you need to have a good understanding of the principle of operation of the Floyd algorithm. General view of Floyd's algorithm: for (k=1;k<=n;k++) for (i=1;i<=n;i++) for (j=1;j<=n;j++) a[i][j] = min(a[i][j], a[i][k]+a[k][j]); That is, at each step we try to pass the path through vertex K. We will not delete vertices, but add them (coming from the end). At each step we will try to pass the path between all vertices through a new one. This way we get a solution that works in cubic time.


const int N = 505;

ll matrix[N][N];

ll dist[N][N];



// keep a set of vertices covered
int main(void) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j =1 ;j <=n; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<int> deleted(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> deleted[n + 1 - i];
    }

    // deleted[1] stores the first vertex that will be considered
    vector<ll> res(n+1);

    // initialise distance matrix
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (u == v) dist[u][v] = 0;
            else dist[u][v] = INF;
        }
    }

    // for every new vertex added, we add their distance to each other

    vector<int> vertices;
    unordered_set<int> present;
    for (int it = 1; it <= n; ++it) {
        // the kth vertex is 
        int k = deleted[it];
        cout << "restored vertex " << k << endl;
        vertices.push_back(k);
        present.insert(k);

        for (int u = 1; u <= n; ++u) {
            // if (present.find(u) != present.end() && k != u) {
                dist[k][u] = min(dist[k][u], matrix[k][u]);
                dist[u][k] = min(dist[u][k], matrix[u][k]);
            // }
        }

        dist[k][k] = 0;


        // accounts for K being the intermeidary vertex
        for (int u = 1; u <= n; ++u) {
            if (present.find(u) == present.end()) continue;
            int uMap = deleted[u];
            for (int v = 1; v <=n; ++v) {
                int vMap = deleted[v];
                if (present.find(vMap) == present.end()) continue;
                if (vMap == uMap) continue;
                dist[uMap][vMap] = min(dist[uMap][vMap], dist[uMap][k] + dist[k][vMap]);
                cout << "set dist[" << uMap << "][" << vMap << "] to " << dist[uMap][vMap] <<endl;
            }
        }

        // need to find shortest distance from every other thing to k
        for (int u = 1; u <=n;++u) {
            // if (present.find(u) == present.end()) continue;
            for (int v = 1; v <=n; ++v) {
                // if (present.find(v) == present.end()) continue;
                if (v == u) continue;
                dist[v][k] = min(dist[v][k], dist[v][u] + dist[u][k]);
                dist[k][v] = min(dist[k][v], dist[k][u] + dist[u][v]);
            }
        }

        cout << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <=n; ++j) {
                cout << dist[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;

        // find every pair
        ll total = 0;
        for (int i = 1; i <=n; ++i) {
            for (int j = 1; j <= n;++j) {
                if (i == j) continue;
                
                if (present.find(j) == present.end()) continue;
                if (present.find(i) == present.end()) continue;

                if (dist[i][j] < INF) {
                    total += dist[i][j];
                    // cout << "total = " << total << endl;
                }
            }
        }

        res[it] = total;
        cout << "set total of iteration " << it << " to " << total << endl << endl;        

    }
    for (int i = n; i > 0; --i) {
        cout << res[i] << ' ';
    }
    cout << endl;

    return 0;
}
