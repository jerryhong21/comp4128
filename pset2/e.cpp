#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll N, M, Q;

vll parent;
vector<pair<ll, ll>> subtree;

// population_counts[p] = k denotes there are k regions with population = p
map<ll, int> population_counts;
ll max_population = 0;

// iterative
ll root(ll x)
{
    while (parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void join(ll x, ll y)
{
    x = root(x);
    y = root(y);
    if (x == y) return;
    
    // when we join x and y, we remove their individual population and add a new entry in population_count of the merged poppulation
    population_counts[subtree[x].second]--;
    if (population_counts[subtree[x].second] == 0)
        population_counts.erase(subtree[x].second);

    population_counts[subtree[y].second]--;
    if (population_counts[subtree[y].second] == 0)
        population_counts.erase(subtree[y].second);

    parent[y] = x;
    subtree[x].first += subtree[y].first;
    subtree[x].second += subtree[y].second;

    population_counts[subtree[x].second]++;
    if (subtree[x].second > max_population)
        max_population = subtree[x].second;
        // if one of the populations we erased was max population, then
    else if (population_counts.find(max_population) == population_counts.end())
        max_population = population_counts.rbegin()->first;
}

struct Query
{
    char c;
    ll a;
    ll b;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    parent.resize(N);
    subtree.resize(N);

    vll originalCities(N);
    vector<vll> pLog(N);
    vector<pair<ll, ll>> originalRoads(M);
    vector<Query> queries(Q);

    // storing a log of populations
    // pLog[i] = a log of populations in chronological order
    for (ll i = 0; i < N; i++)
    {
        ll currP;
        cin >> currP;
        originalCities[i] = currP;
        pLog[i].push_back(currP);
    }

    for (ll i = 0; i < M; i++)
    {
        ll s, t;
        cin >> s >> t;
        originalRoads[i] = make_pair(s - 1, t - 1);
    }

    vll finalCities = originalCities;
    vector<bool> roadsToRemove(M, false);

    // for each query
    for (ll i = 0; i < Q; i++)
    {
        char currCommand;
        ll currA, currB;
        cin >> currCommand;
        // keep track of population change
        // update populations
        if (currCommand == 'P')
        {
            cin >> currA >> currB;
            finalCities[currA - 1] = currB;
            pLog[currA - 1].push_back(currB);
        }
        else if (currCommand == 'D')
        {
            // record removal of codes
            cin >> currA;
            currB = -1;
            roadsToRemove[currA - 1] = true;
        }
        // store the query
        queries[i] = {currCommand, currA, currB};
    }

    // initialise the union find
    for (ll i = 0; i < N; i++)
    {
        parent[i] = i;
        subtree[i] = make_pair(1, finalCities[i]);
        population_counts[finalCities[i]]++;
        if (finalCities[i] > max_population)
            max_population = finalCities[i];
    }

    // join the final roads
    for (ll i = 0; i < M; i++)
    {
        if (!roadsToRemove[i])
        {
            join(originalRoads[i].first, originalRoads[i].second);
        }
    }

    vector<ll> res;
    res.push_back(max_population);

    // go back in queries
    for (ll i = Q - 1; i >= 0; --i)
    {
        Query q = queries[i];
        // for each query, either we can join up the orads
        if (q.c == 'D')
        {
            join(originalRoads[q.a - 1].first, originalRoads[q.a - 1].second);
        }
        else if (q.c == 'P')
        {
            // if it's a population difference, then it must been that the log of the city has at least 2 entries
            // this current chance, and its original population
            ll city = q.a - 1;
            ll currPop = finalCities[city];
            ll prevPop = pLog[city][pLog[city].size() - 2];
            ll diff = prevPop - currPop;
            // update the population of city
            finalCities[city] = prevPop;
            pLog[city].pop_back();

            ll r = root(city);

            // decrement, and delete this city of the population tree that we keep
            population_counts[subtree[r].second]--;
            if (population_counts[subtree[r].second] == 0)
                population_counts.erase(subtree[r].second);
            
            // because this city might already be part of a region
            // we can calculate the difference and add the offset to the population of this entire region
            subtree[r].second += diff;

            population_counts[subtree[r].second]++;
            if (subtree[r].second > max_population)
                max_population = subtree[r].second;
            else if (population_counts.find(max_population) == population_counts.end())
                max_population = population_counts.rbegin()->first;
        }
        if (i != 0)
            res.push_back(max_population);
    }

    string output;
    for (ll i = res.size() - 1; i >= 0; --i)
    {
        output += to_string(res[i]) + '\n';
    }
    cout << output;

    return 0;
}
