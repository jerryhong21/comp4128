#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>

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

// const ll INF = (1LL << 59);
ll INF = (1LL << 30);
// const int INF = 1e9;

vector<ll> primefactorize(ll x) {
  vector<ll> factors;
  for (int f = 2; f*f <= x; f++)
    while (x % f == 0) {
      factors.push_back(f);
      x /= f;
    }

  if (x != 1) factors.push_back(x);
  return factors;
}

/** if p does not divide q
 * then report p
 * 
 * if p divides q
 * find all prime facts of q, repeatedly divide p by the smallest prime factors, until p does not divide q
 */

int main(void) {
    int t;
    cin >> t;
    vector<ll> res(t);
    for (int i = 0; i < t; ++i) {
        ll q, p;
        cin >> p >> q;
        
        if (p % q != 0) {
            res[i] = p;
            continue;
        }

        vector<ll> primeFactors = primefactorize(q);
        ll cand = 1;
        for (ll f : primeFactors) {
            // divide p by prime factors until p % q != 0
            ll currP = p;
            while (currP % f == 0) {
                currP /= f;
                if (currP % q != 0) {
                    cand = max(cand, currP);
                    break;
                }
            }
        }

        res[i] = cand;
    }

    for (int i = 0; i < t; ++i) cout << res[i] << '\n';

    return 0;
}
