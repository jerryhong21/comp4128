#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <unordered_map>
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

const double EPS = 1e-8;
#define x first
#define y second


pt operator-(pt a, pt b) {
    return pt(a.x - b.x, a.y - b.y);
}

bool zero(ll x) {
    return llabs(x) <= EPS;
}

ll cross(pt a, pt b) {
    return a.x * b.y - a.y * b.x;
}

int n;
const int N = 100010;
vector<pt> points;


string tokenise(ll a, ll b) {
    return to_string(a) + " " + to_string(b);
}

string tokenise(pt a) {
    return to_string(a.x) + " " + to_string(a.y);
}

int main(void) {
    cin >> n;
    unordered_map<string, int> idx;

    for (int i = 0; i < n; ++i) {
        ll currX, currY;
        cin >> currX >> currY;
        points.push_back(pt(currX, currY));
        idx[tokenise(points.back())] = i;    
    }

    // sort points in increasing X and increasing Y
    sort(points.begin(), points.end());

    // pick any 2 points find the third point that makes the smallest cross product with them
    // int p1 = 0, p2 = 1;
    pt p1 = points[0];
    pt p2 = points[1];
    // int p1 = idx[tokenise(points[0].first, points[0].second)];
    // int p2 = idx[tokenise(points[1].first, points[1].second)];

    // int p1 = 0, p2 = 1;
    pt p3 = points[2];

    ll minCross = INF;
    for (int i = 2; i < n; ++i) {
        // if (i == p1 || i == p2) continue;
        ll currCross = llabs(cross(p2 - p1, p2 - points[i]));
        if (currCross < minCross && currCross != 0) {
            // p3 = idx[tokenise(points[i].first, points[i].second)];
            p3 = points[i];
            minCross = currCross;
        }
    }
    cout << idx[tokenise(p1)] + 1 << " " << idx[tokenise(p2)] + 1<< " " << idx[tokenise(p3)] + 1 << endl;
    // cout << p1 + 1 << " " << p2 + 1 << " " << p3 + 1 << endl;

}
