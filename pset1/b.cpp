#include <iostream>
#include <numeric>

using namespace std;

void helper()
{

    int n;
    cin >> n;

    vector<int> seq(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> seq[i];
    }

    // for each + / -, find max and max - can push into vector
    // keep running sum

    long long runningCount = 0;
    int currMax = seq[0];
    bool pos = seq[0] > 0;

    for (int i = 1; i < n; ++i) {
        // if same sign
        if ((pos && seq[i] > 0) || (!pos && seq[i] < 0)) {
            currMax = max(currMax, seq[i]);
        }
        else if ((pos && seq[i] < 0) || (!pos && seq[i] > 0)) {
            // if switched signs
            runningCount += currMax;
            // cout << "Added " << currMax << " to the input \n";
            currMax = seq[i];
            pos = !pos;
        }
    }

    runningCount += currMax;

    cout << runningCount << endl;
}

int main()

{

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        helper();
    }

    return 0;
}
