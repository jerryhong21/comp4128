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

// ld grad(pt a, pt b) {
//     ll rise = b.y - a.y;
//     ll run = b.x - a.x;
//     if (llabs(run) <= EPS) {
//         return INF;
//     }
//     return static_cast<ld>(rise) / run;
// } 

int n;
const int N = 100010;
vector<pt> pts;


bool valid(int p1, int p2) {
    pt a = pts[p1], b = pts[p2];
    unordered_set<int> toRemove;
    toRemove.insert(p1); toRemove.insert(p2);

    pt vecAB = b - a;

    // earse every point that also lie on the line of a->b
    for (int i = 2; i < n; ++i) {
        pt currVec = pts[i] - a;
        if (cross(vecAB, currVec) == 0) {
            toRemove.insert(i);
        }
    }
    // out of everything we have NOT REMOVED
    vector<pt> rem;
    for (int i = 0; i < n; ++i) {
        if (toRemove.find(i) == toRemove.end()) {
            rem.push_back(pts[i]);
        }
    }

    // rem contains all the points that are left
    // check if rem forms a straight line
    if (rem.size() <= 2) return true;
    pt XY = rem[0] - rem[1];
    for (int i = 2; i < rem.size(); ++i) {
        pt currXY = rem[i] - rem[1];
        if (cross(XY, currXY) != 0) return false;
    }
    return true;
    
}

int main(void)
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll X, Y;
        cin >> X >> Y;
        pts.push_back(pt(X,Y));
    }

    // fix first 3 points: x,y,z
    // x,y on same line
    // x,z on same line
    // y,z on same line

    // assume 2 points on same line: XY
    // cross XY with every other point, if 0, remove that point
    // check if the remaining points are on a line
    // arbitrarily choose the first three points inputted
    for (int x = 0; x < 3; ++x) {
        for (int y = x + 1; y < 3; ++y) {
            // we assume x, y lie on a line
            // we erase everything on the line of x,y
            // and check if everything else lies on a straight line
            if (valid(x,y)) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    
    cout << "NO\n";
    return 0;


}
