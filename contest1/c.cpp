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

bool comparePair(pll p1, pll p2) {

    if (p1.first != p2.first) {
        return p1.first < p2.first;
    }
    return p1.second > p2.second;
}

int main()
{
    ll n;
    cin >> n;

    vector<pll> costDue(n);
    for (int i = 0; i < n; ++i) {
        ll currCost, currDue;
        cin >> currCost >> currDue;
        costDue[i] = make_pair(currCost, currDue);
    }

    // sort by cost
    sort(costDue.begin(), costDue.end(), comparePair);


    ll totalProfit = 0;
    ll currDay = 0;
    for (pll cd : costDue) {
        totalProfit += (cd.second - (currDay + cd.first));
        currDay += cd.first;
    }
    cout << totalProfit << endl;


    return 0;
}
