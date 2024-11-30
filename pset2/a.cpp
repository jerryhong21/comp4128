#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <map>
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


bool comp(pll p1, pll p2) {
    
    if (p1.second != p2.second) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}


int main()
{
    ll n, k;
    cin >> n >> k;
    vector<pll> times(n);


    REPi(n) {
        ll a,b;
        cin >> a >> b;
        times[i] = make_pair(a, b);
    }
    // minimise the gaps in end and start time
    // ending time to each classroom
    map<ll, ll> cr;
    REPi(k) cr[0] = k;
    
    // sort by starting time of activities
    ll res = 0;
    sort(times.begin(), times.end(), comp);
    ll l = 0;
    // for every time, look for the classroom with the latest endtime that is < start time
    for (ll i = 0; i < n; ++i) {
        // retrieve the start time
        pii earliest = times[i];

        auto it = cr.lower_bound(earliest.first);
        if (it == cr.begin()) {
        } else {
            --it;
            if (it->second != 0) {
                ll prevEndTime = it->first;
                cr[it->first] -= 1;
                if (cr[it->first] == 0) {
                    cr.erase(it->first);
                }
                res++;
                // it keeps track of the first time that earliest.first goes
                cr[earliest.second] += 1;
            } else {
                // cout << "No room found to finish later than " << earliest.first << '\n';
            }
        }
    }
    
    cout << res << '\n';


    return 0;
}

