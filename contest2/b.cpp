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
#include <deque>

// #include <bits/stdc++.h>
using namespace std;

// const ll INF = (1LL << 61);
const int INF = (1LL << 30);
// const int INF = 1e9;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
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

ll r, c, k;

bool cmpSmaller(int a, int b)
{
    return a < b;
}

bool cmpLarger(int a, int b)
{
    return a > b;
}

vll minMaxSliding(vll &row, int k, function<bool(int, int)> cmp)
{
    vll res;
    deque<int> rowIdx;
    for (int progress = 0; progress < row.size(); progress++)
    {
        // remove outside of current window
        if (!rowIdx.empty() && rowIdx.front() == progress - k)
            rowIdx.pop_front();
        // filter
        while (!rowIdx.empty() && cmp(row[rowIdx.back()], row[progress]))
            rowIdx.pop_back();

        rowIdx.push_back(progress);

        if (progress < (k - 1)) continue;
        res.push_back(row[rowIdx.front()]);
    }
    return res;
}

int main(void)
{
    cin >> r >> c >> k;
    vvll grid(r, vll(c));
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> grid[i][j];
        }
    }

    // precompute min and max of all grids
    vvll preMin(r), preMax(r);
    // binary search?
    // we need to calculate min and max value outside of grid
    // min and max inside the square

    // for each grid, determine if there exists a value outside that grid
    // that is in between min and max

    // for every row
    // compare if the max of the point, is larger than max of previous point
    // and comprae if max of

    // cases
    // everything inside is smaller
    // everything inside is larger
    vll allNumbers;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            allNumbers.push_back(grid[i][j]);
        }
    }
    sort(allNumbers.begin(), allNumbers.end());
    ll maxRow = r - k, maxCol = c - k;

    for (int i = 0; i < r; ++i)
    {
        preMin[i] = minMaxSliding(grid[i], k, cmpLarger);
        preMax[i] = minMaxSliding(grid[i], k, cmpSmaller);
    }
    // for (int i = 0; i < preMax[1].size(); ++i)
    // {
    //     cout << "minimum at row " << i << "is " << preMin[1][i] << '\n';
    // }

    vvll preMinGrid(maxRow + 1, vll(maxCol + 1)), preMaxGrid(maxRow + 1, vll(maxCol + 1));

    // llop through each column to compute prefix sum again
    for (int i = 0; i < maxCol + 1; ++i)
    {
        vll minCol, maxCol;
        for (int j = 0; j < r; ++j)
        {
            minCol.push_back(preMin[j][i]);
            maxCol.push_back(preMax[j][i]);
        }
        vll preMinCol = minMaxSliding(minCol, k, cmpLarger);
        for (ll j = 0; j < maxRow + 1; ++j)
        {
            preMinGrid[j][i] = preMinCol[j];
        }
        vll preMaxCol = minMaxSliding(maxCol, k, cmpSmaller);
        for (ll j = 0; j < maxRow + 1; ++j)
        {
            preMaxGrid[j][i] = preMaxCol[j];
        }
    }

    // for (int i = 0; i < r-k+1; ++i) {
    //     for (int j = 0; j < maxCol+1; ++j) {
    //         cout << "Min at grid starting " << i << ',' << j << " is " << preMinGrid[i][j] << '\n';
    //         cout << "Max at grid starting " << i << ',' << j << " is " << preMaxGrid[i][j] << '\n';
    //     }
    // }

    // iterate through eahc subgrid
    // for each subgrid, we binary search the allnumbers array for the boundaries
    // and then we calcualte how many things are in betwene, if k^2 then valid
    for (int i = 0; i < r - k + 1; ++i)
    {
        for (int j = 0; j < maxCol + 1; ++j)
        {
            ll gridMax = preMaxGrid[i][j], gridMin = preMinGrid[i][j];
            // bsearch and count gap
            int nBetween = upper_bound(RANGE(allNumbers), gridMax) - lower_bound(RANGE(allNumbers), gridMin);
            if (nBetween == k * k)
            {
                cout << "YES\n";
                cout << i + 1 << ' ' << j + 1 << '\n';
                return 0;
            }
        }
    }
    cout << "NO\n";

    return 0;
}
