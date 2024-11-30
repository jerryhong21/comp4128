#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// const ll INF = (1LL << 59);
// const ll INF = (1LL << 30);
const int INF = 1e9;

const int N = 200020, H = 1000010;

int n;

struct cmp
{
    bool operator()(pair<int, int> t1, pair<int, int> t2)
    {
        return t1.second < t2.second;
    }
};
int main(void) {

    cin >> n;

    int maxExp = -1;

    vector<pair<int, int>> fruit;
    for (int i = 0; i < n; ++i) {
        int e,h;
        cin >> e >> h;
        fruit.push_back({e,h});
        maxExp = max(maxExp, e);
    }

    sort(fruit.begin(), fruit.end(), [&](const auto &p1, const auto &p2) {
        return p1.first > p2.first;
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    // keeps track of the currnet fruit that we have become eligible to eat
    int l = 0;
    ll res = 0;
    // going down in day count, pushing everything that has just become consumable into the hap
    for (int day = maxExp; day >= 1; --day) {
        while (l < n && fruit[l].first >= day) {
            pq.push(fruit[l]);
            l++;
        }
        if (pq.empty()) continue;
        res += pq.top().second;
        pq.pop();
    }
    cout << res << endl;
    return 0;



    // // for every day, keep on pushing fruit that is eatable
    // // keep track of the left fruit that is still eatable

    // // the heap stores every fruit that has not expired, 
    // int l = 0;
    // for (l < n) {
    //     int minExp = fruit[l].first;
    //     while (l < n && fruit[l] <= minExp) {
    //         pq.push(fruit[l]);
    //         ++l;
    //     }
    //     // everything in the heap is less than minExp, consume the one with the largest happiness
    //     // pop 


    // } 



    // // sort by expiry date
    // // put everything that expires before a specific day into a heap sorted by happiness
    

}