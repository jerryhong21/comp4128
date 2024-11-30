#include <vector>
#include <cmath>
#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <iomanip>

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

const ll MOD = 1e9 + 7;
const ll INF = (1LL << 59);
// const ll INF = (1LL << 30);
// const int INF = 1e9;
// const int N = 600, K = 100;

int t;
const int N = 1e5 + 5;
ll pow2[N];

void precompute() {
    pow2[0] = 1;
    for (int i = 1; i <= N- 1; ++i) {
        pow2[i] = pow2[i-1] * 2 % MOD;
    }
}

int main(void) {
    cin >> t;
    precompute();
    for (int it = 0; it < t; ++it) {
        int n;
        cin >> n;
        ll res = 0;
        ll s[n + 1];
        fill(s, s+n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        sort(s, s+n+1);
        for (int i = 1; i <= n; ++i) {
            // CANNOT HANDLE OVERFLOW LIKE THIS
            // res += (s[i] * ((pow2[i - 1] - pow2[n - i]) % MOD)) % MOD;
            ll diff = (pow2[i-1] - pow2[n-i] + MOD) % MOD;
            res = (res + s[i] * diff % MOD) % MOD;
        }
        
        cout << res << endl;
    }


    return 0;
}
