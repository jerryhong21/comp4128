#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXN = 19;
const int MAXMASK = 1 << MAXN;

int dp[MAXMASK][MAXN];

int main(void)
{
    ll n;
    cin >> n;
    int total = n + 1;
    int max_mask = 1 << total;

    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < total; ++i){
        dp[1 << i][i] = 1;
    }

    for (int bset = 1; bset < max_mask; ++bset)
    {
        for (int last = 0; last < total; ++last)
        {
            if (!(bset & (1 << last)))
                continue;
            int pBset = bset ^ (1 << last);
            if (pBset == 0)
                continue;
            for (int cand = 0; cand < total; cand++)
            {
                if (!(pBset & (1 << cand)))
                    continue;
                //  forbidden pairs
                if (last >= 1 && cand == last - 1)
                    continue;
                dp[bset][last] = (dp[bset][last] + dp[pBset][cand]) % MOD;
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < total; ++i)
    {
        res = (res + dp[max_mask - 1][i]) % MOD;
    }
    cout << res << endl;

    return 0;
}