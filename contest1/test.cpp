#include <limits>
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
#include <tuple>
#include <set>
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
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

void printQuad(vvs quads)
{
    int i = 0;
    for (vs quad : quads)
    {
        cout << "Quad " << i++ << ": ";
        for (string s : quad)
        {
            cout << s << ", ";
        }
        cout << endl;
    }
}

class Graph
{
public:
    void addEdge(string &node1, string &node2)
    {
        adjList[node1].insert(node2);
        adjList[node2].insert(node1);
    }

    bool hasEdge(string &node1, string &node2) const
    {
        auto it = adjList.find(node1);
        if (it != adjList.end())
        {
            return it->second.find(node2) != it->second.end();
        }
        return false;
    }

    bool isQuadruplet(vs &quadruplet)
    {
        return hasEdge(quadruplet[0], quadruplet[1]) && hasEdge(quadruplet[1], quadruplet[2]) &&
               hasEdge(quadruplet[2], quadruplet[3]) && hasEdge(quadruplet[0], quadruplet[3]);
    }

    vvs solve(vs &vertices)
    {
        vvvs quads = generateQuadruplets(vertices);
        for (vvs &comb : quads)
        {
            if (isQuadruplet(comb[0]) && isQuadruplet(comb[1]) && isQuadruplet(comb[2]) && isQuadruplet(comb[3]))
            {
                return comb;
            }
        }
        vvs res;
        return res;
    }

    vvvs generateQuadruplets(vs &vertices)
    {
        ll combCount = 0;
        vs comb1, comb2, comb3, comb4;
        vvvs res;

        // First quadruplet
        for (int i = 0; i < vertices.size() - 3; ++i)
        {
            for (int j = i + 1; j < vertices.size() - 2; ++j)
            {
                for (int k = j + 1; k < vertices.size() - 1; ++k)
                {
                    for (int l = k + 1; l < vertices.size(); ++l)
                    {
                        // comb1 = vs(vertices[i], vertices[j], vertices[k], vertices[l]);
                        comb1.clear();
                        comb1.push_back(vertices[i]);
                        comb1.push_back(vertices[j]);
                        comb1.push_back(vertices[k]);
                        comb1.push_back(vertices[l]);
                        vs remainingVertices;

                        for (int v = 0; v < vertices.size(); ++v)
                        {
                            if (v != i && v != j && v != k && v != l)
                            {
                                remainingVertices.push_back(vertices[v]);
                            }
                        }

                        // Second quadruplet
                        for (int x = 0; x < remainingVertices.size() - 3; ++x)
                        {
                            for (int y = x + 1; y < remainingVertices.size() - 2; ++y)
                            {
                                for (int z = y + 1; z < remainingVertices.size() - 1; ++z)
                                {
                                    for (int w = z + 1; w < remainingVertices.size(); ++w)
                                    {
                                        // comb2 = vs{remainingVertices[x], remainingVertices[y], remainingVertices[z], remainingVertices[w]};
                                        comb2.clear();
                                        comb2.push_back(remainingVertices[x]);
                                        comb2.push_back(remainingVertices[y]);
                                        comb2.push_back(remainingVertices[z]);
                                        comb2.push_back(remainingVertices[w]);
                                        vs rem2;

                                        for (int v = 0; v < remainingVertices.size(); ++v)
                                        {
                                            if (v != x && v != y && v != z && v != w)
                                            {
                                                rem2.push_back(remainingVertices[v]);
                                            }
                                        }

                                        for (int a = 0; a < rem2.size() - 3; ++a)
                                        {
                                            for (int b = a + 1; b < rem2.size() - 2; ++b)
                                            {
                                                for (int c = b + 1; c < rem2.size() - 1; ++c)
                                                {
                                                    for (int d = c + 1; d < rem2.size(); ++d)
                                                    {
                                                        comb3.clear();
                                                        comb3.push_back(rem2[a]);
                                                        comb3.push_back(rem2[b]);
                                                        comb3.push_back(rem2[c]);
                                                        comb3.push_back(rem2[d]);

                                                        vs final;
                                                        for (int v = 0; v < rem2.size(); ++v)
                                                        {
                                                            if (v != a && v != b && v != c && v != d)
                                                            {
                                                                final.push_back(rem2[v]);
                                                            }
                                                        }

                                                        if (final.size() != 4)
                                                        {
                                                            cout << "Something is wrong\n";
                                                            cout << "Final array is of size " << final.size() << " with elements ";
                                                            for (string s : final)
                                                            {
                                                                cout << s << ", ";
                                                            }
                                                            cout << endl;
                                                        }

                                                        comb4 = final;

                                                        vvs currRes;
                                                        currRes.push_back(comb1);
                                                        currRes.push_back(comb2);
                                                        currRes.push_back(comb3);
                                                        currRes.push_back(comb4);

                                                        printQuad(currRes);

                                                        res.push_back(currRes);

                                                        combCount++;
                                                        cout << combCount << " combinations considered so far\n";
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return res;
    }

private:
    unordered_map<string, set<string> > adjList;
};

int main()
{
    vs vertices;
    string word;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cin >> word;
            vertices.push_back(word);
        }
    }

    // Read the number of pairs of related words
    int m;
    cin >> m;

    Graph graph;
    for (int i = 0; i < m; ++i)
    {
        string word1, word2;
        cin >> word1 >> word2;
        graph.addEdge(word1, word2);
        // cout << "Added edge between " << word1 << " and " << word2 << endl;
    }

    vvs res = graph.solve(vertices);
    cout << "SOLVED\n";
    if (res.empty())
    {
        cout << "Impossible\n";
        return 0;
    }

    if (res.size() == 4)
    {
        cout << "Possible\n";
        for (vs &quad : res)
        {
            for (string &v : quad)
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
