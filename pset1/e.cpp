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
    ll n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;

    // figure out the tree structure and levels
    vll levels(n);

    if (t == s || k == 1) {
        cout << n << endl;
        return 0;
    }
    
    ll c = 0;
    for (ll i = 0; i < n; ++i) {
        ll penalty = 0;
        if (s[i] == 'b') penalty++;
        if (t[i] == 'a') penalty++;
        if (i == 0) {
            levels[i] = min(2 - penalty, k);
        } else {

            levels[i] = min(levels[i - 1] * 2 - penalty, k);
        }
        c += levels[i];
    }
    cout << c << '\n';
    return 0;
}
