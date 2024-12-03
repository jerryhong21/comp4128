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

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;

const ll N = 200010, Q = 500100;
ll parent[N], subtreeSize[N];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        subtreeSize[i] = 1;
    }
}

// with path compression
// amortized O(logn)
int root(int x) {
   return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y)  {
    x = root(x); y = root(y);

    // if already connected, return
    if (x == y) return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtreeSize[x] < subtreeSize[y]) {
        parent[x] = y;
        subtreeSize[y] += subtreeSize[x];
    } else  {
        parent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }
}

int n, q;

int main(void) {

    cin >> n >> q;
    init(n);

    // at most, you can merge n times
    // we we have alr merged (1, 5)
    // if we want to merge (2 - 6)

    // we want to keep track of some kind of group
    // we know that 2-6 is a group, so if we want to merge 4-7, 4-6 is redundant
    // if 2-5 is a group, and we want to merge 1-9, what do we do?

    // we can have a array to keep track of where the next segment if a is, since all teams are contiguous subarrays
    int jump[n + 1];
    fill(jump, jump + n + 1, 0);
    for (int i = 0; i < n; ++i) {
        jump[i] = i + 1;
    }

    for (int i = 0; i < q; ++i) {
        int type, x, y;
        cin >> type >> x >> y;
        --x; --y;
        if (x == y) {
            if (type == 3) {
                cout << "YES\n";
            }
            continue;
        }
        if (type == 1) {
            //merge team x and team y
            join(x, y);
        } else if (type == 2) {
            // for (a,b), set jump[a], jump[a+1],... jump[b-1] = jump[b]
            int temp = 0;
            for (int k = x; k <= y; k = temp) {
                join(x, k);
                temp = jump[k];
                jump[k] = jump[y];
            }


        } else if (type == 3) {
            if (root(x) == root(y)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}

