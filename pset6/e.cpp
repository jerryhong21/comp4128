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
#include <cstring>

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
 * Algorithm:
 * 
 * For every t, find out whether a,b can reach x,y
 * Keep track of the status of the maze time t using dfs
 * In the flow network, connect an edge from a,b to x,y iff reachability = true for t
 * 
 * reach[t][a][b][x][y] checks for whether you can go from (a,b) to (x,y) in t time
 * this is done by a dfs that keeps track of allowed time
 * 
 */

int n,t;

const int N = 15, T = 65;

// mazeState[t][x][y] describes state of (x,y) at time t
int mazeState[T][N][N];
int ppl[N][N], pods[N][N];
bool seen[N][N];
bool reachable[T][N][N][N][N];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

// flood fill from the maze
void fillMazeState() {

    for (int i = 1; i <= t; ++i) {
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                // if the maze is a safe reactor
                if (mazeState[i - 1][x][y]) {
                    mazeState[i][x][y] = mazeState[i - 1][x][y];
                } else {
                    // if the maze is a lab or affected
                    // check the surroundings for affected
                    for (int dir = 0; dir < 4; ++dir) {
                        int nx = x + dx[dir], ny = y + dy[dir];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                        if (mazeState[i-1][nx][ny] == 2) {
                            mazeState[i][x][y] = 2;
                        }
                    }
                }
            }
        }
    }
}

// compute if a,b can reach x,y
void dfsReachable(int a, int b, int x, int y, int time) {
    seen[x][y] = true;
    reachable[time][a][b][x][y] = true;
    if (time >= t || mazeState[time][x][y] != 0) return;

    for (int i = 0; i < 4; ++i){
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        // if visited, continue
        if (seen[nx][ny]) continue;
        // if maze cannot is unavailable
        if (mazeState[time][nx][ny] == 0) {
            dfsReachable(a, b, nx, ny, time + 1);
        }

    }

}

void computeReachability() {

    // perform dfs from each scientist
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (ppl[x][y] != 0) {
                memset(seen, false, sizeof(seen));
                dfsReachable(x,y,x,y,0);
            }
        } 
    }

    // recalibrate reachability
    for (int i = 1; i <= t; ++i) {
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                for (int x = 0; x < n; ++x) {
                    for (int y = 0; y < n; ++y) {
                        reachable[i][a][b][x][y] |= reachable[i-1][a][b][x][y];
                    }
                }
            }
        }
    }

}

// 0 1 2 3
// 4 5 6 7
int getId(int x, int y, int k) {
    return x * n + y + k * n*n;
}

void init() {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ppl[i][j] = 0;
            pods[i][j] = 0;
            // cout << "x = " << x << " y = " << y << " id = " << getId(x,y)
            // cout << getId(i,j) << ' ';
        }
        // cout << endl;
    }

}

int main(void) {

    cin >> n >> t;

    memset(ppl, 0, sizeof(ppl));
    memset(pods, 0, sizeof(pods));
    memset(seen, false, sizeof(seen));
    memset(mazeState, 0, sizeof(mazeState));
    memset(reachable, false, sizeof(reachable));

    init();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char cur; 
            cin >> cur;
            if (cur >= '0' && cur <= '9') {
                ppl[i][j] = cur - '0';
            } else if (cur == 'Y') {
                mazeState[0][i][j] = 1;
            } else if (cur == 'Z') {
                mazeState[0][i][j] = 2;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char cur;
            cin >> cur;
            if (cur >= '0' && cur <= '9') {
                pods[i][j] = cur - '0';
            }
        }
    }

    fillMazeState();
    computeReachability();

    // construct the flow network
    // 0->n^2 - 1 = nodes
    const int NODES = 210;
    int src = NODES - 1; int sink = NODES - 2;
    FlowNetwork flow(NODES);

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (ppl[x][y] != 0) {
                flow.addEdge(src, getId(x,y,0), ppl[x][y]);
                // cout << "added edge from source to " << getId(x, y, 0) <<  " of capcaicty " << ppl[x][y] << endl;
            }
            if (pods[x][y] != 0) {
                flow.addEdge(getId(x, y, 1), sink, pods[x][y]);
                // cout << "added edge from " << getId(x, y, 1) << " to sink of capcaicty " << pods[x][y] << endl;
           }
        }
    }

    // add an edge of inf capacity between every cell with scientist, and cell with pod, and reachable
    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < n; ++y) {
                    if (ppl[a][b] != 0 && pods[x][y] != 0 && reachable[t][a][b][x][y]) {
                        flow.addEdge(getId(a,b,0), getId(x,y,1), INF);
                        // cout << "added edge from " << getId(a, b, 0) << " to " << getId(x, y, 1) << endl;
                    }
                }
            }
        }
    }

    cout << flow.dinic(src, sink) << endl;

    return 0;
}

