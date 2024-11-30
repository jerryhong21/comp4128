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

// #include <bits/stdc++.h>
using namespace std;

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
#define pb(n) push_back(n);

ll N, M, Q;

// vector of pair
// <size, population>
// .first = size, .second = population
vll parent(1 << 20);
vector<pair<ll, ll>> subtree(1 << 20);
multiset<ll> populations;

// ll maxP = -1;

ll root(ll x) {
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}


void join(ll x, ll y) {
    // cout << "x = " << x << " has population " << subtree[x].second << " and y = " << y << " with population " << subtree[y].second << endl;
    x = root(x); y = root(y);
    if (x == y) return;
    // cout << "x = " << x << " has population " << subtree[x].second << " and y = " << y << " with population " << subtree[y].second << endl;
    // cout << "joining road " << x << " and road " << y << endl;
    if (subtree[x].first < subtree[y].first) {
        parent[x] = y;
        subtree[y].first += subtree[x].first;
        populations.erase(populations.find(subtree[y].second));
        populations.erase(populations.find(subtree[x].second));
        subtree[y].second += subtree[x].second;
        populations.insert(subtree[y].second);
    } else {
        parent[y] = x;
        subtree[x].first += subtree[y].first;
        populations.erase(populations.find(subtree[x].second));
        populations.erase(populations.find(subtree[y].second));
        subtree[x].second += subtree[y].second;
        populations.insert(subtree[x].second);
    }
}

struct Query {
    char c;
    ll a;
    ll b;
};

ll maxPopulation() {
    return populations.empty() ? -1 : *populations.rbegin();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    vll originalCities(N);

    // a log of all populations, from beginning to end
    vector<vll> pLog(N);

    vector<pair<ll, ll>> originalRoads(M);
    vector<Query> queries(Q);

    // <size, population> of original cities
    REPi(N) {
        ll currP;
        cin >> currP;
        originalCities[i] = currP;
        pLog[i].pb(currP);
    }
    // REPi(N)
    // {
    //     cout << "Last population for town " << i << " was " << pLog[i].back() << endl;
    // }


    REPi(M) {
        // roads
        ll s,t;
        cin >> s >> t;
        originalRoads[i] = make_pair(s - 1, t - 1);
    }

    vll finalCities{originalCities};
    set<ll> roadsToRemove;
    REPi(Q) {
        char currCommand;
        ll currA, currB;
        cin >> currCommand;
        if (currCommand == 'P') {
            // has b
            cin >> currA >> currB;
            finalCities[currA - 1] = currB;
            pLog[currA - 1].pb(currB);
        } else if (currCommand == 'D') {
            // b = -1
            cin >> currA;
            currB = -1;
            roadsToRemove.insert(currA - 1);
        }
        // currA are 1 indexed
        queries[i] = {currCommand, currA, currB};
    }
    REPi(N) pLog[i].pop_back();

    // construct a union find with finalCities and originalRoads \ roadsToRemove
    // init
    REPi(N) {
        parent[i] = i;
        // subtree size were all 1
        subtree[i] = make_pair(1, finalCities[i]);
        // maxP = max(maxP, finalCities[i]);
        populations.insert(finalCities[i]);
    }

    // join all roads
    REPi(M) {
        if (roadsToRemove.find(i) == roadsToRemove.end()) {
            // if i was NOT removed
            join(originalRoads[i].first, originalRoads[i].second);
            // cout << "Joining roads " << originalRoads[i].first << " and  " << originalRoads[i].second << endl;
        }
    }


    
    vll res;
    res.pb(maxPopulation());
    // cout << maxPopulation() << endl;

    // now reverse query everything
    for (ll i = Q -1 ; i >= 0; --i) {
        Query q = queries[i];
        if (q.c == 'D') {
            join(originalRoads[q.a - 1].first, originalRoads[q.a - 1].second);
        } else if (q.c == 'P') {
            
            ll oldPop = finalCities[q.a - 1];

            // this is problematic - what if a city was updated multiple times
            // ll diff = originalCities[q.a - 1] - finalCities[q.a - 1];
            ll diff = pLog[q.a - 1].back() - finalCities[q.a - 1];
            finalCities[q.a - 1] = pLog[q.a - 1].back();
            pLog[q.a-1].pop_back();

            // cout << "b = " << q.b << " ";
            // cout << "City " << q.a - 1 << " originally had population " << oldPop << ", update now to " << finalCities[q.a - 1] << endl;

            populations.erase(subtree[root(q.a - 1)].second);
            subtree[root(q.a-1)].second += diff;
            populations.insert(subtree[root(q.a - 1)].second);
        }
        if (i != 0) res.pb(maxPopulation());
    }

    for (ll i = res.size() - 1; i >= 0; --i) cout << res[i] << endl;


    return 0;
}
