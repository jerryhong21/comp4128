#include <vector>
#include <cmath>
#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <iomanip>

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
// const ll INF = (1LL << 30);
// const int INF = 1e9;
// const int N = 600, K = 100;

int movementX[4] = {1, -1, 0, 0};
int movementY[4] = {0, 0, 1, -1};

struct FlowNetwork
{

    int n;
    vector<vector<ll>> adjMat, adjList;
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n)
    {
        adjMat.resize(n);
        for (int i = 0; i < n; ++i)
        {
            adjMat[i].resize(n);
        }
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void addEdge(int u, int v, ll c)
    {
        if (adjMat[u][v] == 0)
        {
            adjMat[u][v] += c;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    void flowEdge(int u, int v, ll c)
    {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    // this constructs the level graph and returns whether sink is still reachable
    bool constructLevelGraph(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            uptochild[u] = 0;
            for (int v : adjList[u])
            {
                if (adjMat[u][v] > 0)
                {
                    if (level[v] != -1)
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    ll augment(int u, int t, ll f)
    {
        if (u == t)
            return f;
        for (int &i = uptochild[u]; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0)
            {
                // ignoring edges not in bfs tree
                if (level[v] != level[u] + 1)
                    continue;
                ll revisedFlow = augment(v, t, min(f, adjMat[u][v]));
                if (revisedFlow > 0)
                {
                    flowEdge(u, v, revisedFlow);
                    return revisedFlow;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    ll dinic(int s, int t)
    {
        ll res = 0;
        while (constructLevelGraph(s, t))
        {
            for (ll x = augment(s, t, INF); x; x = augment(s, t, INF))
            {
                res += x;
            }
        }
        return res;
    }
};

/**
 * Binary search for the maximum weight able to send
 *
 * The problem now becomes: How to determine if its possible to have a valid maximum weight
 * There needs to be x path of maxWeight / x -> we call this d
 * we can change the capacity of all edges to the nearest largest factor of
 */
int n,m,x;
const int N = 55;
const int M = 505;
const int X = 100005;
const long double EPS = 1e-11;

// edges[u] = {v, w}
vector<pair<int, ll>> edges[N];

// void testFlow() {
//     FlowNetwork f = FlowNetwork(5);
//     f.addEdge(1, 2, 2);
//     f.addEdge(1, 3, 2);
//     f.addEdge(2, 4, 1);
//     f.addEdge(3, 4, 1);
//     // cout << "maxflow is " << f.dinic(1,4) << endl;
// }


bool canFlow(long double d) {
    // construct flow network such that every edge capacity is the largest possible integer mulitple to w
    FlowNetwork flow = FlowNetwork(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (auto &edge : edges[u]) {
            ll multiple = floor(edge.second / d);
            if (multiple <= 0) continue;
            flow.addEdge(u, edge.first, multiple);
            // cout << "Added edge between " << u << " to " << edge.first << " with weight "  << multiple << endl;
        }
    }
    ll maxFlow = flow.dinic(1, n);
    return maxFlow >= x;
}

int main(void) {
    // testFlow();
    cin >> n >> m >> x;
    ll maxW = 0;
    for (int i = 1; i <=m; ++i) {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        maxW = max(maxW, w);
        edges[u].push_back({v, w});
    }

    // maximum possible flow to be carried is maxW * x
    // double l = 0, h = maxW * x;
    long double l = 0, h = 1e9;
    ll lastAnswer = -1;
    for (int i = 0; i < 100; ++i) {
        long double mid = (l + h) / 2;

        if (canFlow(mid)) {
            lastAnswer = mid;
            l = mid;
        } else {
            h = mid;
        }
    }

    if (lastAnswer == -1) {
        cout << "Sumting wong\n";
        return 0;
    }
    
    // maybe specify decimal place accuracy
    cout << fixed << setprecision(10) << l * x << endl;

    return 0;
}
