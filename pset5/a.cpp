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

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;


#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

int n, k;
const int N = 100005, K = 100005;


struct node {
    int depth; // starts at 0
    int side; // 0 for left, 1 for right
    bool valid;
};


// left[i] denotes the node at ith node
node leftNodes[N + K + 5], rightNodes[N+K+5];

/*
    approach:
    
    construct the bipartite graph, and you need information about the node's level
    make the nodes -1 if it is dangerous

    in the bfs starting from bottom node, we need to dynamically determine what edges it has
    need to record the parent in the bfs, and also record what side the bfs is on
    keep track of "depth" in the bfs and compare it to what level you are on. the depth indicates the time elapsed
*/

// leftDepth[i] marks depth of left node i
int leftDist[N], rightDist[N];

bool bfs() {

    fill(leftDist, leftDist + N, -1);
    fill(rightDist, rightDist + N, -1);
    leftDist[0] = 0;

    queue<node> q;
    q.push(leftNodes[0]);

    while (!q.empty()) {
        node currNode = q.front();
        q.pop();

        // iterate through edges
        vector<node> edges;
        bool isLeft = currNode.side == 0;
        int *dist = isLeft ? leftDist : rightDist;
        node *nodes = isLeft ? leftNodes : rightNodes;
        node *oppNodes = isLeft ? rightNodes : leftNodes;
        // if you can go straight up, or jump out, then return true
        if (currNode.depth >= n - k) return true;

        // determine if the water is not so high that the ninja cannot go down a level
        int waterLvl = dist[currNode.depth];
        if (currNode.depth - 1 >= 0 && waterLvl < currNode.depth - 1) {
            if (nodes[currNode.depth - 1].valid) {
                edges.push_back(nodes[currNode.depth - 1]);
            }
        }

        // can you go up
        if (nodes[currNode.depth + 1].valid) {
            edges.push_back(nodes[currNode.depth + 1]);
        }

        // can jump across?
        if (oppNodes[currNode.depth + k].valid) {
            edges.push_back(oppNodes[currNode.depth + k]);
        }

        for (node nxt : edges) {
            bool nxtLeft = nxt.side == 0;
            if (nxtLeft) {
                if (leftDist[nxt.depth] == -1) {
                    leftDist[nxt.depth] = dist[currNode.depth] + 1;
                    q.push(nxt);
                }
            } else {
                if (rightDist[nxt.depth] == -1) {
                    rightDist[nxt.depth] = dist[currNode.depth] + 1;
                    q.push(nxt);
                }
            }
        }

    }

    return false;
}

// keep a set of vertices covered
int main(void) {
    cin >> n >> k;
    string leftStr, rightStr;
    cin >> leftStr >> rightStr;

    for (int i = 0; i < n; ++i) {
        if (leftStr[i] == '-') {
            leftNodes[i] = {i, 0, true};
        } else {
            leftNodes[i] = {i, 0, false};
        }
        if (rightStr[i] == '-') {
            rightNodes[i] = {i, 1, true};
        } else {
            rightNodes[i] = {i, 1, false};
        }
    }
    if (bfs()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }



    return 0;
}
