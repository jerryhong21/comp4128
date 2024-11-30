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
void generateBitset(int i, int pos, int ones, int currSet, vi &res)
{
    if (i == ones)
    {
        res.push_back(currSet);
        return;
    }
    if (pos >= n)
        return;

    generateBitset(i, pos + 1, ones + 1, currSet | (1 << pos), res);
    generateBitset(i, pos + 1, ones, currSet, res);
}

vi getBitsets(int i)
{
    vi res;
    generateBitset(i, 0, 0, 0, res);
    return res;
}

int main(void)
{

    cin >> n >> m >> k;
    ll a[n + 1];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ll rules[n + 1][n + 1];
    memset(rules, 0, sizeof(rules));

    REPi(k)
    {
        ll x, y, c;
        cin >> x >> y >> c;
        rules[x][y] = c;
    }

    // ll dp[m + 1][1 << (n + 1)];
    ll dp[1 << (n+1)][n+1];
    memset(dp, -1, sizeof(dp));

    // base cases - 1 dishes
    for (int i = 0; i < n; ++i) {
        dp[1 << (i)][i+1] = a[i+1]; 
    }

    ll best = 0;
    // loops over all sets
    for (int bs = 1; bs < (1 << n); ++bs) {
        // cout << "Currently examining " << bitset<4>(bs) << endl; 

        // count how many ones are in this bset
        int ones = __builtin_popcount(bs);
        if (__builtin_popcount(bs) > m) continue;

        // pick the last bit set
        for (int last = 1; last <= n; ++last) { 
            if (!(bs & (1 << (last-1)))) continue;
            if (dp[bs][last] == -1) continue;
            
            if (ones == m) {
                best = max(best, dp[bs][last]);
            }
            // pick the next one
            for (int next = 1; next <= n; ++next) {
                if (bs & (1 << (next - 1))) continue;
                // compute all possible next ones
                int nextBs = bs | (1 << (next - 1));
                dp[nextBs][next] = max(dp[nextBs][next], dp[bs][last] + a[next] + rules[last][next]);
            }   
        }
    }

    cout << best << endl;

    return 0;
}
