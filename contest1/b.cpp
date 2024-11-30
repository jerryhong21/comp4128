#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
#include <tuple>
#include <string>
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
    // split into its rows, store as vectors
    // figure out number of elements in each row

    int n;
    string s;
    cin >> n >> s;

    // n vectors, each representing a layer
    vvi layers(n);
    vi nChars(n);

    int blockSize = 2*n -2;
    int nCompleteBlock = s.size() / blockSize;
    int remChars = s.size() % blockSize;
    
    for (int i = 0; i < n; i++) {
        nChars[i] = 2 * nCompleteBlock;
    }
    nChars[0] = nCompleteBlock, nChars[n - 1] = nCompleteBlock;
    // now deal with remaining chars

    int currRow = 0;
    bool directionUp = false;
    // cout << "remChars = " << remChars << " and rows = "<< n << endl;
    for (int i = 0; i < remChars; i++) {
        if ((currRow == n - 1) || (currRow == 0)) {
            directionUp = !directionUp;
        }
        // cout << "i = " << i << endl;
        // cout << "currRow = " << currRow << endl;
        nChars[currRow]++;
        currRow = directionUp ? currRow + 1 : currRow - 1;

    }

    // cout << "There are " << nCompleteBlock<<" complete blocks" << " and "<< remChars << "remaining chars\n";
    // for (int i = 0; i < n; i++) {
    //     cout << "Layer " << i << " has " << nChars[i] << " characters \n";
    // }

    // construct the layer arrays
    int progress = 0;
    for (int i = 0; i < n; i++) {
        int numChars = nChars[i];
        for (int j = 0; j < numChars; j++) {
            layers[i].push_back(s[progress]);
            progress++;
        }
    }

    // int k = 1;
    // for (vi layer : layers) {
    //     cout << "At layer " << k << endl;
    //     for (char num : layer) {
    //         cout << num << ", ";
    //     }
    //     cout << endl;
    //     k++;
    // }

    // // after the first character, a point is hit after every n-1 chars are placed
    int currCharsPlaced = 0;

    // // direction cna only be down or up
    currRow = 0;
    vi rowProgress(n, 0);
    directionUp = false;
    string res;
    for (int i = 0; i < s.size(); i++) {
        if ((currRow == n - 1) || (currRow == 0)) {
            directionUp = !directionUp;
        }
        res.push_back(layers[currRow][rowProgress[currRow]]);
        rowProgress[currRow]++;

        currRow = directionUp ? currRow + 1 : currRow - 1;
    }

    cout << res << endl;

    return 0;
}
