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

const int N = 600, K = 100;

int movementX[4] = {1,-1,0,0};
int movementY[4] = {0,0,1,-1};

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

int solveCase() {
    int n;
    cin >> n;
    bool grid[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char curr;
            cin >> curr;
            if (curr == '.') grid[i][j] = false;
            else grid[i][j] = true;
        }
    }

    FlowNetwork flow(2 * n * n + 3);
    // 1->n^2 = left side
    // n^2 + 1 -> 2n^2 = right side
    // 2n^2 + 1 = s
    // 2n^2 + 2 = t
    int s = 2*n*n+1;
    int t = 2*n*n+2;
    int currCell = 1;
    // white cell on s side
    // black cell on t side
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!grid[i][j]) {
                currCell++;
                continue;
            }
            bool currCellWhite = ((i + j) % 2 == 0);
            // for each cell, connect with every neighbouring cell
            if (currCellWhite) {
                flow.addEdge(s, currCell, 1);
                for (int k = 0; k < 4; ++k) {
                    int dx = j + movementX[k];
                    int dy = i + movementY[k];
                    if (dx == -1 || dy == -1 || dy == n || dx == n) continue;
                    if (!grid[dy][dx]) continue;
                    // add edge from currCell from s side to neighbour cell of t side
                    int neighbour = dy * n + dx + 1;
                    flow.addEdge(currCell, neighbour, 1);
                }
            } else {
                flow.addEdge(currCell, t, 1);
            }
            currCell++;
        }
    }
    return flow.dinic(s, t);
}

int main(void) {
    int k;
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        cout << "Case " << i << ": " << solveCase() << endl;
    }    
    return 0;
}
