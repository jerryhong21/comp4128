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

    // dp[i][j][l] denotes min paint used the first i trees with j beauty and l being the last color used.
    // dp[i][j][l] = min_{j < i, c~{C}/l} ( opt(j, k-1, c) + sum of P[p][c] for p = j->i )

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

    if (c[1] == 0) {
        for (int color = 1; color <= m; ++color) {
            dp[1][1][color] = p[1][color];
        }
    } else dp[1][1][c[1]] = 0;

    // base case: dp[0][0][m] = 0
    // REPi(m) dp[1][1][i+1] = 0;

    for (int i = 2; i <= n; ++i) {
        // for each tree from 0->i, we iterate over possible beauties
        for (int b = 1; b <= i; ++b) {
            // iterate over every possible last color, and iterate over every next color  
            // last color = c 
            // if c[i] != 0, then we have a predetermined color
            if (c[i] == 0) {
                for (int nextColor = 1; nextColor <= m; ++nextColor) {
                    // nextColor = l
                    ll best = INF;
                    for (int lastColor = 1; lastColor <= m; ++lastColor) {
                        // cout << "At " << i << " th tree, " << " with beauty = " << b << ", last unique color is " << m << " and picking " << nextColor << " as next color\n";
                        if (nextColor == lastColor) {
                            best = min(best, dp[i - 1][b][lastColor] + p[i][nextColor]);
                        } else {
                            best = min(best, dp[i - 1][b - 1][lastColor] + p[i][nextColor]);
                        }
                    }
                    dp[i][b][nextColor] = min(best, dp[i][b][nextColor]);
                    // std::cout << "dp[" << i << "][" << b << "][" << nextColor << "] = " << dp[i][b][nextColor] << '\n';
                }

                // if last color was also predetermined, then we have a set nextColor
            } else {
                int nextColor = c[i];
                ll best = INF;
                if (c[i-1] == 0) {
                    for (int lastColor = 1; lastColor <= m; ++lastColor) {
                        if (dp[i-1][b][lastColor] < INF) {
                            if (nextColor == lastColor) {
                                best = min(best, dp[i - 1][b][lastColor]);
                            } else if (b > 1) {
                                best = min(best, dp[i - 1][b - 1][lastColor]);
                            }
                        }
                    }
                } else {
                    if (nextColor == c[i-1]) {
                        best = min(best, dp[i - 1][b][c[i - 1]]);
                    } else {
                        best = min(best, dp[i - 1][b - 1][c[i - 1]]);
                    }
                }
                dp[i][b][nextColor] = min(best, dp[i][b][nextColor]);
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
