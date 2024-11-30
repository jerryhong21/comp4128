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

vll findN(ll a)
{
    vll res;
    if (a == 0) {
        res.push_back(0);
        res.push_back(1);
        return res;
    } else if (a < 0)
        return res;

    double n = (1 + sqrt(1 + 8 * a)) / 2;

    if (n == static_cast<ll>(n))
    {
        res.push_back(static_cast<ll>(n));
        return res;
    }

    return res;
}

string findStr(int a, int b, int c, int d, int n, int m) {
    // deal with cases if a = 0, d = 0
    // m, n could both either be 0 or 1
    // we can brute force these combinations

    // constructing a '0..01..1 string
    string s(n, '0');
    s.insert(n, m, '1');

    // move each zero to the other end
    // if moving that zero to the other end causes c to increase by too much
    // then greedily place
    ll currC = 0;
    ll currB = n * m;

    // cout << "m = " << m << endl;
    // cout << "n = " << n << endl;
    // for each zero at the front now
    for (int i = 0; i <= n; i++) {
        // cout << "current string is " << s <<endl;
        // cout << "current C count is " << currC <<endl;
        // cout << "current B count is " << currB <<endl;

        if (currC == c && currB == b) {
            // cout << s << endl;
            return s;
        }

        // tentative currC
        ll tentC = currC + m;
        if (tentC > c) {
            tentC = currC;
            // then find a place to place the last zero
            // at this point, we have moved i zeroes to the back
            ll firstOneInd = n - i - 1;
            // cout << "FirstoneIndex = " << firstOneInd << endl;

            for (ll i = firstOneInd; i < firstOneInd + m; i++) {
                ll ones = i - firstOneInd;
                if (tentC + ones == c)
                {
                    // we have found our position to place the '0'
                    s.erase(0, 1);
                    s.insert(i, 1, '0');
                    return s;
                }
            }
            // if there are no place, return impossible
            return "";
        }

        // move a zero to the end
        s.erase(0, 1);
        // append a zero to the end
        s.push_back('0');
        currC += m;
        currB -= m;
    }
    return "";
}

int main()
{

    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    // number of zeroes
    vll nCand = findN(a), mCand = findN(d);

    if (nCand.size() == 0 || mCand.size() == 0) {
        cout << "impossible\n";
        return 0;
    }

    string s;
    for (ll n : nCand) {
        for (ll m : mCand) {
            if (b + c == m * n) {
                s = findStr(a,b,c,d,n,m);
                if (s.size() > 0) {
                    cout << s << endl;
                    return 0;
                }
            }
        }
    }

    cout << "impossible\n";
    return 0;

}
