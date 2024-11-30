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



int n;
const ll N = 1e7 + 5;
bool marked[N + 1];
vector<int> primes;

int main(void) {
    cin >> n;
    vector<int> res1;
    vector<int> res2;

    for (int i = 0; i <= N; ++i) {
        marked[i] = false;
    }
    for (int i = 2; i <= N; i++) {
        if (!marked[i]) {
            primes.push_back(i);
            for (int j = 2*i; j <= N; j += i) {
                marked[j] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int curr;
        cin >> curr;
        if (!marked[curr]) {
            res1.push_back(-1);
            res2.push_back(-1);
            continue;
        }

        int smallp = 0;
        for (int p : primes) {
            if (curr % p == 0) {
                smallp = p;
                break;
            }
        }

        while (curr % smallp == 0) {
            curr /= smallp;
        }

        if (curr == 1) {
            res1.push_back(-1);
            res2.push_back(-1);
            continue;
        }
        res1.push_back(curr);
        res2.push_back(smallp);
    }

    for (int i = 0; i < n; ++i) {
        cout << res1[i] << ' ';
    }
    cout << endl;
    
    for (int i = 0; i < n; ++i) {
        cout << res2[i] << ' ';
    }
    cout << endl;

    return 0;
}
