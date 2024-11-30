#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
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

typedef long long ll;
const int N = 100100;
const ll INF = (1LL << 61);
int n, m;

vector<pair<int, ll>> segments[N]; // (start, cost)
ll dp[N];
ll tree[1 << 18]; // range min tree with point update
/*
 * range tree query
 */

// the number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)

// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
ll query(int qL, int qR, int i = 1, int cL = 0, int cR = n)
{
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i];
    // we might need to query one or both of the children
    int mid = (cL + cR) / 2;
    ll ans = INF;
    // query the part within the left child [cL, mid), if any
    if (qL < mid)
        ans = min(ans, query(qL, min(qR, mid), i * 2, cL, mid));
    // query the part within the right child [mid, cR), if any
    if (qR > mid)
        ans = min(ans, query(max(qL, mid), qR, i * 2 + 1, mid, cR));
    return ans;
}
/*
 * range tree update
 */

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void update(int p, ll v, int i = 1, int cL = 0, int cR = n)
{
    if (cR - cL == 1)
    {
        // this node is a leaf, so apply the update
        tree[i] = v;
        return;
    }
    // figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);
    // once we have updated the correct child, recalculate our stored value.
    tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
}

// print the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void debug(int i = 1, int cL = 0, int cR = n)
{
    // print current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << ") = " << tree[i]  << endl;

    if (cR - cL > 1)
    { // not a leaf
        // recurse within each child
        int mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int s, e, c;
        cin >> s >> e >> c;
        segments[e].emplace_back(s, c); // preprocess: collate by end point
    }

    for (int i = 0; i <= n; i++)
        update(i, INF);
    debug();
    cout << endl;

    for (int i = 0; i <= n; i++)
    {
        dp[i] = INF;
        for (auto seg : segments[i])
        {
            ll prevcost = seg.first == 0 ? 0 : query(seg.first - 1, i);
            cout << "at segment starting "<<seg.first << " and ending " << i << " prevcost = " << prevcost << endl;
            dp[i] = min(dp[i], prevcost + seg.second);
        }
        update(i, dp[i]);
        debug(); cout << endl;
        cout << "dp[" << i << "] = " << dp[i] << endl;
    }
    cout << dp[n] << '\n';
}
