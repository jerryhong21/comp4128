#include <bits/stdc++.h>

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

    if ((sum * product) == stoll(n)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}