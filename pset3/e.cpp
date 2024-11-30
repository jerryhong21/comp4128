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
// const int INF = (1LL << 30);
// const int INF = 1e9;

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

ll n, m;
string s;

int main(void)
{
    cin >> n >> m >> s;
    // 'a' = 1, not 0
    ll adj[m + 1][m + 1];
    memset(adj, 0, sizeof(adj));
    // process string into adjacencies
    for (int i = 1; i < n; ++i) {
        if (s[i-1] == s[i]) continue;
        // cout << "added adjency between " << s[i] << " and " << s[i-1] << endl;
        adj[s[i]-'a' + 1][s[i-1] - 'a' + 1] += 1;
        adj[s[i - 1]-'a' + 1][s[i] - 'a' + 1] += 1;
    }

    // dp
    // dp[S] = min_{l in S}, dp[S\l] + num of adjenceies between each letter in S and each letter not in S

    // precompute bitsets in increasing size
    ll dp[(1 << m)];
    for (ll i = 0; i < (1 << m); ++i) {
        dp[i] = INF;
    }
    dp[0] = 0;
    // for (int i = 0; i < m; ++i) {
    //     dp[1 << i] = 0;
    //     cout << "set " << bitset<4>(1 << i) << " to 0\n";
    // }

    // for (int i = 0; i < (1 << m); ++i) {
    //     cout << dp[i] << ' ';
    // }
    // cout << endl;
    

    for (ll bset = 1; bset < (1 << m); ++bset) {
        int nLetters = __builtin_popcount(bset);
        if (nLetters > m) continue;
        // loop over each letter in i
        // find all letters in the bset, and all letters not in the bset

        // potentially optimise

        // VECTOR IS TOO SLOW????????????

        // vll missing(m - nLetters), present(nLetters);
        ll missing[m], present[m];
        ll a = 0, b = 0;
        for (int pos = 0; pos < m; ++pos) {
            if (!(bset & (1 << pos))) {
                missing[a] = pos + 1;
                a++;
                // missing.push_back(pos + 1);
            } else {
                present[b] = pos + 1;
                b++;
                // present.push_back(pos + 1);
            }
        }

        // cout << "Current bitset is " << bitset<4>(bset) << endl;
        ll count = 0;
        // for (int p : present) {
        //     for (int m : missing) {
        //         count += adj[p][m];
        //     }
        // }
        for (int p = 0; p < b; ++p) {
            for (int m = 0; m < a; ++m) {
                count += adj[present[p]][missing[m]];
            }
        }

        for (ll last = 0; last < m; ++last) {
            // if this is a zero, then continue
            if (!(bset & (1 << last))) continue;

            // set the last index to zero
            int lastBset = bset & ~(1 << last);
            // cout << "lastBest is " << bitset<4>(lastBset) << " and count = " << count << endl;

            dp[bset] = min(dp[bset], dp[lastBset] + count);
        }
        // cout << "dp[" << bitset<4>(bset) << "] = " << dp[bset] << endl;
    }

    cout << dp[(1 << m) - 1] << '\n';


    return 0;
}
