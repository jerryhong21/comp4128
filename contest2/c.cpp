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
#include <deque>

// #include <bits/stdc++.h>
using namespace std;

// const ll INF = (1LL << 61);
const int INF = (1LL << 30);
// const int INF = 1e9;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
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

ll MOD = 1e9 + 7;
ll n;

int main(void)
{
    cin >> n;
    int dp[1 << (1 + n)][1+n];
    // memset(dp, 0, sizeof(dp));
    for (int i = 0; i < (1 << ((1 + n) - 1)); ++i) {
        for (int j =0; j < 1 +n;++j){
            dp[i][j] = 0;
        }
    }
        // base case
        for (int i = 0; i < n + 1; ++i)
        {
            dp[1 << i][i] = 1;
        }

    for (int bset = 1; bset < 1 << (1 + n); ++bset) {
        for (int last =0; last <n+1; ++last) {
            // cout << bitset<4><bset> << endl
            // if last does not exist at that spot
            if (!(bset & (1 << last))) continue;
            int pBset = bset ^ (1<<last);
            if (pBset == 0) continue;
            for (int cand = 0; cand < n +1 ; cand++) {
                if (!(pBset & (1 << cand))) continue;
                // this is not allowed
                if (last >= 1 && cand == last-1) continue;
                // reucrruence is
                dp[bset][last] = (dp[bset][last] + dp[pBset][cand]) % MOD;
            }
        }
    }
    ll res= 0;
    for (int i = 0; i < 1+n; ++i) {
        res = (res + dp[(1 << (n+1)) - 1][i])% MOD;
    }
    cout << res %MOD << endl;

    return 0;
}
