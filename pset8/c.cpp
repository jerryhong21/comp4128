#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <deque>

// #include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;

const ll MOD = 1000 * 1000 * 1000 + 7;

typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef tuple<ll, ll, ll> t3l;

typedef pair<ll, ll> pt;
typedef long double ld;

const double EPS = 1e-5;
#define x first
#define y second

pt operator-(pt a, pt b)
{
    return pt(a.x - b.x, a.y - b.y);
}

bool zero(ld x)
{
    return abs(x) <= EPS;
}

ll cross(pt a, pt b)
{
    return a.x * b.y - a.y * b.x;
}

bool ccw(pt a, pt b, pt c)
{
    return cross(b - a, c - a) > 0;
}

vector<pt> halfHull(vector<pt> pts) {
    vector<pt> res;
    for (int i = 0; i < pts.size(); ++i) {
        while (res.size() >= 2 && ccw(pts[i], res[res.size() - 1], res[res.size() - 2])) {
            res.pop_back();
        }
        res.push_back(pts[i]);
    }
    return res;
}

vector<pt> convexHull(vector<pt> pts) {
    sort(pts.begin(), pts.end());
    vector<pt> top = halfHull(pts);

    reverse(pts.begin(), pts.end());
    vector<pt> bottom = halfHull(pts);

    top.pop_back();
    bottom.pop_back();
    vector<pt> res(top.begin(), top.end());
    res.insert(res.end(), bottom.begin(), bottom.end());
    return res;
}
 
int nA, nB;
const int N = 100010;
vector<pt> ptsA, ptsB;
vector<pt> allPoints;

int main(void)
{
    unordered_set<string> setA;

    cin >> nA;
    for (int i = 0; i < nA; ++i) {
        ll X,Y;
        cin >> X>> Y;
        ptsA.push_back(pt(X,Y));
        allPoints.push_back(pt(X,Y));
        setA.insert(to_string(X) + " " + to_string(Y));
    }

    cin >> nB;
    for (int i = 0; i < nB; ++i) {
        ll X, Y;
        cin >> X >> Y;
        if (setA.find(to_string(X) + " " + to_string(Y)) != setA.end()) {
            cout << "NO\n";
            return 0;
        }
        ptsB.push_back(pt(X, Y));
        allPoints.push_back(pt(X, Y));
    }

    // convexHull of A+B must be exactly A
    vector<pt> totalHull = convexHull(allPoints);
    sort(ptsA.begin(), ptsA.end());
    sort(totalHull.begin(), totalHull.end());

    if (totalHull.size() != ptsA.size()) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < nA; ++i) {
        if (ptsA[i].x != totalHull[i].x || ptsA[i].y != totalHull[i].y) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
 


}
