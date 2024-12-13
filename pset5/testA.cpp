#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;

int n, k;
bool exit_found = false;
const int N = 1e5 + 10;

// first value is the vertex, second value is the level it's at.
vector<vector<ll>> list;
vector<ll> dist;

bool bfs() {
    ll start = 0;
    ll end = 2*n;

    queue<pair<int, int>> q;
    vector<bool> visited(2* n + 1, false);

    q.push({start, 0});
    visited[start] = true;

    while (!q.empty()) {
        auto [node, time] = q.front();
        q.pop();

        if (node == end) return true;

        for (int next : list[node]) {
            int next_height = next;
            if (next != 2*n) next_height = next % n;
            if (!visited[next] && next_height > time) {
                visited[next] = true;
                q.push({next, time + 1});
            }
        }
    }
    return false;
}


int main()
{
    cin >> n >> k;
    list.resize(2 * n + 1);
    dist.resize(2 * n + 1, LLONG_MAX);

    vector<vector<bool>> tower(2, vector<bool>(n));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            char possible;
            cin >> possible;
            if (possible == '-') {
                tower[i][j] = true;
            } else if (possible == 'X') {
                tower[i][j] = false;
            }
        }
    }
    
    // CONSTRUCT THE GRAPH
    int endNode = 2*n;

    for (int level = 0; level < 2; level++) {
        for (int i = 0; i < n; i++) {
            if (!tower[level][i]) continue;

            int currspot = i;
            int nextspot = i + 1;
            int boundary = n;

            if (level == 1) {
                nextspot += n;
                currspot += n;
                boundary = 2*n;
            }

            // if it will jump to the end then stop
            if (nextspot >= boundary) {
                list[currspot].push_back(endNode);
                continue;
            }

            // if exists tower in the next spot
            if (tower[level][i + 1]) {
                // double ting
                list[currspot].push_back(nextspot);
                list[nextspot].push_back(currspot);
            }

            // jumping
            if (currspot + k < boundary) {
                int newlevel;
                if (level == 0) newlevel = 1;
                if (level == 1) newlevel = 0;

                // if not dangerous jump.
                if (tower[newlevel][i+k]) {
                    if (newlevel == 0) {
                        // go down the indices since jumping from right wall
                        list[currspot].push_back(currspot - n + k);
                    } else if (newlevel == 1) {
                        // just + k 
                        list[currspot].push_back(i + n + k);
                    }
                } 
            } else {
                // since itll go on the boundary means you reach the end
                list[currspot].push_back(endNode);
            }
        }
    }

    exit_found = bfs();

    if (exit_found) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}