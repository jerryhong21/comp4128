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
    return cross(b - a, c - a) >= 0;
}

vector<pt> halfHull(vector<pt> pts)
{
    vector<pt> res;
    for (int i = 0; i < pts.size(); ++i)
    {
        while (res.size() >= 2 && ccw(pts[i], res[res.size() - 1], res[res.size() - 2]))
        {
            res.pop_back();
        }
        res.push_back(pts[i]);
    }
    return res;
}

vector<pt> convexHull(vector<pt> pts)
{
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

struct line {
    double a,b,c;
    line(double a_, double b_, double c_)
    {
        a = a_;
        b = b_;
        c = c_;
    }
};

struct halfPlane {
    line l;
    bool neg; // inequality <= or >=
    // halfPlane(line l, bool neg) {
    //     l = line(l.a, l.b, l.c); neg = neg;
    // }
};

pt intersect(line f, line g) {
    double y = (f.a * g.c - f.c * g.a) / (f.b * g.a - f.a * g.b);
    double x = (f.c * g.b - f.b * g.c) / (f.b * g.a - f.a * g.b);
    return pt(x, y);
}

bool inHalfPlane(halfPlane hp, pt q) {
  if (hp.neg) {
    return hp.l.a*q.x + hp.l.b*q.y + hp.l.c <= EPS;
  } else {
    return hp.l.a*q.x + hp.l.b*q.y + hp.l.c >= -EPS;
  }
}

bool inOpenHalfPlane(halfPlane hp, pt q) {
    // check that p doesn't lie on the line
    if (abs(hp.l.a*q.x + hp.l.b*q.y + hp.l.c) <= EPS) {
        return false;
    }

    if (hp.neg) {
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c <= EPS;
    } else {
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c >= -EPS;
    }
}

int n, m, q;
const int N = 310, M = 3010, K = 310;
const int Q = 1e6 + 10;

/**
 * Algorithm:
 * We can precompute how many black points are in each red triangle
 * Check if a black point is in a red triangle through checking half planes
 * This is O(mn)
 * 
 * For each query, we can break down each convex polygon (run it through convex hull to get order)
 * To get non-overlapping triangles, and add each triangle up
 * 
 */
vector<pt> red, black;
unordered_map<string, int> blacksInTriangle;

string tokenise(int p1, int p2) {
    if (p1 > p2) swap(p1,p2);
    return to_string(p1) + " " + to_string(p2);
}

/*
Given 2 points (x0, x1) and (y0, y1)

y(x1-x0) - x(y1-y0) - y0(x1-x0) + x0(y1-y0) = 0

*/

line getLine(pt A, pt B) {
    double x0 = A.x, x1 = B.x;
    double y0 = A.y, y1 = B.y;
    double lineA = y0-y1;
    double lineB = x1-x0;
    double lineC = x0 * (y1-y0)+ y0*(x0-x1);
    return line(lineA, lineB, lineC);
}


// anchor O, and get the number of points in triangle OAB
void processTriangle(int p1, int p2)
{
    pt A = {0.0, 0.0};
    pt B = red[p1], C = red[p2];
    // process AB, AC, BC
    line l1 = getLine(A, B);
    halfPlane hp1 = {l1, false};
    if (!inHalfPlane(hp1, C))
        hp1.neg = true;

    line l2 = getLine(A, C);
    halfPlane hp2 = {l2, false};
    if (!inHalfPlane(hp2, B))
        hp2.neg = true;

    line l3 = getLine(B, C);
    halfPlane hp3 = {l3, false};
    if (!inHalfPlane(hp3, A))
        hp3.neg = true;

    // now we have three half planes, for each black point
    // we check if its in all three halfplanes
    for (int i = 0; i < m; ++i)
    {
        pt currBlack = black[i];
        if (inOpenHalfPlane(hp1, currBlack) && inOpenHalfPlane(hp2, currBlack) && inOpenHalfPlane(hp3, currBlack))
        {
            blacksInTriangle[tokenise(p1, p2)]++;
        }
    }
    // cout << "For vertices " << p1 << ", " << p2 << " there are " << blacksInTriangle[tokenise(p1, p2)] << " black dots\n";
}

int getSignedNumBlackPoints(int p1, int p2) {
    // check the cross product of OA and AB
    pt A = {0.0, 0.0};
    pt B = red[p1], C = red[p2];
    int multiplier = 1;
    if (cross(B - A, C - B) > 0.0) {
        multiplier = -1;
    }
    return multiplier * blacksInTriangle[tokenise(p1,p2)];
}

int main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int X,Y;
        cin >> X >> Y;
        red.push_back(pt(X,Y));
    }

    for (int i = 0; i < m; ++i) {
        int X, Y;
        cin >> X >> Y;
        black.push_back(pt(X,Y));
    }

    // process all triangles with respect to origin
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // process triangle OIJ
            processTriangle(i,j);
        }
    }
    
    // for each query
    vector<int> res;
    cin >> q;
    for (int i = 0; i < q; ++i) {

        int k; cin >> k;
        vector<int> queryPts;
        for (int j = 0; j < k; ++j) {
            int cur; cin >> cur;
            queryPts.push_back(cur - 1);
        }
        int currRes = 0;
        // queryPts is given in clockwise order so we can use
        for (int j = 0; j < k; ++j) {
            // j and j + 1 % k
            int A = j, B = (j + 1) % k;
            // find the signd area of OAB
            currRes += getSignedNumBlackPoints(queryPts[A], queryPts[B]);
        }
        res.push_back(currRes);
    }

    for (int i = 0; i < q; ++i) {
        cout << res[i] << endl;
    }

}
