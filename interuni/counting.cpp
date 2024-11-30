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
typedef vector<vll> vvl;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

ll LIS(vector<ll> &arr)
{
    vector<ll> lis;
    for (ll x : arr)
    {
        auto it = lower_bound(lis.begin(), lis.end(), x);
        if (it == lis.end())
        {
            lis.push_back(x);
        }
        else
        {
            *it = x;
        }
    }
    return lis.size();
}

int main()
{
    ll n;
    cin >> n;
    vector<pll> points(n);

    for (ll i = 0; i < n; ++i)
    {
        ll x, y;
        cin >> x >> y;
        points[i] = make_pair(x, -y);
    }

    sort(points.begin(), points.end());

    // Extract the y-coordinates after sorting
    vector<ll> y_coords;
    for (const auto &p : points)
    {
        y_coords.push_back(p.second); // Only consider the y-coordinates (which are -y)
    }

    // Find the LIS on the y-coordinates
    ll result = LIS(y_coords);
    cout << result << endl;

    return 0;
}