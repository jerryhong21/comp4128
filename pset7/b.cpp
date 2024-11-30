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

const ll MOD = 1e9 + 7;
const ll INF = (1LL << 59);
// const ll INF = (1LL << 30);
// const int INF = 1e9;
// const int N = 600, K = 100;

int n;

/**
 * 1. you never want to multiply by more than n 
 * 2. find prime factors and exponentiations
 * 3. increase every factor to nearest power of 2
 * 4. sqrt
 * 5. repeat this until all numbers are 1
 */

int primeFactorisation(int n, vector<int> &factors, vector<int> &exponents) {
    int maxExp = 0;
    for (int f = 2; f * f <= n; ++f) {
        int exp = 0;
        if (n % f == 0) factors.push_back(f);
        while (n % f == 0) {
            n /= f;
            exp++;
         }
         maxExp = max(maxExp, exp);
        // cout << "Exponent for the prime factor " << f << " is " << exp << endl;
        if (exp > 0) exponents.push_back(exp);
    }
    if (n != 1) {
        factors.push_back(n);
        exponents.push_back(1);
        maxExp = max(maxExp, 1);
    }
    return maxExp;
}

bool isPow2(int x) {
    return (x & (x - 1)) == 0;
}

int main(void) {
    cin >> n;
    vector<int> factors, exponents;
    int maxExp = primeFactorisation(n, factors, exponents);
    if (maxExp == 0) {
        cout << n <<' ' << 0 << endl;
        return 0;
    }
    ll res = 1;
    for (int f : factors) {
        res *= f;
    }
    if (isPow2(maxExp)) {
        bool valid = true;
        for (int e : exponents) {
            if (e != maxExp) {
                valid = false;
                break;
            }
        }
        if (valid) {
            cout << res << ' ' << static_cast<int>(log2(maxExp)) << endl;
            return 0;
        } 
    }
    if (isPow2(maxExp)) {
        cout << res << ' ' << static_cast<int>(log2(maxExp)) + 1 << endl;
        return 0;

    }
    cout << res << ' ' << static_cast<int>(log2(maxExp)) + 2 << endl;

    return 0;
}



