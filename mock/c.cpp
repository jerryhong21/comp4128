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
using namespace std;
typedef long long ll;
const ll INF = (1LL << 59);
// const ll INF = (1LL << 30);
// const int INF = 1e9;


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



void printCoord(int x, int y, int z) {
    cout << x << " " << y << " " << z;
}

int main(void) {

    int l, w, h, n;
    ll a, b, c;
    cin >> l >> w >> h >> a >> b >> c >> n;

    set<tuple<int, int, int>> parcels;
    for (int i = 0; i < n; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        parcels.insert(make_tuple(x, y, z));
    }

    map<tuple<char, int, int, int>, int> node_id;
    int id_counter = 0;

    auto getId = [&](int x, int y, int z)
    {
        tuple<char, int, int, int> key = make_tuple('i', x, y, z);
        if (node_id.find(key) == node_id.end())
        {
            node_id[key] = id_counter++;
        }
        return node_id[key];
    };

    int S = (l + 1) * (w + 1) * (h + 1) + 10;
    int T = T + 1;

    FlowNetwork mf(S + 15);

    for (int x = 0; x < l; ++x) {
        for (int y = 0; y < w; ++y) {
            for (int z = 0; z < h; ++z) {
                int in_id = getId(x, y, z);
                // If this cell contains a parcel, connect S to in-node
                if (parcels.count(make_tuple(x, y, z))) {
                    mf.addEdge(S, in_id, INF);
                }

                // For each neighbor, connect out-node to neighbor's in-node
                vector<tuple<int, int, int, ll>> dirs = {
                    {-1, 0, 0, a}, {1, 0, 0, a}, {0, -1, 0, b}, {0, 1, 0, b}, {0, 0, -1, c}, {0, 0, 1, c}};

                for (auto &dir : dirs) {
                    auto [dx, dy, dz, cost] = dir;
                    int nx = x + dx, ny = y + dy, nz = z + dz;
                    int neighbour_id = getId(nx, ny, nz);

                    if (nx < 0 || nx >= l || ny < 0 || ny >= w || nz < 0 || nz >= h) {
                        mf.addEdge(neighbour_id, T, INF);
                    }

                    mf.addEdge(in_id, neighbour_id, cost);
                }
            }
        }
    }

    ll result = mf.dinic(S, T);
    cout << result << endl;

    return 0;
}

