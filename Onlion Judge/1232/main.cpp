#include <iostream>
using namespace std;

int N, A, B, position = 0, * path;
bool *mark, **wall;

class disjointSet
{
private:
    int *parent;
public:
    disjointSet(int n) :parent(new int[n + 1])
    {
        for (int i = 1;i <= n;++i) parent[i] = -1;
    }
    ~disjointSet() { delete[]parent; }
    int find(int x)
    {
        if (parent[x] < 0)return x;
        else
        {
            int tmp = parent[x];
            while (parent[tmp] > 0)tmp = parent[tmp];
            int y;
            while (x != tmp)
            {
                y = parent[x];
                parent[x] = tmp;
                x = y;
            }
            return tmp;
        }
    }
    void merge(int root1, int root2)
    {
        if (root1 == root2)return;
        if (parent[root1] < parent[root2])
        {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
        else
        {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
};

int getX(int P)
{
    int left = 1, right = N;
    while (left <= right)
    {
        int mid = left + right >> 1;
        if ((mid*(mid + 1) >> 1) < P)left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

inline int getP(int x, int y)
{
    return ((x*(x - 1) >> 1) + y);
}

bool dfs(int x, int y)
{
    mark[getP(x,y)] = true;
    if (getP(x, y) == B) return true;
    if (wall[0][getP(x, y)] && !mark[getP(x - 1, y - 1)])
    {
        if (dfs(x-1,y-1))
        {
            path[position++] = getP(x - 1, y - 1);
            return true;
        }
    }
    if (wall[1][getP(x, y)] && !mark[getP(x - 1, y)])
    {
        if (dfs(x-1,y))
        {
            path[position++] = getP(x - 1, y);
            return true;
        }
    }
    if ( wall[2][getP(x, y)] && !mark[getP(x + 1, y)])
    {
        if (dfs(x+1,y))
        {
            path[position++] = getP(x + 1, y);
            return true;
        }
    }
    if (wall[3][getP(x, y)] && !mark[getP(x + 1, y + 1)])
    {
        if (dfs(x+1,y+1))
        {
            path[position++] = getP(x + 1, y + 1);
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> N >> A >> B;
    int P, Q;
    int x, y;
    wall = new bool*[4];
    for(int i=0;i<4;++i)wall[i] = new bool[(N*(N + 1) >> 1) + 1]();
    disjointSet dSet(N*(N + 1) >> 1);
    while (cin >> P >> Q)
    {
        x = getX(P);
        y = P - (x*(x - 1) >> 1);
        switch (Q)
        {
        case 0:
            if (y != 1)
            {
                dSet.merge(dSet.find(P), dSet.find(P - x));
                wall[0][P] = wall[3][P - x] = true;
            }
            break;
        case 1:
            if (y != x)
            {
                dSet.merge(dSet.find(P), dSet.find(P - x + 1));
                wall[1][P] = wall[2][P - x + 1] = true;
            }
            break;
        case 2:
            if (x != N)
            {
                dSet.merge(dSet.find(P), dSet.find(P + x));
                wall[2][P] = wall[1][P + x] = true;
            }
            break;
        case 3:
            if (x != N)
            {
                dSet.merge(dSet.find(P), dSet.find(P + x + 1));
                wall[3][P] = wall[0][P + x + 1] = true;
            }
        }
        if (dSet.find(A) == dSet.find(B))break;
    }

    x = getX(A);
    y = A - (x*(x - 1) >> 1);
    mark = new bool[(N*(N + 1) >> 1) + 1]();
    path = new int[(N*(N + 1) >> 1)]();
    if (dfs(x, y)) path[position++] = A;
    for (int i = position - 1;i >= 0;--i) cout << path[i] << ' ';
}
