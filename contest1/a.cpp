#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
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
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

int main()
{
    int n, m;
    cin >> n >> m;
    vll freq(m, 0);
    for (int i = 0; i < n; ++i) {
        int nCards;
        cin >> nCards;
        // cout << " current number of cards reading is "<< nCards << endl;
        for (int j = 0; j < nCards; ++j) {
            int currM;
            cin >> currM;
            freq[currM - 1]++;
            // cout<<"frequency of " << currM << " increased by 1 \n";
        }
    }
    
    cout << *min_element(freq.begin(), freq.end()) << endl;
    return 0;
}
