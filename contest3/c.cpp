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

// const ll INF = (1LL << 59);
ll INF = (1LL << 30);
// const int INF = 1e9;


const int N = 3010, M = 3010;

int s;
int t;

int n,m;

struct FlowNetwork {

    int n;
    vector<vector<ll>> adjMat, adjList;
    vector<vector<bool>> isVirtual;
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n) {
        adjMat.resize(n);
        isVirtual.resize(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            adjMat[i].resize(n);
        }
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void addEdge(int u, int v, ll c) {
        adjMat[u][v] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        isVirtual[v][u] = true;
    }

    void flowEdge(int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    // this constructs the level graph and returns whether sink is still reachable
    bool constructLevelGraph(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0;
            for (int v : adjList[u]) {
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    ll augment(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            if (adjMat[u][v] > 0) {
                // ignoring edges not in bfs tree
                if (level[v] != level[u] + 1) continue;
                ll revisedFlow = augment(v, t, min(f, adjMat[u][v]));
                if (revisedFlow > 0) {
                    flowEdge(u, v, revisedFlow);
                    return revisedFlow;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    ll dinic(int s, int t) {
        ll res = 0;
        while (constructLevelGraph(s, t)) {
            for (ll x = augment(s,t,INF); x; x = augment(s,t,INF)) {
                res += x;
            }
        }
        return res;
    }
};

int main(void) {
    cin >> n >> m;
    FlowNetwork flow(n + 1);
    int targetC = 0;
    for (int i = 0; i < m; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        if (i == 0) {
            s = a;
            t = b;
            targetC = c;
            continue;
        }
        if (c <= targetC) {
            flow.addEdge(a,b,1);
            flow.addEdge(b,a,1);
        }
    }
    ll maxFlow = flow.dinic(s,t);
    cout << maxFlow << endl;
    // cout << flow.min_cut(s, t).size() << endl; 


    return 0;
}
