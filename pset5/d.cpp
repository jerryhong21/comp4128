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
    const ll INF = (1LL << 30);
    // const int INF = 1e9;

    int n, m, s, t;
    ll L;
    typedef pair<ll, int> edge;

    const int N = 1010;
    vector<edge> edges[N];

    string tokenise(int u, int v) {
        if (u > v) swap(u,v);
        return to_string(u) + " " + to_string(v);
    }

    unordered_set<string> erasedEdges;
    /*
        Algorithm:
        Determine possibility
        1. make every erased edge to weight 1 and run dijkstras, if shortest path > L then impossible
        2. treat every erased edge to infinity, if shortest path < L then also impossible
    */

    bool seen[N];
    int pred[N];
    ll dist[N];

    void reset() {
        for (int i = 0; i <= n + 1; ++i) {
            seen[i] = false;
            dist[i] = INF;
            pred[i] = -1;
        }
    }

    void dijkstrasPossible(int s, ll erasedWeight) {
        reset();
        priority_queue<edge, vector<edge>, greater<edge>> pq;
        fill(seen, seen + N,  false);
        pq.push(edge(0, s));
        while (!pq.empty()) {
            edge cur = pq.top(); pq.pop();
            int v = cur.second;
            ll d = cur.first;
            if (seen[v]) continue;
            
            dist[v] = d;
            seen[v] = true;

            for (edge &nxt : edges[v]) {
                int u = nxt.second;
                if (v == u) continue;
                ll w = nxt.first;
                if (w == 0) w = erasedWeight;
                if (!seen[u]) {
                    pq.push(edge(d + w, u));
                }
            }
        }
    }

    // returns an edge 
    ll shortestPath() {
        reset();
        priority_queue<edge, vector<edge>, greater<edge>> pq;
        pq.push(edge(0, s));
        dist[s] = 0;
        // printPred();

        while (!pq.empty() && !seen[t]) {

            edge cur = pq.top(); pq.pop();
            int v = cur.second;
            ll d = cur.first;
            if (seen[v]) continue;
            seen[v] = true;
            for (edge nxt : edges[v]) {
                int u = nxt.second;
                ll w = nxt.first;
                if (seen[u]) continue;
                if (v == u) continue;
                if (dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;
                    pq.push(edge(dist[u], u));
                    pred[u] = v;
                }
            }
        }

        ll shortest = dist[t];
        // back track from t, find an erased edge and set it to L
        if (shortest == L) {
            return shortest;
        }

        // find edge u->v
        int curr = t;
        int u = -1, v = -1;
        while (curr != s) {
            int parent = curr;
            curr = pred[parent];
            // edge is curr -> parent
            string currEdge = tokenise(curr, parent);
            if (erasedEdges.find(currEdge) != erasedEdges.end()) {
                u = curr, v = parent;
                break;
            }
        }
        if (u == -1) return shortest;
        ll newWeight = L - shortest + 1;

        for (edge &e : edges[u]) {
            if (e.second == v) {
                e.first = newWeight;
            }
        }
        for (edge &e : edges[v]) {
            if (e.second == u) {
                e.first = newWeight;
            }
        }
        return shortest;
    }

    struct edgeRes {
        int u;
        int v;
        ll w;
        edgeRes(int _u, int _v,ll _w) : u(_u), v(_v), w(_w) {} 
    };

    // keep a set of vertices covered
    int main(void) {
        cin >> n >> m >> L>>s>>t;
        for (int i = 0; i < m; ++i) {
            int u,v;
            ll w;
            cin >> u >> v >> w;
            edges[u].push_back({w, v});
            edges[v].push_back({w, u});
            if (w == 0) erasedEdges.insert(tokenise(u,v));
        }

        dijkstrasPossible(s, 1);
        if (dist[t] > L) {
            cout << "NO\n";
            return 0;
        }
        reset();
        dijkstrasPossible(s, INF);
        if (dist[t] < L) {
            cout << "NO\n";
            return 0;
        }

        // definitely possible
        // change all the weight of erased edges to 1
        for (int i = 0; i < n; ++i) {
            for (edge &e : edges[i]) {
                if (e.first == 0) {
                    e.first = 1;
                }
            }
        }

        ll currShortest = shortestPath();
        while (currShortest != L) {
            // change an edge to from 1 -> (L - pathLength + 1)
            // reset distance array, seen array, pred array
            currShortest = shortestPath();
        }
        
        unordered_set<string> seenEdges;
        vector<edgeRes> res;
        for (int u = 0; u < n;++u) {
            for (edge &e : edges[u]) {
                if (seenEdges.find(tokenise(u, e.second)) != seenEdges.end()) {
                    continue;
                }
                seenEdges.insert(tokenise(u, e.second));
                res.push_back(edgeRes(u, e.second, e.first));
            }
        }

        cout << "YES\n";
        for (auto &e : res) {
            cout << e.u << ' ' << e.v << " " << e.w << endl;
        }
        
        return 0;
    }
