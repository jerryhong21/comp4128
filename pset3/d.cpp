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

const ll INF = (1LL << 61);

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

ll n, k;
string router;

ll tree[1<<19];

// query
ll query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (cL == qL && cR == qR) {
        return tree[i];
    }
    ll mid = (cL + cR) / 2;
    ll ans = INF;
    if (qL < mid) ans = min(ans, query(qL, min(qR, mid), i * 2, cL, mid));
    if (qR > mid) ans = min(ans, query(max(mid, qL), qR, i*2+1, mid, cR));
    return ans;
}


void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
    if (cR - cL == 1) {
        tree[i] = v;
        return;
    }
    // figure out which child is responsible for index p being udpated
    ll mid = (cL + cR) / 2;
    if (p < mid) {
        update(p, v, i*2, cL, mid);
    } else {
        update(p, v, i*2+1, mid, cR);
    }
    tree[i] = min(tree[i*2], tree[i*2+1]);
}


int main(void) {

    cin>>n>>k;
    cin>>router;
    // dp[i][j] denotes min money to come up to ith room 
    // with last router purchased at room j
    
    ll dp[n + 1];
    memset(dp, 0, sizeof(dp));

    // (start, cost)
    vpll segments[n];
    
    // convert everything to ranges
    for (ll i = 0; i < n; ++i) {
        if (router[i] == '1') {
            ll s = max(0LL, i - k);
            ll e = min(n - 1, i + k);
            segments[e].emplace_back(s, i + 1);
            // cout << "created segment starting at " << s<< " ending at " << e << " with cost " << i + 1 << endl;
        }
        segments[i].emplace_back(i, i+1);
        // cout << "created segment starting at " << i << " ending at " << i << " with cost " << i + 1 << endl;
    }

    // dp[i+1] = c + min dp[j]
    // where c is the segmenet with [s, i+1];
    
    for (ll i = 0; i < n; ++i) {
        update(i, INF);
    }
  
    for (ll i = 0; i < n; ++i) {
        dp[i] = INF;
        for (auto seg : segments[i]) {
            // cout << "Considering segment " << i << " with s = " << seg.first << " , e = " << seg.second << endl << endl;
            ll prevcost = seg.first == 0 ? 0 : query(seg.first - 1, i);
            dp[i] = min(dp[i], prevcost + seg.second);
        }
        update(i, dp[i]);
        // cout << "updating dp[" << i << "] to be " << dp[i] << endl;
    }
    cout << dp[n - 1] << endl;


    return 0;
}
