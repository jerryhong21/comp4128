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

/**
 * 
 * every hero is one node -> connect to a monster node if monster is in set M_i
 * source connects to every hero with capacity 1
 * every potion is a node, source connects to every potion with capacity 1
 * every potion connects to every hero with capacity 1
 *  
 */

const int N = 500, M = 500, K = 500;
int n,m,k;

struct FlowNetwork {

    int n;
    vector<vector<ll>> adjMat, adjList;
    vector<int> level, uptochild;

    FlowNetwork(int _n) : n(_n) {
        adjMat.resize(n);
        for (int i = 0; i < n; ++i) {
            adjMat[i].resize(n);
        }
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void addEdge(int u, int v, ll c) {
        if (adjMat[u][v] == 0) {
            adjMat[u][v] += c;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
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

    // 1->m = monster
    // m + 1 -> m + n = hero_in
    // m + n + 1 -> m + 2n = hero_out
    // m + 2n + 1 -> m + 2n + k = potion
    cin >> n >> m >> k;
    FlowNetwork flow(2*n + m + k + 3);

    int s = 2*n + m + k + 1;
    int t = 2*n + m + k + 2;
    
    for (int i = 1; i <= n; ++i) {
        int monsters;
        cin >> monsters;
        int heroIn = m + i;
        int heroOut = m + n + i;
        
        flow.addEdge(heroIn, heroOut, 2);
        flow.addEdge(s, heroIn, 1);

        for (int j = 0; j < monsters; ++j) {
            int currMonster;
            cin >> currMonster;
            flow.addEdge(heroOut, currMonster, 1);
        }
        
        // connect all potion to hero with 1
        for (int p = 1; p <= k; ++p) {
            // add edge from potion to hero
            flow.addEdge(2*n + m + p, heroIn, 1);
        }
    }
    
    // connect source to every potion and every monster
    for (int p = 1; p <= k; ++p) {
        flow.addEdge(s, 2*n + m + p, 1);
    }

    for (int i = 1; i <= m; ++i) {
        flow.addEdge(i, t, 1);
    }

    cout << flow.dinic(s,t) << endl;

    return 0;
}

