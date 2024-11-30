#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
// #include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)


int main()
{
    int n;
    cin >> n;
    vi m(n);
    REPi(n) cin >> m[i];
    vi dp(n);
    dp[0] = 1;
    // dp[i] = max(dp[i - 1], mi + 1)
    
    for (int i = 1; i < n; ++i) {
        dp[i] = max(dp[i - 1], m[i] + 1);
    }

    // if dp[i - 1] < dp[i] - 1, dp[i - 1] = dp[i] - 1
    for (int i = n - 1; i > 0; --i) {
        if (dp[i - 1] < dp[i] - 1) {
            dp[i - 1] = dp[i] - 1;
        }
    }
    // for (int n : dp) {
    //     cout << n << ", ";
    // }
    // cout << endl;

    ll total = 0;
    for (int i = 0; i < n; i++)
    {
        total += (dp[i] - m[i] - 1);
    }
    cout << total << endl;

    return 0;
}
