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

bool compareInversions(pii i1, pii i2)
{
    if (i1.first != i2.first)
    {
        return i1.first < i2.first;
    }
    return i1.second < i2.second;
}

int main()
{
    int n;
    cin >> n;
    vll a(n);
    REPi(n) cin >> a[i];

    vector<pii> sorted_a(n);
    for (int i = 0; i < n; i++)
        sorted_a[i] = make_pair(a[i], i);
    sort(sorted_a.begin(), sorted_a.end(), compareInversions);

    vector<int> rank_a(n);
    int current_rank = 1;
    rank_a[sorted_a[0].second] = current_rank;
    for (int i = 1; i < n; i++)
    {
        current_rank++;
        rank_a[sorted_a[i].second] = current_rank;
    }

    // Replace original array with ranks
    for (int i = 0; i < n; i++)
        a[i] = rank_a[i];

    unordered_map<int, int> idx;
    REPi(n) {
        idx[a[i]] = i;
    }

    vector<pll> inv;
    // // look for all inversion with v_i being the last element
    for (int k = n - 1; k >= 0; k--) {
        // k is meant to be the last element in the array
        // search for each a[k] + 1, a[k] + 2, ..., k, they should all be inversions
        // perform swaps
        vector<pll> toSwap;
        for (int i = a[k] + 1; i <= k + 1; i++) {
            // look for the index of i, and then swap it with a[k]
            int index = idx[i];
            if (index >= k) break;
            inv.push_back(make_pair(index + 1, k + 1));
            toSwap.push_back(make_pair(index, k));

        }
        for (pll s : toSwap) {
            swap(a[s.first], a[s.second]);
            int temp = idx[a[s.first]];
            idx[a[s.first]] = idx[a[s.second]];
            idx[a[s.second]] = temp;
        }
        toSwap.clear();
    }


    if (inv.empty())
    {
        cout << 0 << endl;
        return 0;
    }

    cout << inv.size() << endl;
    for (auto &p : inv)
    {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
