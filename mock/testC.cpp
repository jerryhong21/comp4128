#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1LL << 60; // Corrected INF definition

struct Edge
{
    int to, rev;
    ll cap;
};

class MaxFlow
{
public:
    MaxFlow(int N) : N(N)
    {
        graph.resize(N);
        level.resize(N);
        iter.resize(N);
    }

    void add_edge(int from, int to, ll cap)
    {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0});
    }

    ll max_flow(int s, int t)
    {
        ll flow = 0;
        while (true)
        {
            bfs(s);
            if (level[t] < 0)
                break;
            fill(iter.begin(), iter.end(), 0);
            ll f;
            while ((f = dfs(s, t, INF)) > 0)
            {
                flow += f;
            }
        }
        return flow;
    }

private:
    int N;
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iter;

    void bfs(int s)
    {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty())
        {
            int v = que.front();
            que.pop();
            for (Edge &e : graph[v])
            {
                if (e.cap > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    ll dfs(int v, int t, ll upTo)
    {
        if (v == t)
            return upTo;
        for (int &i = iter[v]; i < (int)graph[v].size(); ++i)
        {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to])
            {
                ll d = dfs(e.to, t, min(upTo, e.cap));
                if (d > 0)
                {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

int main()
{
    int l, w, h, a, b, c, n;
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

    auto get_in_id = [&](int x, int y, int z)
    {
        tuple<char, int, int, int> key = make_tuple('i', x, y, z);
        if (node_id.find(key) == node_id.end())
        {
            node_id[key] = id_counter++;
        }
        return node_id[key];
    };

    auto get_out_id = [&](int x, int y, int z)
    {
        tuple<char, int, int, int> key = make_tuple('o', x, y, z);
        if (node_id.find(key) == node_id.end())
        {
            node_id[key] = id_counter++;
        }
        return node_id[key];
    };

    int S = id_counter++;
    int T = id_counter++;

    MaxFlow mf(id_counter);

    for (int x = 0; x < l; ++x)
    {
        for (int y = 0; y < w; ++y)
        {
            for (int z = 0; z < h; ++z)
            {
                int in_id = get_in_id(x, y, z);
                int out_id = get_out_id(x, y, z);
                // Connect in-node to out-node with infinite capacity
                mf.add_edge(in_id, out_id, INF);

                // If this cell contains a parcel, connect S to in-node
                if (parcels.count(make_tuple(x, y, z)))
                {
                    mf.add_edge(S, in_id, INF);
                }

                // For each neighbor, connect out-node to neighbor's in-node
                vector<tuple<int, int, int, ll>> dirs = {
                    {-1, 0, 0, a}, {1, 0, 0, a}, {0, -1, 0, b}, {0, 1, 0, b}, {0, 0, -1, c}, {0, 0, 1, c}};

                for (auto &dir : dirs)
                {
                    int dx, dy, dz;
                    ll cost;
                    tie(dx, dy, dz, cost) = dir;
                    int nx = x + dx, ny = y + dy, nz = z + dz;
                    if (0 <= nx && nx < l && 0 <= ny && ny < w && 0 <= nz && nz < h)
                    {
                        int neighbor_in_id = get_in_id(nx, ny, nz);
                        // Edge from out-node to neighbor's in-node with capacity equal to cost
                        mf.add_edge(out_id, neighbor_in_id, cost);
                    }
                    else
                    {
                        // Cell is adjacent to a wall, connect out-node to T with capacity equal to cost
                        mf.add_edge(out_id, T, cost);
                    }
                }
            }
        }
    }

    ll result = mf.max_flow(S, T);
    cout << result << endl;

    return 0;
}
