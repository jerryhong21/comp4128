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

int n,k;
int main(void) {
    // end[i] = 1 -> 1 classroom ends at time = i
    map<int, int> end;
    cin >> n >> k;
    // k classrooms end at -1 hour
    end[-1] = k;
    vector<pair<int, int>> iv;
    for (int i = 0; i < n; ++i) {
        ll s,f;
        cin >> s >> f;
        iv.push_back({f, s});
    }
    sort(iv.begin(), iv.end());

    int res = 0;
    // for each interval, look for a class that ends closest to the new starting time
    for (int i = 0; i < n; ++i) {
        // binary search for a key in "end" with the cloest
        auto it = end.lower_bound(iv[i].second);
        if (it == end.begin()) {
            if (it->first >= iv[i].second) {
                continue;
            }
        }
        auto prevIt = prev(it);
        if (prevIt->second == 1) {
            end.erase(prevIt);
        } else {
            prevIt->second -= 1;
        }
        end[iv[i].first] += 1;
        res++;
    }

    cout << res << endl;
}