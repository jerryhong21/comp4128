#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// const ll INF = (1LL << 59);
// const ll INF = (1LL << 30);
const int INF = 1e9;

const ll MOD = 1000 * 1000 * 1000 + 7;

const int N = 22;
// freq[k][2] = frequency of letter 'a' + 2 in the kth dice
ll freq[N][30];
char dice[N][7];
ll dp[1 << N];

int n, k;
string s;

int main(void) {
    // memset(dice, 0, sizeof(dice));
    memset(freq, 0, sizeof(freq));
    memset(dp, 0, sizeof(dp));
    cin >> n >> k >> s;
    for (int i = 0; i < n; ++i) {
        string cur;
        cin >> cur;
        for (int j = 0; j < 6; ++j) {
            char ch = cur[j];
            dice[i][j] = ch;
            freq[i][ch - 'a']++;
        }
    }

    dp[0] = 1LL;
    for (int bset = 1; bset < (1 << n); ++bset) {
        // cout << "Currently examining " << bitset<8>(bset) << endl; 

        // iterate for every bitset
        ll total = 0;
        int currSize = __builtin_popcount(bset);
        // cout << s[currSize - 1] << " current letter filling\n"; 
        // pick last dice to be added
        for (int last = 0; last < n; ++last) {
            // if last has no membership
            if (!(bset & (1 << last))) continue;

            int prev = bset & (~(1 << last));
            // cout << "prev = " << bitset<8>(prev) << endl; 
            ll res = dp[prev];

            // find out frequency of s[|bset|] in dice[last]
            res *= (freq[last][s[currSize - 1] - 'a'] % MOD);
            res %= MOD;

            total += res;
            total %= MOD; 
        }

        dp[bset] = total;
        // cout << "dp[ " << bitset<8>(bset) << " = " << dp[bset] << endl;
    }

    // the answer is every subset with the right bitset amount
    ll ans = 0;
    for (int i = 1; i < (1 << n); ++i) {
        if (__builtin_popcount(i) == k) {
            ans += dp[i];
            ans %= MOD;
        }
    }
    cout << ans << endl;


    return 0;
}