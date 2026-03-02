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

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;

const ll N = 100010;
const ll LOGN = 18;

// this array stores the original data that we are performing
// range queries on using the sparse table
ll a[N];

// Sparse Table key idea - Precompute the max of all intervals whose lengths are powers of 2
// This can be done in O(nlogn) time since an interval of length 2^k is decomposed into 2 * 2^(k-1) intervals

// sparseTable[i][l]  = max a[i ... i + 2^l]
ll sparseTable[N][LOGN];
int log2s[N];

void precomp(int n)
{

    // log2s[i] = floor(log_2(i))
    fill(log2s, log2s + N, 0);
    log2s[1] = 0;
    for (int i = 2; i <= n; i++)
        log2s[i] = log2s[i / 2] + 1;

    for (int i = 0; i < n; ++i) {
        //  sparseTable[i][0] = max { a[i... i + 0] } -> itself
        sparseTable[i][0] = a[i];
    }

    for (int l = 1; l < LOGN; ++l) {
        // w = 2 ^ (l - 1)
        int width = (1 << l);
        for (int i = 0; i + width <= n; ++i) {
            int segment_width = width / 2; // segment width = 2^(l - 1)
            // a[i,i+ w) is made up of a[i, i + w / 2) and a[i + w / 2, i + w)
            // min(a[i, ..., i + 2^j - 1]) = MIN [ min(a[i, ... , i + 2^(j - 1) - 1]) , min(a[i + 2^(j - 1) - 1], ...,  a[i + 2^j - 1]) ] 
            sparseTable[i][l] = max(sparseTable[i][l - 1], sparseTable[i + segment_width][l - 1]);
        }
    }
}


// Query [L, R] INCLUSIVE!!!!!
int query(int L, int R)
{
    // find k, such that 2^k <= (r - l + 1)
    int query_interval_length = R - L + 1;

    int k = log2s[query_interval_length];

    /*
    The union of 2 intervals are guaranteed to cover all of the interval [L , R]
        1. A[L][k] = A[L], ..., A[L + 2 ^ k - 1]
        2. A[R - 2^k + 1][k] = A[R - 2^k + 1], ..., A[R]
    */
    int ans = max(
        sparseTable[L][k],
        sparseTable[R - (1 << k) + 1][k]
    );
    
    return ans;
}


int main() {
    // Input the initial array
    ll n; cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    precomp(n);

    ll q; cin >> q;
    for (int j = 0; j < q; j++) 
    {
        ll l, r; cin >> l >> r;

        // Problem: Find max of a[l,r)
        cout << query(l, r - 1) << "\n"; // r - 1 since query is INCLUSIVE [L, R]

    }
}