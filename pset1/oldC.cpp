#include <iostream>
#include <vector>
#include <cmath>
// #include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

// const ll INF = LONG_LONG_MAX >> 2;

ll findN(int a) {
    // if (a == 0) return 0;
    if (a < 0) return -1;
                                                                         
    double n = (1 + sqrt(1 + 8 * a)) / 2;

    if (n == static_cast<int>(n)) {
        return static_cast<int>(n);
    }

    return -1;
}

int main() {

    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    // number of zeroes
    ll n = findN(a), m = findN(d);
    if (n == -1 || m == -1 || b + c != m * n) {
        cout << "impossible\n";
        return 0;
    }

    // deal with cases if a = 0, d = 0
    // m, n could both either be 0 or 1
    // we can brute force these combinations

    

    if (n == 0 && m != -1 && b == 0 && c == 0) {
        string s(m, '1');
        cout << s << endl;
        return 0;
    } else if (m == 0 && n != -1 && b == 0 && c == 0) {
        string s(n, '0');
        cout << s << endl;
        return 0;
    }

    // find k such that kn < b
    ll k = 0;
    if (n != 0) {
        k = b / n;
    }

    // move k 1' to the end
    ll rem = b - k * n;

    string s(n, '0');
    s.insert(s.size(), k, '1');

    if (rem != 0) {
        s.insert(rem, 1, '1');
        if (m - k - 1 >= 0) s.insert(0, m - k - 1, '1');
    }

    cout << s << endl;

    return 0;
}

