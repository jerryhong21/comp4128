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

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

int n, m, k;

// generates all bitsets with i number of ones
void generateBitset(int i, int pos, int ones, int currSet, vi &res) {
    if (i == ones) {
        res.push_back(currSet);
        return;
    }
    if (pos >= n) return;

    generateBitset(i, pos+1, ones + 1, currSet | (1 << pos), res);
    generateBitset(i, pos+1, ones, currSet, res);

}

vi getBitsets(int i) {
    vi res;
    generateBitset(i, 0, 0, 0, res);
    return res;
}

int main(void) {
    
    cin >>n>>m>>k;
    ll a[n + 1];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ll rules[n+1][n+1];
    memset(rules, 0, sizeof(rules));

    REPi(k) {
        ll x, y, c;
        cin >> x>>y>>c;
        rules[x][y] = c;
    }

    // initially, bitset is all zero and i = 0
    // pair<ll, ll> dp[m+1][1 << (n + 1)];
    // memset(dp, 0, sizeof(dp));

    ll dp[m+1][1<<(n + 1)];
    memset(dp, 0, sizeof(dp));

    // base cases
    REPi(k) dp[0][0] = 0;
    
    // vector<pll> bitsets;
    // bitsets.push_back(make_pair(0, -1));

    
    ll best = 0;
    for (int i = 1; i <= m; ++i) {
        ll res = 0;
        vi bitsets = getBitsets(i);
        for (int bset : bitsets) {
            // cout << "currently exploring " << bitset<4>(bset) << endl;
            // loop over all ones, and get rid of them one at a time, this should be an existing state
            for (int j = 0; j < n; ++j)
            {
                if (bset & (1 << j)) {
                    int mask = ~(1 << j);
                    int shouldExistBset = bset & mask;

                    // cout << bitset<4>(shouldExistBset) << " should already exist.\n";

                    ll res = a[j + 1];
                    // loop over all ones in this bset, and assume that each of them was put last
                    for (int k = 0; k < n; ++k) {
                        if (shouldExistBset & (1 << k)) {
                            // this k couldve been put last
                            // cout << "the " << k + 1 <<  " could've been the last dish placed\n";
                            // cout << "there exists a " << rules[k + 1][j + 1] << " bonus for choosing the " << j + 1 << " item after " << k + 1 << endl;
                            // cout << "the reward for choosing the " << j + 1 << " th menu is " << a[j+1] << endl;
                            res = max(res, dp[i - 1][shouldExistBset] + a[j+1] + rules[k+1][j+1]);
                            // cout << endl;
                        }
                    }
                    dp[i][bset] = max(dp[i][bset], res);
                    best = max(best, dp[i][bset]);
                    // cout << "set dp(" << i << ", " << bitset<4>(bset) << ") to " << res << endl;
                }
            }
        }
    }

    cout << best <<endl;

    return 0;
}

