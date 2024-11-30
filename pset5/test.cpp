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
 * 3. increase every factor to have even exponentiations
 * 4. sqrt
 * 5. repeat this until all numbers are 1
 */

void primeFactorisation(int n, vector<int> &factors, vector<int> &exponents) {
    for (int f = 2; f * f <= n; ++f) {
        int exp = 0;
        if (n % f == 0) factors.push_back(f);
        while (n % f == 0) {
            n /= f;
            exp++;
        }
        if (exp > 0) exponents.push_back(exp);
    }
}

// check if everything is even
bool exponentEven(vector<int> &exp) {
    for (int i : exp) {
        if (i %2!=0) return false;
    }
    return true;
}
bool allOne(vector<int> &exp) {
    for (int i : exp) {
        if (i != 1) return false;
    }
    return true;
}

bool scaleUp(vector<int> &exp) {
    bool needed = false;
    for (int e : exp) {
        if (e % 2 != 0) {
            e++;
            needed = true;
        }
    }
    return needed;
}

int main(void) {
    cin >> n;
    vector<int> factors, exponents;
    primeFactorisation(n, factors, exponents);

    int steps = 0;
    while (!allOne(exponents)) {
        // scale up to all even
        bool needed = scaleUp(exponents);
        if (needed) steps++;
        // divide
        for (int i : exponents) {
            i /= 2;
        }
        steps++;
    }
    cout << steps << endl;


    return 0;
}



