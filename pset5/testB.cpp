// #include <iostream>
// #include <vector>
// #include <stack>
// #include <queue>
 
// using namespace std;
 
// typedef long long ll;
// // to vertex, weight, isTrain
// typedef tuple<ll, ll, ll> edge;
// const int N = 100100;
// vector<edge> edges[N];
// ll dist[N];
// bool seen[N];
// ll usingTrainEdge[N];
 
//  // just to prioritse lower edge weights and also put non train edges first.
// struct CompareEdge {
//     bool operator()(const edge& e1, const edge& e2) {
//         if (get<1>(e1) == get<1>(e2)) {
//             return get<2>(e1) > get<2>(e2);
//         }
//         return get<1>(e1) > get<1>(e2);
//     }
// };
// priority_queue<edge, vector<edge>, CompareEdge> pq;
 
// ll trainsUsed = 0;
 
// void dijkstra (ll s) {
//     fill(seen,seen+N,false);
//     fill(dist, dist + N, 1e18); 
//     fill(usingTrainEdge, usingTrainEdge+N, 0);    

//     pq.push(edge(s, 0, 0)); // distance to s itself is zero
//     dist[s] = 0;
 
//     while (!pq.empty()) {   
//         auto [v, d, isTrain] = pq.top();
//         pq.pop();

//         if (seen[v]) continue;
//         seen[v] = true;
        
//         if (isTrain && usingTrainEdge[v] == 0) {
//             usingTrainEdge[v] = 1;
//             trainsUsed++;
//         }
 
//         // relax all edges from v
//         for (auto [u, weight, newEdgeisTrain] : edges[v]) {
//             ll newWeight = d + weight;
//             if (newWeight < dist[u]) {
//                 dist[u] = newWeight;
//                 pq.push(edge(u, newWeight, newEdgeisTrain));    
//                 if (newEdgeisTrain == 1) {
//                     if (usingTrainEdge[u] == 0) trainsUsed++;
//                     usingTrainEdge[u] = 1;
//                 } else {
//                     if (usingTrainEdge[u] == 1) trainsUsed--;
//                     usingTrainEdge[u] = 0;
//                 }
//             }
//         }
//     }
// }
 
// int main() {
//     ll n, m, k;
//     cin >> n >> m >> k;
 
//     for (int i = 0; i < m; i++) {
//         ll u, v, x;
//         cin >> u >> v >> x;
 
//         edges[u].push_back({v, x, 0});
//         edges[v].push_back({u, x, 0});
//     }
 
//     for (int i = 0; i < k; i++) {
//         ll s, y;
//         cin >> s >> y;
 
//         edges[1].push_back({s, y, 1});
//         edges[s].push_back({1, y, 1});
//     }
 
//     dijkstra(1);
 
//     // count all the trains

//     cout << k - trainsUsed << endl;
// }

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
 
using namespace std;
 
typedef long long ll;
// to vertex, weight, isTrain
typedef tuple<ll, ll, bool> edge;
const int N = 100100;
vector<edge> edges[N];
ll dist[N];
bool seen[N];
bool usingTrain[N];
 
 // just to prioritse lower edge weights and also put non train edges first.
struct CompareEdge {
    bool operator()(const edge& e1, const edge& e2) {
        if (get<1>(e1) == get<1>(e2)) {
            return get<2>(e1) < get<2>(e2);
        }
        return get<1>(e1) < get<1>(e2);
    }
};

priority_queue<edge, vector<edge>, CompareEdge> pq;
 
ll trainsUsed = 0;
 
void dijkstra (ll s) {
    fill(seen,seen+N,false);
    fill(dist, dist + N, 1e18); 
    fill(usingTrain, usingTrain+N, 0);    

    pq.push(edge(s, 0, 0)); // distance to s itself is zero
    dist[s] = 0;
 
    while (!pq.empty()) {   
        auto [v, d, isTrain] = pq.top();
        pq.pop();

        if (seen[v]) continue;
        seen[v] = true;
        
        if (isTrain && usingTrain[v] == false) {
            usingTrain[v] = true;
            trainsUsed++;
        }
 
        // relax all edges from v
        for (auto [u, weight, newEdgeisTrain] : edges[v]) {
            ll newWeight = d + weight;
            if (newWeight < dist[u]) {
                dist[u] = newWeight;
                pq.push(edge(u, newWeight, newEdgeisTrain));    
                if (newEdgeisTrain == 1) {
                    if (usingTrain[u] == 0) trainsUsed++;
                    usingTrain[u] = true;
                } else {
                    if (usingTrain[u] == 1) trainsUsed--;
                    usingTrain[u] = false;
                }
            }
        }
    }
}
 
int main() {
    ll n, m, k;
    cin >> n >> m >> k;
 
    for (int i = 0; i < m; i++) {
        ll u, v, x;
        cin >> u >> v >> x;
 
        edges[u].push_back({v, x, false});
        edges[v].push_back({u, x, false});
    }
 
    for (int i = 0; i < k; i++) {
        ll s, y;
        cin >> s >> y;
 
        edges[1].push_back({s, y, true});
        edges[s].push_back({1, y, true});
    }
 
    dijkstra(1);
 
    // count all the trains

    cout << k - trainsUsed << endl;
}
