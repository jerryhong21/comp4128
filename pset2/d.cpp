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

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

struct TreeNode {
    ll min;
    ll max;
    ll leftValue;
    ll rightValue;
    bool increasing;
    bool decreasing;
    ll d;
};

vector<TreeNode> tree(1<<20);
// n = numProblems
// m = numOperations
ll n, m;

// p: index of the array
// v: value of the pth element
void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
    if (cR - cL == 1) {
        tree[i].min = v;
        tree[i].max = v;
        tree[i].leftValue = v;
        tree[i].rightValue = v;
        tree[i].increasing = true;
        tree[i].decreasing = true;
        tree[i].d = v;
        return;
    }
    // figure out which child is responsible for the index p being updated
    ll mid = (cL + cR) / 2;
    if (p < mid) {
        update(p, v, i*2, cL, mid);
    } else {
        update(p, v, i*2+1, mid, cR);
    }
    TreeNode &l = tree[2 * i];
    TreeNode &r = tree[2 * i + 1];
    tree[i].min = min(l.min, r.min);
    tree[i].max = max(l.max, r.max);
    tree[i].d = l.d + r.d;
    tree[i].leftValue = l.leftValue;
    tree[i].rightValue = r.rightValue;
    // increasing if right min >= left max, and both increasing
    tree[i].increasing = (r.leftValue >= l.rightValue) && (r.increasing && l.increasing);
    // decreasing - both decreasing, left min >= right max
    tree[i].decreasing = (l.rightValue >= r.leftValue) && (r.decreasing && l.decreasing);
}

// queries: 
// max difficulty
// total difficulty
// is increasing

/*
 * range tree debug
 */

// print the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void debug(int i = 1, int cL = 0, int cR = n)
{
    // print current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << "): " << " max = " << tree[i].max << " min = " << tree[i].min << " difficulty = " << tree[i].d << " increasing = " << tree[i].increasing << " decreasing = " << tree[i].decreasing << endl;

    if (cR - cL > 1)
    { // not a leaf
        // recurse within each child
        int mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}

ll maxQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (cL == qL && cR == qR) {
        return tree[i].max;
    }
    ll mid = (cL + cR) / 2;
    ll ans = 1;
    if (qL < mid) ans = max(ans, maxQuery(qL, min(qR, mid), i*2, cL, mid));
    if (qR > mid) ans = max(ans, maxQuery(max(qL, mid), qR, i*2+1, mid, cR));
    return ans;
}

ll sumQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (cL == qL && cR == qR) {
        return tree[i].d;
    }

    ll mid = (cL + cR) / 2;
    ll ans = 0;
    if (qL < mid) ans += sumQuery(qL, min(qR, mid), i * 2, cL, mid);
    if (qR > mid) ans += sumQuery(max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

struct QueryRes {
    bool isInc;
    bool isDec;
    ll leftValue;
    ll rightValue;
};

QueryRes orderQuery(ll qL, ll qR, ll i=1, ll cL = 0, ll cR = n) {
    // in value result
    if (qR <= cL || qL >= cR) {
        return {true, true, -1, -1};
    }
    
    if (qL == cL && cR == qR) {
        return {tree[i].increasing, tree[i].decreasing, tree[i].leftValue, tree[i].rightValue};
    }
    ll mid = (cL + cR) / 2;
    QueryRes leftRes = {true, true, -1, -1};
    QueryRes rightRes = {true, true, -1, -1};
    if (qL < mid) leftRes = orderQuery(qL, min(qR, mid), i*2, cL, mid);
    if (qR > mid) rightRes = orderQuery(max(qL, mid), qR, i*2+1, mid, cR);
    if (leftRes.leftValue == -1) return rightRes;
    if (rightRes.leftValue == -1) return leftRes;

    bool increasing = (leftRes.isInc && rightRes.isInc) && (leftRes.rightValue <= rightRes.leftValue);
    bool decreasing = (leftRes.isDec && rightRes.isDec) && (leftRes.rightValue >= rightRes.leftValue);

    return {increasing, decreasing, leftRes.leftValue, rightRes.rightValue};
}


int main()
{
    cin >> n >> m;
    
    // build tree
    REPi(n) {
        ll curr;
        cin >> curr;
        update(i, curr);
    }
    // debug();
    REPi(m) {
        char c;
        ll x, y;
        cin >> c >> x >> y;
        if (c == 'U') {
            update(x - 1, y);
            // debug();
        } else if (c == 'M') {
            cout << maxQuery(x - 1, y) << endl;
        } else if (c == 'S') {
            cout << sumQuery(x - 1, y) << endl;
        } else if (c == 'I') {
            QueryRes inc = orderQuery(x - 1, y);
            if (inc.isInc) {
                cout << 1 << '\n';
            } else cout << 0 << '\n';
        } else if (c == 'D') {
            QueryRes dec = orderQuery(x - 1, y);
            if (dec.isDec) {
                cout << 1 << '\n';
            } else cout << 0 << '\n';
        }
    }

    return 0;
}
