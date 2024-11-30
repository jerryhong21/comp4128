#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
// #include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef pair<char, int> pci;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

string s;

pci findLeast(string s, int l) {

    char least = 'z';
    ll n = s.size();
    for (int i = l; i < n; ++i) {
        if (s[i] <= least) {
            least = s[i];
        }
    }
    ll total = 0;
    for (int i  = l; i < n; ++i) {
        if (s[i] == least) total++;
    }

    return make_pair(least, total);

}

int main()
{
    ll n = s.size();

    cin >> s;
    
    string t;
    string u;
    
    // keep track of how many we have popped from s
    ll ls = 0;
    auto p = findLeast(s, ls);
    char leastChar = p.first;

    ll freq = p.second;

    while (freq > 0)
    {
        // once exhausted, find the new one
        char curr = s[ls];
        if (curr == leastChar) {
            freq--;
            u.push_back(curr);
            ls++;
        } else {
            t.push_back(curr);
            ls++;
        }

        if (freq == 0) {
            auto p = findLeast(s, ls);
            leastChar = p.first;
            freq = p.second;
        }

        while (!t.empty() && t.back() <= leastChar) {
            u.push_back(t.back());
            t.pop_back();
        }

    }

    while (!t.empty()) {
        u.push_back(t.back());
        t.pop_back();
    }

    cout << u << '\n';


    return 0;
}
