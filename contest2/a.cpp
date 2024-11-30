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

// const ll INF = (1LL << 61);
const int INF = (1LL << 30);
// const int INF = 1e9;

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

int n;

int main(void)
{
    cin >> n;
    vi radius(n);

    for (int i = 0; i < n; ++i) {
        cin>>radius[i];
    }
    // sort in dec order
    sort(radius.begin(), radius.end(), [&](const int r1, const int r2) {
        return r1 > r2;
    });

    // pick the largest 
    // keep a counter of smallest remaining minutes
    ll remDuration = INF;
    ll ans = 0;
    for (int r : radius) {
        // pick a new radius
        // cout << "current radius is " << r<<endl; 
        if (remDuration <= 0) break;
        ans++;
        if (r < remDuration) {
            // cout << " New remaining duration is " << remDuration << endl;
            remDuration = r;
        }

        remDuration--;
    }

    cout << ans << endl;
    for (int i = 0; i < ans; ++i) {
        cout << radius[i] << ' ';
    }
    cout << endl;


    return 0;
}
