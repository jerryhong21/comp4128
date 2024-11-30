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
// const int INF = 1e9;

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

struct Edge {
    int to, cost, color;
};

struct State {
    int node, exhaustion, bmask;
    bool operator>(const State &other) const {
        return exhaustion > other.exhaustion;
    }
};

int n, m, k;

int minimumExhaustion(vector<int> &elevations, vector<vector<Edge>> &edges) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0});
    vector<vector<int>> dist(n, vector<int>(1 << k, INF));
    dist[0][0] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int node = curr.node, currExhaustion = curr.exhaustion;
        int bmask = curr.bmask;

        if (currExhaustion > dist[node][bmask]) continue;

        if (node == n - 1 && bmask == (1 << k) - 1) {
            return currExhaustion;
        }

        for (const Edge &edge : edges[node]) {
            int nextNode = edge.to;
            int color = edge.color;
            int cost = max(0, elevations[nextNode] - elevations[node]);

            int newMask = bmask | (1 << color);
            int newExhaustion = currExhaustion + cost;

            if (newExhaustion < dist[nextNode][newMask]) {
                dist[nextNode][newMask] =  newExhaustion;
                pq.push({nextNode, newExhaustion, newMask});
            }
        }
    }

    // nothing
    return -1;
}

int main() {
    cin >> n >> m >> k;

    vector<int> elevations(n);
    for (int i = 0; i < n; i++) {
        cin >> elevations[i];
    }

    vector<vector<Edge>> edges(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b,  --c;
        edges[a].push_back({b, 0, c});
        edges[b].push_back({ a, 0, c});
    }

    int result = minimumExhaustion(elevations, edges);
    cout << result << endl; 

    return 0;
}