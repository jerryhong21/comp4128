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

ll n, m;

struct edge {
    ll a; // from person
    ll b; // to person
    ll c; // weight
};

const int N = 10100;

ll parent[N];
ll subtreeSize[N];

void init(ll n) {
    for (int i = 1; i <= n;++i) {
        parent[i] = i;
        subtreeSize[i] = 1;
    }
}

ll root(ll x) {
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(ll x, ll y) {
    x = root(x); y = root(y);
    if (x == y) return;

    if (subtreeSize[x] < subtreeSize[y]) {
        parent[x] = y;
        subtreeSize[y] += subtreeSize[x];
    } else {
        parent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }
}



// keep a set of vertices covered
int main(void)
{
    cin  >> n;
    ll q[n + 1];
    for (ll i = 1; i <= n; ++i) {
        cin >> q[i];
    }
    cin >> m;
    vector<edge> edges;
    for (int i = 0 ;i < m; ++i) {
        ll a,b,c;
        cin >> a>>b>>c;
        edge newedge {a,b,c};
        edges.push_back(newedge);
    }

    // sort edges in decrasing ability, then increasing weight
    sort(edges.begin(), edges.end(), [&](const edge &a1, const edge &a2) {
        return a1.c < a2.c;
    });

    ll res = 0;
    ll parentEmployee[n + 1];
    for (int i = 1; i <= n; ++i) {
        parentEmployee[i] = -1;
    }

    init(n);
    ll maxSize = 1;
    ll nEdges = 0;
    for (int i = 0; i < m; ++i) {
        edge& e = edges[i];
        // cout << "at edge u = " << e.a << " v = " << e.b << " with weight " << e.c << endl;

        if (root(e.a) != root(e.b) && parentEmployee[e.b] == -1) {
            res += e.c;
            nEdges++;
            join(e.a, e.b);
            // cout << "joined edges " << e.a << " and " << e.b << endl;
            maxSize = max(maxSize, subtreeSize[root(e.a)]);
            // cout << "maxSize = " << maxSize << endl;
            // a is b's parent
            parentEmployee[e.b] = e.a;
            if (maxSize == n) break;
            // if (nEdges == (n-1)) break;
        } 
    }

    // if (nEdges == n-1) cout << res << endl;
    // else cout << -1 << endl;

    if (maxSize == n) cout << res << endl;
    else cout << -1 << endl;

    return 0;
}
