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
    #include <cfloat>
    #include <bitset>
    #include <deque>

    using namespace std;

    typedef long long ll;
    typedef vector<ll> vll;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef pair<ll, ll> pll;
    typedef pair<int, int> pii;
    typedef vector<pll> vpll;
    typedef pair<char, int> pci;
    #define fori(n) for (int i = 0; i < n; i++)
    #define forj(n) for (int j = 0; j < n; j++)
    #define fork(n) for (int k = 0; k < n; k++)
    #define for1i(n) for (int i = 1; i <= n; i++)
    #define for1j(n) for (int j = 1; j <= n; j++)
    #define for1k(n) for (int k = 1; k <= n; k++)

    #define print(x) cout << #x << "=" << x << endl
    #define print2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
    #define printV(x)         \
        for (auto &i : x)     \
            cout << i << ' '; \
        cout << endl;

    #define pb push_back

    #define all(x) x.begin(), x.end()
    #define sortAll(x) sort(all(x))

    /*
    * cross product
    */

    const long double EPS = 1e-8;
    typedef pair<double, double> pt;
    #define x first
    #define y second

    pt operator-(pt a, pt b) {
    return pt(a.x - b.x, a.y - b.y);
    }

    bool zero(double x) {
    return fabs(x) <= EPS;
    }

    double cross(pt a, pt b) {
    return a.x*b.y - a.y*b.x;
    }

    bool ccw(pt a, pt b, pt c) {
    return cross(b - a, c - a) >= 0;
    }

    ll N, M, Q;
    pt red[105];
    pt black[3005];

    pt originVector = make_pair(0, 0);

    string tokenize(pt point) {
        return to_string(point.x) + " " + to_string(point.y);
    }

    string tokenizeTriangle(int i, int j) {
        int temp = i;
        if (i > j) {
        i = j;
        j = temp;
        }
        return to_string(i) + " " + to_string(j); 
    }

    vector<pt> half_hull(vector<pt> pts) {
    vector<pt> res;
    for (int i = 0; i < pts.size(); i++) {
        // ccw means we have a left turn; we don't want that
        while (res.size() >= 2 &&
            ccw(pts[i], res[res.size()-1], res[res.size()-2])) {
        res.pop_back();
        }
        res.push_back(pts[i]);
    }
    return res;
    }

    vector<pt> convex_hull(vector<pt> pts) {
    sort(pts.begin(), pts.end());
    vector<pt> top = half_hull(pts);

    reverse(pts.begin(), pts.end());
    vector<pt> bottom = half_hull(pts);
    
    top.pop_back();
    bottom.pop_back();
    vector<pt> res(top.begin(), top.end());
    res.insert(res.end(), bottom.begin(), bottom.end());
    return res;
    }


    struct line {
    double a, b, c;
    };

    struct half_plane {
    line l;
    bool neg; // is the inequality <= or >=
    };

    pt intersect(line f, line g) {
    double d = f.a*g.b - f.b*g.a;
    double y = (f.a*g.c - f.c*g.a)/(f.b*g.a - f.a*g.b);
    double x = (f.c*g.b - f.b*g.c)/(f.b*g.a - f.a*g.b);
    return pt(x, y);
    }

    bool in_half_plane(half_plane hp, pt q) {
    if (hp.neg)
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c <= EPS;
    else
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c >= -EPS;
    }

    bool in_half_plane_strict(half_plane hp, pt q) {
    if (hp.neg)
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c < EPS;
    else
        return hp.l.a*q.x + hp.l.b*q.y + hp.l.c > -EPS;
    }

    /*
    * half plane intersection
    */

    vector<pt> intersect_half_planes(vector<half_plane> half_planes) {
    int n = half_planes.size();
    vector<pt> pts;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
        pt p = intersect(half_planes[i].l, half_planes[j].l);
        bool fail = false;
        for (int k = 0; k < n; k++)
            if (!in_half_plane(half_planes[k], p))
            fail = true;
        if (!fail)
            pts.push_back(p);
        }
    }

    vector<pt> res = pts;
    return pts;
    }

    int main(void) {
        cin >> N >> M;
        int x, y;
        fori(N) {
            cin >> x >> y;
            red[i] = make_pair(x, y);
        }
        fori(M) {
            cin >> x >> y;
            black[i] = make_pair(x, y);
        }
        unordered_map<string, int> numBlack;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
            pt p1 = red[i], p2 = red[j];
            if ((abs(p1.x) <= EPS && abs(p1.y) <= EPS) || (abs(p2.x) <= EPS && abs(p2.y) <= EPS)) {
                continue;
            }
            // print2(p1.x, p1.y);
            // print2(p2.x, p2.y);
            // cout << endl;
            line l1 = {-1 * (p1.y - p2.y), p1.x - p2.x, p1.x * (p1.y - p2.y) - p1.y * (p1.x - p2.x)};
            half_plane hp1 = {l1, false};
            if (!in_half_plane(hp1, originVector)) {
                hp1.neg = true;
            }
            line l2 = {-1 * p2.y, p2.x, 0};
            half_plane hp2 = {l2, false};
            if (!in_half_plane(hp2, p1)) {
                hp2.neg = true;
            }
            line l3 = {-1 * p1.y, p1.x, 0};
            half_plane hp3 = {l3, false};
            if (!in_half_plane(hp3, p2)) {
                hp3.neg = true;
            }
            string tokenizedTriangle = tokenizeTriangle(i, j);
            for (int l = 0; l < M; ++l) {
                if (in_half_plane_strict(hp1, black[l]) && in_half_plane_strict(hp2, black[l]) && in_half_plane_strict(hp3, black[l])) {
                    numBlack[tokenizedTriangle]++;
                }
            }
            }
        }
        // for (auto entry : numBlack) {
        //   print2(entry.first, entry.second);
        // }
        // 
        int Q;
        cin >> Q;
        int firstPointIndex, pointIndex, nextPointIndex, k;
        vector<int> result;
        fori(Q) {
            cin >> k;
            int res = 0;
            cin >> pointIndex;
            pointIndex--;
            firstPointIndex = pointIndex;
            for (int j = 1; j <= k; ++j) {
            if (j != k) {
                cin >> nextPointIndex;
                nextPointIndex--;
            } else {
                nextPointIndex = firstPointIndex;
            }

            if (ccw(originVector, red[pointIndex], red[nextPointIndex])) {
                res += numBlack[tokenizeTriangle(pointIndex, nextPointIndex)];
            } else {
                res -= numBlack[tokenizeTriangle(pointIndex, nextPointIndex)];
            }
            
            pointIndex = nextPointIndex;
            }
            result.push_back(abs(res));
        }
        fori(result.size()) {
            cout << result[i] << endl;
        }
        return 0;
    }