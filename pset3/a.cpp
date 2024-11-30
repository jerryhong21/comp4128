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


int main()
{  
    ll n;
    cin >> n;
    // height array
    ll h[n][2];
    REPi(n) cin >> h[i][0];
    REPi(n) cin >> h[i][1];

    ll dp[n][2];
    
    // opt(i, k) = h[i][k] + max(opt(i-1, ~k), opt(i-2, ~k))

    dp[0][0] = h[0][0];
    dp[0][1] = h[0][1];

    for (ll i = 1; i < n; ++i) {
        // max(opt(i-1, ~k), opt(i-2, ~k))

        if (i == 1) {
            dp[i][0] = h[i][0] + dp[i-1][1];
            dp[i][1] = h[i][1] + dp[i-1][0];
            continue;
        }
        dp[i][0] = h[i][0] + max(dp[i-1][1], dp[i-2][1]);
        dp[i][1] = h[i][1] + max(dp[i-1][0], dp[i-2][0]);
    }

    // find the max over all of dp
    ll res = 0;
    for (ll i = 0; i < n; ++i) {
        res = max(res, dp[i][0]);
        res = max(res, dp[i][1]);
    }

    cout << res << endl;


    return 0;
}
