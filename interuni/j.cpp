#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
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

ll gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int main()
{
    ll n, x, y;

    cin >> n >> x >> y;

    vll a(n);
    vll b(n);
    vll d(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }



    REPi(n) {
        // cout << gcd(a[i], b[i]) << " is gcd\n";
        d[i] = gcd(a[i], b[i]);
    }
    
    ll prev = d[0];
    REP1i(n) {
        prev = gcd(prev, d[i]);
    }

    if ((x - y) % prev == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
