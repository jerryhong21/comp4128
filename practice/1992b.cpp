#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>

// #include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// const ll INF = (1LL << 59);
ll INF = (1LL << 30);
// const int INF = 1e9;


int main(void) {

    int t; cin >> t;
    ll n, k;
    vector<ll> ans;
    for (int i = 0; i < t;  ++i) {
        cin >> n >> k;
        ll a[k];
        for (int j = 0; j < k; ++j) {
            cin >> a[j];
        }
        sort(a, a + k);
        ll res = 0;
        for (int j = 0; j < k - 1; ++j) {
            res += (a[j] - 1);
            res += a[j];
        }
        ans.push_back(res);
    }

    for (int i = 0; i < t; ++i) {
        cout << ans[i] << endl;
    }

}