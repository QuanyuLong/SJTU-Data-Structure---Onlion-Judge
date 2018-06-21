#include <iostream>
using namespace std;

class adjustGraph
{
private:
    struct edgeNode
    {
        int end;
        edgeNode *next;

        edgeNode(int e,edgeNode *p = NULL) :end(e), next(p) {}
    };
    edgeNode **verList;
    int vers;

public:
    adjustGraph(int vSize) :vers(vSize),verList(new edgeNode*[vSize + 1]()) {}
    ~adjustGraph()
    {
        for (int i = 1;i <= vers;++i){
            if (verList[i]){
                edgeNode*p = verList[i]->next;
                while (p){
                    edgeNode *q = p->next;
                    delete p;
                    p = q;
                }
            }
        }
        delete[]verList;
    }

    bool insert(int u, int v)
    {
        verList[u] = new edgeNode(v, verList[u]);
        return true;
    }

    void dfs(int start,int M, bool * visited, int * result)
    {
        if (M == 0){
            ++*result;
            return;
        }
        if (verList[start])
        {
            edgeNode *p = verList[start];
            while (p)
            {
                if (!visited[p->end])
                {
                    visited[p->end] = true;
                    dfs(p->end, M - 1, visited, result);
                    visited[p->end] = false;
                }
                p = p->next;
            }
        }
    }
};

int main()
{
    int n, m, start, M;
    cin >> n >> m >> start >> M;
    bool * visited = new bool [n] {false};
    adjustGraph graph(n);
    int u, v;
    for (int i = 0;i < m;++i)
    {
        cin >> u >> v;
        graph.insert(u, v);
    }
    visited[start] = true;
    int * result = new int (0);
    graph.dfs(start, M, visited, result);
    cout << *result << endl;
    return 0;
}
