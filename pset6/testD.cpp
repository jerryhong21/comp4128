#include <vector>
#include <cmath>
#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <iomanip>
#define int long long
#define double long double
using namespace std;
const double eps = 1e-11;
const int inf = 0x3f3f3f3f;
const int N = 55, M = 2e4 + 10;
int n, m, h[N], s, t, x, a[M], b[M], c[M];
int head[N], nex[M], to[M], w[M], tot;
inline void ade(int a, int b, int c)
{
    to[++tot] = b;
    nex[tot] = head[a];
    head[a] = tot;
    w[tot] = c;
}
inline void add(int a, int b, int c)
{
    ade(a, b, c);
    ade(b, a, 0);
}
inline int bfs()
{
    queue<int> q;
    q.push(s);
    memset(h, 0, sizeof h);
    h[s] = 1;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = nex[i])
        {
            if (!h[to[i]] && w[i])
            {
                h[to[i]] = h[u] + 1;
                q.push(to[i]);
            }
        }
    }
    return h[t];
}
int dfs(int x, int f)
{
    if (x == t)
        return f;
    int fl = 0;
    for (int i = head[x]; i && f; i = nex[i])
    {
        if (w[i] && h[to[i]] == h[x] + 1)
        {
            int mi = dfs(to[i], min(w[i], f));
            w[i] -= mi, w[i ^ 1] += mi, fl += mi, f -= mi;
        }
    }
    if (!fl)
        h[x] = -1;
    return fl;
}
inline int dinic()
{
    int res = 0;
    while (bfs())
        res += dfs(s, inf);
    return res;
}
inline int check(double mid)
{
    tot = 1;
    memset(head, 0, sizeof head);
    for (int i = 1; i <= m; i++)
        add(a[i], b[i], floor(c[i] / mid));
    return dinic() >= x;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> x;
    s = 1;
    t = n;
    for (int i = 1; i <= m; i++)
        cin >> a[i] >> b[i] >> c[i];
    double l = 0, r = 1e9;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.10Lf\n", l * x);
    return 0;
}
