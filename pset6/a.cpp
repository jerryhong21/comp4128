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
 * Flow construction:
 * 
 * very cell is a vertex
 * an edge between every c1 and c2 iff: 
 * c1 and c2 are adjacent to each other
 * distance of c1 from center < distance of c2 from center
 * sink vertex t, with an infinite capacity edge to every cell on the outer edge
 * 
 * capacities:
 * c(c1->c2) = cost of c2 to barracade, inf if c2 is unbarracadable
 * 
 * implementation:
 * Use BFS to construct the flow network
 * Run dinics - if max flow >= INF, then return -1, otherwise return max flow
 */ 

const int N = 30, M = 30, C = 26;
int n,m,c;

char grid[M][N];
int cost[C];
int dist[N * M + 1];

int s;
int t;

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


/** (n = 5, m = 3)
 * 0  1  2  3  4
 * 5  6  7  8  9
 * 10 11 12 13 14
 */

int movementX[4] = {0, 0, 1, -1};
int movementY[4] = {1, -1, 0, 0};

// to check if on border, if node % n == 0 or (node + 1) % n == 0
int movement[4] = {5, -5, 1, -1};


int getNode(int x,int y) {
    return (n * y + x);
}


bool isBoundary(int v) {
    if (v < n) return true;
    if (v % n == 0 || (v + 1) % n == 0) return true;
    if (v > (n * (m - 1))) return true;
    return false;
}


void floodfill(int bx, int by) {
    // node nm + 1 = t

    // queue<pair<int, int>> q;
    // q.push({-1, s});
    queue<pair<int, int>> q;
    q.push({bx, by});
    dist[s] = 0;

    while (!q.empty()) {
        auto curr = q.front(); q.pop();
        int currX = curr.first, currY = curr.second;
        int currNode = getNode(currX, currY);

        for (int i = 0; i < 4; ++i) {
            int nx = currX + movementX[i];
            int ny = currY + movementY[i];
            if (nx >= n || nx < 0 || ny >= m || ny < 0) continue;
            int nxtNode = getNode(nx, ny);
            if (dist[nxtNode] != -1) continue;
            dist[nxtNode] = dist[currNode] + 1;

            q.push({nx, ny});
        }
    }

    // cout << "distances: \n"; 
    // for (int i = 0; i < m * n; ++i) {
    //     cout << dist[i] << ' ';
    //     if ((i + 1) % n == 0) cout << endl;
    // }

}

// void bfs(int bx, int by, FlowNetwork &flow) {
//     // node nm + 1 = t

//     // queue<pair<int, int>> q;
//     // q.push({-1, s});
//     queue<pair<int, int>> q;
//     q.push({bx, by});

//     vector<bool> seen(N * M + 1);

//     while (!q.empty()) {
//         auto curr = q.front(); q.pop();
//         int currX = curr.first, currY = curr.second;
//         int currNode = getNode(currX, currY);
//         if (isBoundary(currNode)) {
//             if (currNode == s) {
//                 flow.addEdge(s, t, INF);
//             } else {
//                 flow.addEdge(n * m + currNode, t, INF);
//             }
//             // cout << "Added edge between " << currNode << " to " << t << " with capacity " << INF << endl;
//         }
//         if (currNode != s) {
//             ll capacity = INF;
//             if (grid[currY][currX] != '.') {
//                 capacity = cost[grid[currY][currX] - 'a'];
//             }
//             flow.addEdge(currNode, n * m + currNode, capacity);
//             cout << "Added edge between " << currNode << " to " << n * m + currNode << " with capacity " << capacity << endl;
//         }

//         seen[currNode] = true;
//         cout << "currX = " << currX << " currY = " << currY << endl;
//         for (int i = 0; i < 4; ++i) {
//             int nx = currX + movementX[i];
//             int ny = currY + movementY[i];
//             if (nx >= n || nx < 0 || ny >= m || ny < 0) continue;
//             int nxtNode = getNode(nx, ny);
//             // if (dist[nxtNode] <= dist[currNode]) continue;

//             flow.addEdge(n * m + currNode, nxtNode, INF);

//             if (!seen[nxtNode]) {
//                 q.push({nx, ny});
//                 seen[nxtNode] = true; 
//             }
//         }
//         cout << endl;
//     }
// }

void buildFlow(FlowNetwork &flow)
{

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int currY = i, currX = j;
            int currIn = getNode(j, i);
            int currOut = currIn + n *m;
            if (s == currIn) currOut = currIn;

            if (currIn != s) {
                ll capacity = INF;
                if (grid[currY][currX] != '.') {
                    capacity = cost[grid[currY][currX] - 'a'];
                }
                flow.addEdge(currIn, currOut, capacity);
            }
            // if (isBoundary(currIn)) {
            //     if (currIn == s) {
            //         flow.addEdge(s, t, INF);
            //     }
            //     else {
            //         flow.addEdge(currIn, t, INF);
            //     }
            //     // cout << "Added edge between " << currNode << " to " << t << " with capacity " << INF << endl;
            // }
            for (int k = 0; k < 4; ++k) {
                int nx = currX + movementX[k];
                int ny = currY + movementY[k];
                if (nx >= n || nx < 0 || ny >= m || ny < 0) {
                    flow.addEdge(currOut, t, INF);
                } else {
                    int nxtIn = getNode(nx, ny);
                    flow.addEdge(currOut, nxtIn, INF);
                }
            }
        }
    }
}


int main(void) {

    cin >> n >> m >> c;
    int count = 0;
    t = 2*n*m;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'B') {
                s = getNode(j, i);
            }
        }
    }


    // in vertex = i
    // out vertex = n * m + i

    // s = whatever
    // t = 2*n*m
    FlowNetwork flow(n * m * 2 + 1);
    // cost[0] represents cost for a
    for (int i = 0; i < c; ++i) {
        cin >> cost[i];
    }
    
    // floodfill(bx, by);
    buildFlow(flow);

    ll res = flow.dinic(s, t);
    cout << ((res >= INF) ? -1 : res) << endl;

    return 0;
}
