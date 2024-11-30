#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

using namespace std;

int main()
{

    int n;
    cin >> n;

    vector<string> str(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> str[i];
    }

    int valid = true;

    int currCount = 0;
    for (string s : str)
    {
        if (s == "mumble")
        {
            currCount++;
        }
        else
        {
            if (stoi(s) != currCount + 1)
            {
                cout << "something is fishy\n";
                return 0;
            }
            else
            {
                currCount++;
            }
        }
    }

    valid = currCount == n;

    if (!valid)
    {
        cout << "something is fishy\n";
        return 0;
    }

    cout << "makes sense\n";
    return 0;
}