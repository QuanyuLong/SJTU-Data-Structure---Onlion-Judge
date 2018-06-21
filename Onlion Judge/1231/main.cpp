#include <iostream>

using namespace std;

class disjointSet{
private:
    struct node{
        int parent, left, right;
        node():parent(0), left(0), right(0) {}
    };
    node * tree;
    int * parent;

    int find(int i)
    {
        if(parent[i] <= 0) return i;
        return find(parent[i]);
    }

    void merge(int root1, int root2)
    {
        if(tree[root1].parent == root2){
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else{
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }

    int LCA(int x, int y, int root)
    {
        int tmp;
        if(root == 0) return -1;
        if((tmp = LCA(x, y, tree[root].left)) > 0) return tmp;
        else if((tmp = LCA(x, y, tree[root].right)) > 0) return tmp;
        else{
            if (tree[root].left) merge(root, tree[root].left);
            if (tree[root].right) merge(root, tree[root].right);
            if ((tmp =  find(x)) == find(y))return tmp;
            else return -1;
        }
    }


public:
    disjointSet(int N)
    {
        int lt,rt;
        tree = new node [N+1];
        parent = new int [N+1] {-1};
        parent[0] = 0;
        for(int i = 1; i <= N; ++i){
            cin>>lt>>rt;
            if(lt) {tree[i].left = lt; tree[lt].parent = i;}
            if(rt) {tree[i].right = rt; tree[rt].parent = i;}
        }
    }
    ~disjointSet()
    {
        delete [] tree;
        delete [] parent;
    }

    int LCA(int x, int y)
    {
        int root =1;
        while(tree[root].parent > 0) root = tree[root].parent;
        return LCA(x, y, root);
    }
};



int main()
{
    int N, x, y;
    cin>>N>>x>>y;
    disjointSet set(N);
    cout<<set.LCA(x, y);
}
