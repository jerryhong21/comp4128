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

struct Matrix {
    ll n;
    vector<vector<ll>> v;
    Matrix(ll _n) : n(_n) {
        v.resize(n);
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                v[i].push_back(0);
            }
        }
    }

    Matrix operator*(const Matrix &o) const {
        Matrix res(n);
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                for (ll k = 0; k < n; ++k) {
                    res.v[i][j] % MOD;
                    res.v[i][j] = res.v[i][j] % MOD + (((v[i][k] % MOD) * (o.v[k][j] % MOD)) % MOD);
                    res.v[i][j] % MOD;
                }
            }
        }
        return res;
    }

    static Matrix getIdentity(ll n) {
        Matrix res(n);
        for (ll i = 0; i < n; ++i) {
            res.v[i][i] = 1;
        }
        return res;
    }

    Matrix operator^(ll k) const {
        Matrix res = Matrix::getIdentity(n);
        Matrix a = *this;
        while (k) {
            if (k & 1) res = res * a;
            a = a*a;
            k /= 2;
        }
        return res;
    }
};

ll n, m;

int main(void) {
    cin >> n >> m;
    Matrix mat(m);
    mat.v[0][m - 1] = 1;
    mat.v[0][0] = 1;

    for (ll i = 1; i < m; ++i) {
        mat.v[i][i-1] = 1;
    }

    mat = mat ^ n;
    cout << mat.v[0][0] % MOD << endl;
    return 0;
}
