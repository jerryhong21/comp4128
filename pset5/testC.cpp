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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    // Read adjacency matrix
    vector<vector<ll>> a(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    // Read deletion order
    vector<int> deletions(n);
    for (int i = 0; i < n; i++)
    {
        cin >> deletions[i];
        deletions[i]--; // Convert to 0-based
    }
    // Create add_order by reversing deletions
    vector<int> add_order(n);
    for (int i = 0; i < n; i++)
    {
        add_order[i] = deletions[n - 1 - i];
    }
    // Initialize distance matrix
    vector<vector<ll>> dist(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = a[i][j];
        }
    }
    // Initialize list of added vertices
    vector<int> list_of_added_vertices;
    // Initialize list of sums
    vector<ll> list_of_sums(n, 0);
    for (int k = 0; k < n; k++)
    {
        int u = add_order[k];
        list_of_added_vertices.push_back(u);
        // Update distances using the newly added vertex u
        for (auto vi : list_of_added_vertices)
        {
            for (auto vj : list_of_added_vertices)
            {
                if (dist[vi][u] + dist[u][vj] < dist[vi][vj])
                {
                    dist[vi][vj] = dist[vi][u] + dist[u][vj];
                }
            }
        }
        // Compute the sum of all shortest paths in the current set
        ll sum = 0;
        for (auto vi : list_of_added_vertices)
        {
            for (auto vj : list_of_added_vertices)
            {
                sum += dist[vi][vj];
            }
        }
        list_of_sums[k] = sum;
    }
    // Output the sums in reverse order
    for (int k = n - 1; k >= 0; k--)
    {
        cout << list_of_sums[k] << (k > 0 ? ' ' : '\n');
    }
}
