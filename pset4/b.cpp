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

int n;
vector<int> edges[100005];

int dfs(int v, int parent) {
    // cout << "at vertex " << v << " with parent " << parent << endl;
    if (edges[v][0] == parent && edges[v].size() == 1) return v;
    if (edges[v].size() > 2) return -1;
    for (int u : edges[v]) {
        // cout << "Examining neightbour " << u << " of vertex " << v << endl;
        if (u == v || u == parent) continue;
        return dfs(u, v);
    }
}


// keep a set of vertices covered
int main(void)
{
    cin>>n;
    int maxV = -1;

    int degrees[n + 1];
    for (int i = 1; i <=n ; ++i) {
        degrees[i] = 0;
    }
    int currMaxDegree = 0;
    int currMaxDegreeV = 1;
    for (int i =0; i < (n-1); ++i) {
        int u, v;
        cin>>u>>v;
        edges[u].push_back(v);
        edges[v].push_back(u);
        degrees[u]++;
        degrees[v]++;
        if (degrees[u] > currMaxDegree) {
            currMaxDegreeV = u;
            currMaxDegree = degrees[u];
        } else if (degrees[v] > currMaxDegree) {
            currMaxDegreeV = v;
            currMaxDegree = degrees[v];
        }
    }

    // cout << "Max vertex is " << currMaxDegreeV << endl;


    // dfs from every nighbour of v, if there exists divergent paths
    vector<pair<int, int>> res;
    for (int neighbor : edges[currMaxDegreeV]) {
        // cout << "Exploring neighbour " << neighbor << endl;
        int endV = dfs(neighbor, currMaxDegreeV);
        if (endV == -1) {
            cout << "No\n";
            return 0;
        }
        res.push_back(make_pair(currMaxDegreeV, endV));
    }
    cout << "Yes\n";
    cout << res.size() << "\n";
    for (int i =0; i < res.size(); ++i) {
        cout << res[i].first << " " << res[i].second << endl;
    }

    return 0;
}
