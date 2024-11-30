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

const ll INF = 1e18;

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

int n,m,k;

int main(void)
{
    cin >> n>>m>>k;
    int c[n+1];
    c[0]= 0;
    REPi(n) cin >> c[i + 1];
    ll p[n+1][m+1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ll curr;
            cin >> curr;
            p[i][j] = curr;
        }
    }

    // using j beauty with last color l
    ll dp[n+1][k+1][m+1];
    // memset(dp, INF, sizeof(dp));
    for (ll i = 0; i <= n; ++i) {
        for (ll j = 0; j <= k; ++j) {
            for (ll l = 0; l <= m; ++l) {
                dp[i][j][l] = INF;
            }
        }
    }

    // base cases
    dp[0][0][0] = 0;
    if (c[1] == 0) {
        for (int color = 1; color <= m; ++color) {
            dp[1][1][color] = p[1][color];
        }
    } else dp[1][1][c[1]] = 0;


    for (int i = 1; i <= n; ++i) {
        for (int b = 1; b <= k; ++b) {
            for (int color = 1; color <= m; ++color) {

                // if ith tree is precolored, then we only want that color
                if (c[i] != 0 && color != c[i]) continue;
                ll cost = (c[i] == 0) ? p[i][color] : 0;

                for (int lastColor = 1; lastColor <= m; ++lastColor) {

                    // if the last tree was precolored, then we only consider that color
                    if (c[i-1] != 0 && c[i-1] != lastColor) continue;

                    if (lastColor == color) {
                        dp[i][b][color] = min(dp[i][b][color], dp[i-1][b][color] + cost);
                    } else {
                        dp[i][b][color] = min(dp[i][b][color], dp[i-1][b-1][lastColor] + cost);
                    }
                }
            }
        }
    }

    // choose from min( dp[n-1][k-1] )
    ll res = INF;
    for (int i = 1; i <= m; ++i) {
        res = min(res, dp[n][k][i]);
    }

    if (res == INF) {
        std::cout << -1 << '\n';
    } else {
        std::cout << res << '\n';
    }
    

    return 0;
}
