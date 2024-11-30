#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <queue>
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
typedef tuple<ll, ll, ll> t3l;

#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)
#define RANGE(vec) (vec).begin(), (vec).end()

ll n, m, s;

// compare by decreasing cost
struct CompareCost
{
    bool operator()(t3l t1, t3l t2)
    {
        return get<2>(t1) > get<2>(t2);
    }
};

bool compStudents(t3l t1, t3l t2)
{
    return get<1>(t1) > get<1>(t2);
}

bool bugsComparator(pll p1, pll p2) {
    return p1.first > p2.first;
}

// check if t days is possible
bool dayPossible(ll t, vector<t3l> &students, vector<pll> comp) {
    // create a min-heap which current students that can solve the hardest unresolved problem
    priority_queue<t3l, vector<t3l>, CompareCost> pq;

    ll l = 0;
    ll currComp = comp[l].first, currCost = 0;

    ll sPointer = 0;
    bool valid = false;
    while (l < m) {
        // push all students that have ability above this threshold
        while (sPointer < n && get<1>(students[sPointer]) >= currComp) {
            pq.push(students[sPointer]);
            sPointer++;
        }

        // pop off the first student, and that student is able to do t tasks in t days
        if (pq.empty()) return false;

        t3l currStudent = pq.top();
        pq.pop();
        if (currCost + get<2>(currStudent) > s) return false;
        currCost += get<2>(currStudent);

        ll k = l + t;
        while (l < m && l < k) {
            ll taskIdx = comp[k].second;
            l++;
        }

        if (l >= m) return true;
        currComp = comp[l].first;
    }
    return l >= m;
}

int main()
{

    cin >> n >> m >> s;
    vll comp(m), ability(n), cost(n);
    REPi(m) cin >> comp[i];
    REPi(n) cin >> ability[i];
    REPi(n) cin >> cost[i];

    vector<t3l> students(n);
    vector<pll> compIndex(m);

    REPi(n) students[i] = make_tuple(i, ability[i], cost[i]);
    REPi(m) compIndex[i] = make_pair(comp[i], i);

    // sort by increasing ability
    // sort bugs by decreasing complexity
    sort(RANGE(students), compStudents);
    sort(RANGE(compIndex), bugsComparator);

    // binary search for the number of days possible
    ll l = 1, r = m;
    ll lastRes = -1;

    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (dayPossible(mid, students, compIndex)) {
            r = mid - 1;
            lastRes = mid;
        }
        else l = mid + 1;
    }

    if (lastRes == -1) {
        cout << "NO\n";
        return 0;
    }

    ll minDays = lastRes;
    priority_queue<t3l, vector<t3l>, CompareCost> pq;
    ll currComplexity = compIndex[0].first;
    ll nBugsAllocated = 0, currCost = 0;
    vll alloc(m);
    ll sPointer = 0;
    while (nBugsAllocated < m) {
        while (get<1>(students[sPointer]) >= currComplexity && sPointer < n) {
            pq.push(students[sPointer]);
            sPointer++;
        }
        t3l currStudent = pq.top();
        pq.pop();
        ll k = nBugsAllocated + minDays;
        while (nBugsAllocated < m && nBugsAllocated < k) {
            ll bugNumber = compIndex[nBugsAllocated].second;
            alloc[bugNumber] = get<0>(currStudent) + 1;
            nBugsAllocated++;
        }
        if (nBugsAllocated == m) {
            cout << "YES\n";
            for (ll a : alloc) cout << a << ' ';
            cout << '\n';
            return 0;
        } else {
            currComplexity = compIndex[nBugsAllocated].first;
        }
    }

    return 0;
}
