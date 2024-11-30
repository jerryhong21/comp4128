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
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)



vi iterativeHelper(vi &nMarksAbove, int n) {
    // stack to keep track of marks
    // use a dfs
    vi lvls;
    // stack<pair<int, int>> keeps track of totalSize, i
    stack<pii> s;
    s.push(make_pair(1, 0));
    while (!s.empty()) {

        // pop from stack
        pii pair = s.top();
        int currTotalMarks = pair.first;
        int i = pair.second;
        s.pop();

        // if its impossible, then you continue, otherwise, you append the layers

        lvls.push_back(currTotalMarks);


        // impossible case
        if (nMarksAbove[i] > currTotalMarks - 1) {
            cout << "nMarksAbove[" << i << "] = " << nMarksAbove[i] << " is larger than what currTotalMarks = " << currTotalMarks << endl;
            lvls.pop_back();
            continue;
        }

        // less optimal case, push before optimal case
        if (nMarksAbove[i + 1] != nMarksAbove[i]) {
            // lvls.push_back(currTotalMarks + 1);
            s.push(make_pair(currTotalMarks + 1, i + 1));
        }

        // optimal case - marks stay the same
        s.push(make_pair(currTotalMarks, i + 1));
    }
    return lvls;

}

bool helper(vvi &res, vi lvls, vi &nMarksAbove, int currNumMarks, int i, int n)
{
    if (res.size() == 1)
        return true;
    cout << "current total number of marks is " << currNumMarks << endl;
    // impossible case
    if (nMarksAbove[i] > currNumMarks - 1)
    {
        return false;
    }
    // base case: i == n
    // lvls[i] = currNumMarks;
    if (lvls.size() == n)
    {
        res.push_back(lvls);
        return true;
    }

    lvls.push_back(currNumMarks);
    bool valid = helper(res, lvls, nMarksAbove, currNumMarks, i + 1, n);
    // if (!valid && nMarksAbove[i + 1] != nMarksAbove[i]) {
    if (!valid)
    {
        lvls.pop_back();
        lvls.push_back(currNumMarks + 1);
        valid = helper(res, lvls, nMarksAbove, currNumMarks + 1, i + 1, n);
    }

    return valid;
}

int main()
{
    int n;
    cin >> n;
    vi recordedLvls(n);
    REPi(n) cin >> recordedLvls[i];

    // take every optimal path at every position
    // whenever you encountered an impossibility
    // backtrack to the last point where you made a decision

    vi currLvl;
    currLvl.push_back(1);

    int currPointer = 0;
    vvi res;

    helper(res, currLvl, recordedLvls, 1, 0, n);

    // vi best = iterativeHelper(recordedLvls, n);
    // for (int p : best) {
    //     cout << p << ", ";
    // }
    // cout << endl;

    // helper(res, recordedLvls, n);
    // cout << "res = " << endl;
    // for (vi potentialSizes : res) {
    //     for (int p : potentialSizes) {
    //         cout << p << ", ";
    //     }
    //     cout << endl;

    // }
    vi best = res[0];
    // for (int p : best) {
    //     cout << p << ", ";
    // }
    // cout << endl;

    // recordedLvl[i] + 1 - res[i] = marks below

    // res[i] = number of marks
    // recordedLvl[i] = number of marks ABOVE current mark
    // there are recoredeLvl[i] + 1 number of MARKS INCLUDING and ABOVE current mark
    // res[i] - (recoredeLvl[i] + 1) = number of marks UNDER
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += (best[i] - recordedLvls[i] - 1);
    }
    cout << total << endl;

    return 0;
}
