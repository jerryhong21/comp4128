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

using namespace std;
typedef long long ll;

 

string n;

int main(void) {

    ll sum = 0, product = 1;
    cin >> n;

    // string res(n.size());
    for (int i = 0; i < n.size(); ++i) {
        sum += (n[i] - '0');
        product *= (n[i] - '0');
    }

    string res = to_string(sum * product);
    if (n == res) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}