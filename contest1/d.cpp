#include <limits>
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
#include <tuple>
#include <string>
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

    ll x = ((3 + 2 * n) - sqrt((3 + 2 * n) * (3 + 2 * n) - 4 * (n*n+n-2*k)))/2;
    cout << x << endl;

    return 0;
}
