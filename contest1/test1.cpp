#include <limits>
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>
#include <tuple>
#include <set>
#include <string>
#include <climits>
// #include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<pll> vpll;
typedef set<int> si;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
#define REPi(n) for (int i = 0; i < n; i++)
#define REPj(n) for (int j = 0; j < n; j++)
#define REPk(n) for (int k = 0; k < n; k++)
#define REP1i(n) for (int i = 1; i <= n; i++)
#define REP1j(n) for (int j = 1; j <= n; j++)
#define REP1k(n) for (int k = 1; k <= n; k++)

struct ColumnNode;

struct Node
{
    Node *left, *right, *up, *down;
    ColumnNode *column;
    int rowID;
    Node() : left(this), right(this), up(this), down(this), column(nullptr), rowID(-1) {}
};

struct ColumnNode : public Node
{
    int size;
    string name;
    ColumnNode(string n) : Node(), size(0), name(n)
    {
        column = this; 
    }
};

class DLX
{
public:
    DLX(vvi &matrix, vs &colNames)
    {
        nCols = colNames.size();
        header = new ColumnNode("header");
        build(matrix, colNames);
    }

    void search(int k = 0)
    {
        if (header->right == header)
        {
            // Found a solution
            cout << "Possible" << endl;
            for (Node *n : solution)
            {
                // cout << "Row " << n->rowID << ": ";
                Node *rowNode = n;
                do
                {
                    cout << n->column->name << " ";
                    n = n->right;
                } while (n != rowNode);
                cout << endl;
            }
            cout << endl;
            return;
        }

        // Choose the column with minimum size
        ColumnNode *col = nullptr;
        int minSize = INT_MAX;
        for (ColumnNode *c = (ColumnNode *)header->right; c != header; c = (ColumnNode *)c->right)
        {
            if (c->size < minSize)
            {
                minSize = c->size;
                col = c;
            }
        }

        if (col == nullptr || col->size == 0)
        {
            return;
        }

        cover(col);

        for (Node *row = col->down; row != col; row = row->down)
        {
            solution.push_back(row);
            for (Node *node = row->right; node != row; node = node->right)
            {
                cover(node->column);
            }

            search(k + 1);

            // Backtrack
            solution.pop_back();
            for (Node *node = row->left; node != row; node = node->left)
            {
                uncover(node->column);
            }
        }

        uncover(col);
    }

private:
    ColumnNode *header;
    int nCols;
    vector<Node *> solution;

    void build(vvi &matrix, vs &colNames)
    {
        int nRows = matrix.size();
        vector<ColumnNode *> columns(nCols);
        for (int i = 0; i < nCols; ++i)
        {
            columns[i] = new ColumnNode(colNames[i]);
        }

        for (int i = 0; i < nCols; ++i)
        {
            columns[i]->left = (i == 0) ? header : columns[i - 1];
            columns[i]->right = (i == nCols - 1) ? header : columns[i + 1];
        }
        header->left = columns[nCols - 1];
        header->right = columns[0];

        // Build nodes
        for (int i = 0; i < nRows; ++i)
        {
            Node *rowNode = nullptr; // First node in the row
            for (int j = 0; j < nCols; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    Node *newNode = new Node();
                    newNode->rowID = i;
                    ColumnNode *col = columns[j];
                    newNode->column = col;

                    newNode->down = col;
                    newNode->up = col->up;
                    col->up->down = newNode;
                    col->up = newNode;

                    col->size++;

                    if (rowNode == nullptr)
                    {
                        rowNode = newNode;
                        newNode->left = newNode->right = newNode;
                    }
                    else
                    {
                        newNode->left = rowNode->left;
                        newNode->right = rowNode;
                        rowNode->left->right = newNode;
                        rowNode->left = newNode;
                    }
                }
            }
        }
    }

    void cover(ColumnNode *col)
    {
        col->right->left = col->left;
        col->left->right = col->right;

        for (Node *row = col->down; row != col; row = row->down)
        {
            for (Node *node = row->right; node != row; node = node->right)
            {
                node->down->up = node->up;
                node->up->down = node->down;
                node->column->size--;
            }
        }
    }

    void uncover(ColumnNode *col)
    {
        for (Node *row = col->up; row != col; row = row->up)
        {
            for (Node *node = row->left; node != row; node = node->left)
            {
                node->column->size++;
                node->down->up = node;
                node->up->down = node;
            }
        }
        col->right->left = col;
        col->left->right = col;
    }
};


class Graph
{
    unordered_map<string, set<string> > adjList;

public:
    void addEdge(string v1, string v2)
    {
        adjList[v1].insert(v2);
        adjList[v2].insert(v1);
    }

    bool hasEdge(string v1, string v2)
    {
        auto it = adjList.find(v1);
        if (it != adjList.end())
        {
            return it->second.find(v2) != it->second.end();
        }
        return false;
    }

    bool isQuad(vs q)
    {
        return hasEdge(q[0], q[1]) &&
               hasEdge(q[0], q[2]) &&
               hasEdge(q[0], q[3]) &&
               hasEdge(q[1], q[2]) &&
               hasEdge(q[1], q[3]) &&
               hasEdge(q[2], q[3]);
    }

    // generate quadriplets
    vvs generateQuads(vs vertices)
    {
        int n = vertices.size();
        vvs quads;
        for (int i = 0; i < n - 3; ++i)
        {
            for (int j = i + 1; j < n - 2; ++j)
            {
                for (int k = j + 1; k < n - 1; ++k)
                {
                    for (int l = k + 1; l < n; ++l)
                    {
                        vs quad;
                        quad.push_back(vertices[i]);
                        quad.push_back(vertices[j]);
                        quad.push_back(vertices[k]);
                        quad.push_back(vertices[l]);
                        quads.push_back(quad);
                    }
                }
            }
        }

        return quads;
    }

    bool isClique(vs quad)
    {
        // cout << "checking if ";
        // for (string s : quad) {
        //     cout << s << " ";
        // }
        // cout << "are cliques" << endl;
        return hasEdge(quad[0], quad[1]) &&
               hasEdge(quad[0], quad[2]) &&
               hasEdge(quad[0], quad[3]) &&
               hasEdge(quad[1], quad[2]) &&
               hasEdge(quad[1], quad[3]) &&
               hasEdge(quad[2], quad[3]);
    }
};

void cover(vvi &matrix, si &cols, si &rows, int c, int r)
{
    // for each column j such that matrix[r][j] == 1
    //      for each row i such that matrix[i][j] == 1
    //          delete i from matrix
    //      delete j from matrix

    vi colsToRemove;
    set<int> rowsToRemove;
    for (int col : cols)
    {
        if (matrix[r][col] == 1)
        {
            colsToRemove.push_back(col);
            for (int row : rows)
            {
                if (matrix[row][col] == 1)
                {
                    rowsToRemove.insert(row);
                }
            }
        }
    }

    for (int col : colsToRemove)
    {
        cols.erase(col);
    }
    for (int row : rowsToRemove)
    {
        rows.erase(row);
    }
}

void uncover(vvi &matrix, si &cols, si &rows, int r)
{
    // given a row, restore each column j that matrix[r][j] = 1;
    // restore each row i such that matrix[i][j] = 1;

    REPj(matrix.size())
    {
        if (matrix[r][j] == 1)
        {
            cols.insert(j);
            REPi(matrix[0].size())
            {
                if (matrix[i][j])
                    rows.insert(i);
            }
        }
    }
}
int selectColumn(vvi &matrix, si &cols)
{
    int minCount = INT_MAX;
    int chosenCol = -1;
    for (int col : cols)
    {
        int count = 0;
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i][col] == 1)
            {
                count++;
            }
        }
        if (count < minCount)
        {
            minCount = count;
            chosenCol = col;
        }
    }
    return chosenCol;
}

vi algoX(vvi &matrix, si &rows, si &cols, vi &sol)
{

    if (cols.empty())
    {
        return sol;
    }

    // choose the column with the least number of i
    int c = selectColumn(matrix, cols);
    // int c = *cols.begin();
    if (c == -1)
    {
        vi curr;
        return curr;
    }

    bool foundRow = false;
    for (int r : rows)
    {
        if (matrix[r][c] == 1)
        {
            foundRow = true;
        }
        sol.push_back(r);

        // cover this row and all conflicting rows and cols
        cover(matrix, cols, rows, c, r);

        vi currSol = algoX(matrix, rows, cols, sol);
        if (currSol.size() > 0)
        {
            return currSol;
        }

        // if failure
        // uncover
        sol.pop_back();
        uncover(matrix, cols, rows, r);
    }

    vi curr;
    return curr;
}

int main()
{
    vs vertices(16);
    REPi(16)
    {
        cin >> vertices[i];
    }
    unordered_map<string, int> vInd;
    REPi(16)
    {
        vInd[vertices[i]] = i;
    }

    int n;
    cin >> n;
    Graph g;

    // read in n pairs
    REPi(n)
    {
        string v1, v2;
        cin >> v1 >> v2;
        g.addEdge(v1, v2);
    }

    vvs quads = g.generateQuads(vertices);
    vvs cliques;
    for (vs quad : quads)
    {
        if (g.isClique(quad))
        {
            cliques.push_back(quad);
        }
    }
    ll nCliques = cliques.size();

    // REPi(nCliques)
    // {
    // cout << i << "th clique: ";
    // for (string s : cliques[i]) {
    //     cout << s << " ";
    // }
    // cout << endl;
    // }
    ll nV = 16;

    // form a matrix with vertices as the column, cliques as the row
    // apply algorithm X to find a set of cliques that cover every column completely
    vvi matrix(nCliques, vi(nV, 0));
    // populate the ones

    REPi(nCliques)
    {
        vs c = cliques[i];
        for (string s : c)
        {
            matrix[i][vInd[s]] = 1;
        }
    }

    // available rows and columns
    si rows, cols;
    REPi(nCliques) rows.insert(i);
    REPi(16) cols.insert(i);
    vi sol;

    // vi res = algoX(matrix, rows, cols, sol);
    // vector<string> colNames = {"v1", "v2", "v3", "v4", "v5", "v6", "v"};
    vs colNames(16);
    REPi(16) {
        colNames[i] = vertices[i];
    }

    DLX dlx(matrix, colNames);
    dlx.search();


    // if (res.empty())
    // {
    //     cout << "Impossible\n";
    //     return 0;
    // }

    // // res contains a list of cliques to take;
    // cout << "Possible\n";
    // for (int cInd : res)
    // {
    //     vs c = cliques[cInd];
    //     for (string s : c)
    //     {
    //         cout << s << ' ';
    //     }
    //     cout << endl;
    // }

    // for (vs quad : res) {
    //     for (string w : quad) {
    //         cout << w << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
