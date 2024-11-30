#include <iostream>
#include <vector>
#include <cstring>
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
typedef long long ll;

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;

// const ll MOD = 1000 * 1000 * 1000 + 7;
const ll MOD = 998244353;

ll add(int a, int b) {
    a += b;
    a %= MOD;
    return a;
}

ll mul(int a, int b) {
    a = a *1LL * b % MOD;
    return a;
}

ll pow(ll x, ll n) {
    if (n == 0) return 1;
    ll a = pow(x, n / 2);
    a = a * a % MOD;
    if (n % 2 == 1) a = a * x % MOD;
    return a;
}

// using fermats little theorem: inv(a) = a^(m-2) % mod
ll computeInv(ll a) {
    return pow(a, MOD - 2) % MOD;
}

const ll N = 5010;


// sum[x][y] = sum (k in x->n) freq[k] * dp[k][y]
// sum[x][y] = sum[x+1][y] + freq[x] * dp[x][y]

// cumulative sum of all probabilities for card numbers k >= x
ll sum[N][N];
ll inv[N];

// dp[x][y] denotes probability of winning with last card X at turn y.
// dp[x][y] = (freq[x] - 1) * inv[n - y] + inv[n - y] * sum[x + 1][y + 1]
ll dp[N][N];

// this stores the frequency of each number
int freq[N];

ll n;
int main(void) {
    cin >> n;
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));
    memset(freq, 0, sizeof(freq));
    // compute inverses of everything up to n
    for (int i = 1; i <= n; ++i) {
        inv[i] = computeInv(i);
    }

    for (int i = 0; i < n; ++i) {
        int cur;
        cin >> cur;
        freq[cur]++;
    }

    freq[0] = 1;

    // loop from largest to smallest card
    // the result at smaller cards depend on 1. if we drew one of the same card, 2. If we drew a same card in a later round (in a larger card)
    for (int x = n; x >= 0; --x) {
        // for each card, we loop from latest turn to earliest turn
        // earlier turn depends on the result from later truns
        for (int y = n; y >= 0; --y) {

            // if there is no number of this value, then we can ignore
            // and
            if (freq[x] == 0) {
                // winning at x is 0
                dp[x][y] = 0;
                sum[x][y] = sum[x + 1][y];
                continue;
            }

            // if there are no cards left in the bag, invalid state
            int cardsLeft = n - y;
            // if n == y, we are at the last term
            if (n - y <= 0) {
                dp[x][y] = 0;
                sum[x][y] = sum[x + 1][y];
                continue;
            }

            // dp[x][y] = (freq[x] - 1) * inv[n - y] + inv[n - y] * sum[x + 1][y + 1]
            // sum[x][y] = sum[x+1][y] + freq[x] * dp[x][y]
            // main dp transition

            // at x = 0, same card probability = 0
            ll sameCardProb = mul(inv[cardsLeft], (freq[x] - 1));
            ll futureCardProb = mul(inv[cardsLeft], sum[x + 1][y + 1]);
            dp[x][y] = add(dp[x][y], sameCardProb);
            dp[x][y] = add(dp[x][y], futureCardProb);

            // update sum
            sum[x][y] = add(sum[x][y], sum[x+1][y]);

            // x = 0, sum = dp[x][y];
            sum[x][y] = add(sum[x][y], mul(freq[x], dp[x][y]));
        }
    }

    cout << dp[0][0] << endl;

}
