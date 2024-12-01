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

// const ll INF = (1LL << 61);
const int INF = (1LL << 30);

// struct Edge {
//   ll w;
//   ll v;
//   bool free;
// };

// struct cmp
// {
//   bool operator()(Edge e1, Edge e2) {
//     // prioritise s
//     if (e1.w == e2.w) {

//     }
//   }
// };
int n, m, k;

struct State {
  ll v, w, used;
  bool operator>(const State &other) const{
    // sort by smallest weight
    return w > other.w;
  }
};

typedef pair<int, int> edge; // (distance, vertex)
const int N = 100100, M = 100100;
const int K = 12;

vector<edge> edges[N];
priority_queue<State, vector<State>, greater<State>> pq;
ll dist[N][K];

ll dijkstra (int s) {
  // dist[i][k] means maximum distance to node i using exactly k free edges
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= k; ++j) {
      dist[i][j] = INF;
    }
  }
  dist[0][0] = 0;
  pq.push({0,0,0});
  ll res = INF;

  while (!pq.empty()) {
    State cur = pq.top();
    pq.pop();

    ll node = cur.v, currDist = cur.w;
    int used = cur.used;

    // 
    if (currDist > dist[node][used]) continue;
    if (node == (n - 1) && used == k) {
      res = min(res, dist[n-1][used]);
      break;
    }

    // exploring neighbours of this node
    // at this node, we have used "used" amount of free edges
    for (edge &e : edges[node]) {
      int nxt = e.second;
      ll d = e.first;

      if (used < k) {
        // we use a free edge if its worth it
        // "worth" is defined by checking dist[nxt][used + 1]
        if (currDist < dist[nxt][used + 1]) {
          dist[nxt][used + 1] = currDist;
          if (nxt == n - 1) {
            res = min(res, dist[nxt][used + 1]);
          }
          pq.push({nxt, currDist, used + 1});
        }
      }
      // add noraml edge
      // similar, we add a normal edge if its worht it
      if (currDist + d < dist[nxt][used]) {
        dist[nxt][used] = currDist + d;
        if (nxt == n - 1) {
          res = min(res, dist[nxt][used]);
        }
        pq.push({nxt, currDist + d, used});
      }
    }
  }
  if (res == INF) {
    return -1;
  }
  return res;
}

int main(void) {

    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i) {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        --u;--v;
        edges[u].push_back({w, v});
    }

    cout << dijkstra(0) << endl;

  return 0;
}