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

const int N = 505;


ll dist[N][N];

// keep a set of vertices covered
int main(void) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j =1 ;j <=n; ++j) {
            cin >> dist[i][j];
        }
    }

    vector<int> deleted(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> deleted[n + 1 - i];
    }

    vector<ll> res;

    bool seen[N];
    fill(seen, seen+ N, false);
    
    for (int it = 1; it <= n; ++it) {
        int k = deleted[it];
        ll total = 0;
        seen[k] = true;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
                if (seen[u] && seen[v]) {
                    total += dist[u][v];
                }
            }
        }
        res.push_back(total);
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << res[i] << ' ';
    }
    cout << endl;

    return 0;
}
