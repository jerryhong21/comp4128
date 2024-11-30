#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// const ll INF = (1LL << 59);
const ll INF = (1LL << 30);
// const int INF = 1e9;



// invariant: comparing number of edges, 
// a shorter path is always more favourable longer path 

// run dijkstras twice


typedef pair<int, int> edge; // (distance, vertex)
const int N = 100100;
vector<edge> edgesF[N];
vector<edge> edgesB[N];
// vector<edge> edgesB[N];

ll distF[N];
ll distB[N];
bool seen[N];

vector<pair<ll, ll>> allEdges;

priority_queue<edge, vector<edge>, greater<edge>> pq;

void dijkstra (int s, bool forward) {
  fill(seen,seen+N,false);
  pq.push(edge(0, s)); // distFance to s itself is zero
  while (!pq.empty()) {
    // choose (d, v) so that d is minimal
    // i.e. the closest unvisited vertex
    edge cur = pq.top();
    pq.pop();
    int v = cur.second;
    ll d = cur.first;
    if (seen[v]) continue;

    if (forward) {
        distF[v] = d;
    } else {
        distB[v] = d;
    }
    seen[v] = true;

    // relax all edges from v
    if (forward) {
      for (edge nxt : edgesF[v]) {
        int u = nxt.second, weight = nxt.first;
        if (!seen[u])
          pq.push(edge(d + weight, u));
      }
      continue;
    }
    for (edge nxt : edgesB[v]) {
        int u = nxt.second, weight = nxt.first;
        if (!seen[u])
          pq.push(edge(d + weight, u));
    }
  }


}

int main(void) {

    int n,m,k;
    cin >> n >> m >> k;

  // memset(distF, INF, sizeof(distF));
  // memset(distB, INF, sizeof(distB));
    for (int i = 0; i < n; ++i) {
      distF[i] = INF;
      distB[i] = INF;
      // cout << "dist from 1 to " << i + 1 << " = " << distF[i] << endl;
    }

    //   for (int i = 0; i < n; ++i) {
    //   // distF[i] = INF;
    //   // distB[i] = INF;
    //   cout << "dist from 1 to " << i + 1 << " = " << distF[i] << endl;
    // }

    for (int i = 0; i < m; ++i) {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        --u;--v;
        edgesF[u].push_back({w, v});
        edgesB[v].push_back({w, u});
        allEdges.push_back({u,v});
    }
    dijkstra(0, true);

    // for (int i = 0; i < n; ++i) {
    //   cout << "dist from 1 to " << i + 1 << " = " << distF[i] << endl;
    // }
    if (distF[n - 1] == INF) {
      cout << -1 << endl;
      return 0;
    }

    if (k == 0) {
      cout << distF[n-1] << endl;
      return 0;
    }

    dijkstra(n-1, false);

    // look through each edge
    ll minDist = INF;
    for (const auto& p : allEdges) {
        minDist = min(minDist, distF[p.first] + distB[p.second]);
    }

    cout << minDist << endl;
}



