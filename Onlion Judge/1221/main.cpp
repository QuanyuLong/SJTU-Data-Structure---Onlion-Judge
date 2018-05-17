#include <iostream>
#include <cstring>

using namespace std;


template <class elemType>
class binarySearchTree {
private:
    struct node {
    elemType data;
    node * left, * right;
    node(const elemType &x, node * lt= NULL, node * rt = NULL):data(x), left(lt), right(rt) {}
    node():left(NULL), right(NULL) {}
    };
    node * root;
    void insert(const elemType & x, node * & root);
    void remove(const elemType & x, node * & root);
    void remove2(const elemType & x, node * & root);
    bool find(const elemType & x, node * root) const;
    void find_ith(const int i, int * k, node * & t, bool &flag);
    void makeEmpty(node * & root);
    void remove_less_than(const elemType & x, node * & root);
    void remove_greater_than(const elemType & x, node * & root);
    void remove_interval(const elemType & lt, const elemType & rt, node * & root);
    void trivial(node * root)const;
    void deleteNode(node * & t);
public:
    binarySearchTree() {root = NULL;}
    ~binarySearchTree() {makeEmpty(root);}
    void insert(const elemType & x) {insert(x, root);}
    void remove(const elemType & x) {remove(x, root);}
    bool find(const elemType & x) const {return find(x, root);}
    bool find_ith(const int i);
    void remove_less_than(const elemType &x) {remove_less_than(x, root);}
    void remove_greater_than(const elemType & x) {remove_greater_than(x, root);}
    void remove_interval(const elemType & lt, const elemType & rt) {remove_interval(lt, rt, root);}
    void trivial()const {trivial(root);}
};

template <class elemType>
bool binarySearchTree<elemType>::find(const elemType & x, node * root)const
{
    if(root == NULL) return false;
    else if(root->data == x) return true;
    else if(root->data < x) return find(x, root->right);
    else return find(x, root->left);
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType & x, node * & root)
{
    if(root == NULL) root = new node (x);
    else if(root->data > x) insert(x, root->left);
    else insert(x, root->right);
}

template <class elemType>
void binarySearchTree<elemType>::remove(const elemType & x, node * & root)
{
    if(root == NULL) return;
    if(root->data > x) remove(x, root->left);
    else if(root->data < x) remove(x, root->right);
    else if(root->left != NULL && root->right != NULL){
        node * tmp = root->right;
        while(tmp->left) tmp = tmp->left;
        root->data = tmp->data;
        remove(tmp->data, root->right);
    }
    else {
        node * tmp = root;
        root = (root->left == NULL)? root->right : root->left;
        delete tmp;
    }
}

template <class elemType>
void binarySearchTree<elemType>::remove2(const elemType & x, node * & root)
{
    if(root == NULL) return;
    if(root->data > x) remove2(x, root->left);
    else if(root->data < x) remove2(x, root->right);
    else if(root->left != NULL && root->right != NULL){
        node * tmp = root->left;
        while(tmp->right) tmp = tmp->right;
        root->data = tmp->data;
        remove2(tmp->data, root->right);
    }
    else {
        node * tmp = root;
        root = (root->left == NULL)? root->right : root->left;
        delete tmp;
    }
}

template <class elemType>
void binarySearchTree<elemType>::deleteNode(node * & t)
{
    if(root->left != NULL && root->right != NULL){
        node ** tmp = & root->right;
        while( (*tmp) ->left) tmp =& (*tmp)->left;
        root->data = (*tmp)->data;
        *tmp = NULL;
    }
    else{
        node * tmp = root;
        root = (root->left == NULL)? root->right : root->left;
        delete tmp;
    }
}

template <class elemType>
void binarySearchTree<elemType>::makeEmpty(node * & root)
{
    if(root->left) makeEmpty(root->left);
    if(root->right) makeEmpty(root->right);
    delete root;
}

template <class elemType>
void binarySearchTree<elemType>::remove_less_than(const elemType & x, node * & root)
{
    if(root == NULL) return;
    if(root->data >= x) remove_less_than(x, root->left);
    else {
        //cout<<root->data<<endl;
        if(root->left) makeEmpty(root->left);
        remove(root->data, root);
        remove_less_than(x, root);
    }
}

template <class elemType>
void binarySearchTree<elemType>::remove_greater_than(const elemType & x, node * & root)
{
    if(root == NULL) return;
    if(root->data <= x) remove_greater_than(x, root->right);
    else {
        //cout<<root->data<<endl;
        if(root->right) makeEmpty(root->right);
        remove2(root->data, root);
        //cout<<root->data<<endl;
        remove_greater_than(x, root);
    }
}

template <class elemType>
void binarySearchTree<elemType>::remove_interval(const elemType & lt, const elemType & rt, node * & root)
{
    if(root == NULL) return;
    if(root->data <= lt) remove_interval(lt, rt, root->right);
    else if(root->data >= rt) remove_interval(lt, rt, root->left);
    else{
        //cout<<root->data<<endl;
        remove(root->data, root);
        remove_interval(lt, rt, root);
        if(root) remove_interval(lt, rt, root->left);
        if(root) remove_interval(lt, rt, root->right);
    }
}

template <class elemType>
void binarySearchTree<elemType>::find_ith(const int i, int * k,  node * & t, bool & flag)
{
    if(*k > i) return;
    if(t == NULL) return;
    find_ith(i, k, t->left, flag);
    if(*k == i) {cout<<t->data<<endl; flag = true;}
    ++*k;
    find_ith(i, k, t->right, flag);
}

template <class elemType>
bool binarySearchTree<elemType>::find_ith(const int i)
{
    int *k = new int (1);
    bool flag = false;
    find_ith(i, k, root, flag);
    return flag;
}

template <class elemType>
void binarySearchTree<elemType>::trivial(node * root)const
{
    if(root->left) trivial(root->left);
    cout<<root->data<<' ';
    if(root->right) trivial(root->right);
}

int main()
{
/*
    binarySearchTree<int> t;

    int a[] = {10, 8, 6, 21, 87, 56, 4, 0 , 11, 3, 22, 7, 5, 34, 1, 2, 9};
    for(int i = 0; i < 17; ++i) t.insert(a[i]);
    t.trivial();
    cout<<endl;
    for(int i = 0; i < 20; ++i) if(!t.find_ith(i)) cout<<"N\n";
    t.remove_greater_than(33);
    t.remove_less_than(3);
    t.remove_interval(6,11);
    //t.trivial();
    t.find_ith(1);
    t.find_ith(4);
    t.find_ith(2);
*/

    /*
    for(int i = 0; i < 10; ++i) t.insert(i);
    t.find_ith(1);
    t.find_ith(2);
    t.find_ith(9);
    t.find_ith(10);
    t.find_ith(11);
    t.trivial();
    */

    binarySearchTree<int> tree;
    int num_of_instructions;
    char instruction[25];
    int ope1, ope2;
    cin>>num_of_instructions;
    for(int i = 0; i < num_of_instructions; ++i){
        cin>>instruction;
        if(strcmp(instruction, "insert") == 0){
            cin>>ope1;
            tree.insert(ope1);
        }
        else if(strcmp(instruction, "delete") == 0){
            cin>>ope1;
            tree.remove(ope1);
        }
        else if(strcmp(instruction, "delete_less_than") == 0){
            cin>>ope1;
            tree.remove_less_than(ope1);
        }
        else if(strcmp(instruction, "delete_greater_than") == 0){
            cin>>ope1;
            tree.remove_greater_than(ope1);
        }
        else if(strcmp(instruction, "delete_interval") == 0){
            cin>>ope1>>ope2;
            tree.remove_interval(ope1, ope2);
        }
        else if(strcmp(instruction, "find") == 0){
            cin>>ope1;
            if(tree.find(ope1)) cout<<"Y\n";
            else cout<<"N\n";
        }
        else if(strcmp(instruction, "find_ith") == 0){
            cin>>ope1;
            if(!tree.find_ith(ope1)) cout<<"N\n";
        }
    }

}


/*
#include <iostream>
#include <cstring>
using namespace std;
#define INF 1<<31

class  binarySearchTree
{
private:
    struct node
    {
        int data, cnt;
        node *left, *right;

        node(int d, node *p = NULL, node *q = NULL) :data(d), cnt(1), left(p), right(q) {}
    }*root;

    void makeEmpty(node *&p)
    {
        if (p)
        {
            makeEmpty(p->left);
            makeEmpty(p->right);
            delete p;
            p = NULL;
        }
    }
    void insert(node *&t, int x)
    {
        if (t)
        {
            if (t->data > x)insert(t->left,x);
            else if (t->data < x) insert(t->right, x);
            else ++t->cnt;
        }
        else t = new node(x);
    }
    void del(node *&t, int x)
    {
        if (!t)return;
        if (x < t->data)del(t->left, x);
        else if (x > t->data)del(t->right, x);
        else if (t->cnt > 1)--t->cnt;
        else if (t->left&&t->right)
        {
            node *tmp = t->right;
            while (tmp->left)tmp = tmp->left;
            t->data = tmp->data;
            t->cnt = tmp->cnt;
            tmp->cnt = 1;
            del(t->right, tmp->data);
        }
        else
        {
            node *old = t;
            t = (t->left ? t->left : t->right);
            delete old;
        }
    }
    void delBetween(node *&t, int x, int y)
    {
        if (!t) return;
        if (x >= t->data)delBetween(t->right, x, y);
        else if (y <= t->data)delBetween(t->left, x, y);
        else
        {
            delBetween(t->left, x, y);
            delBetween(t->right, x, y);
            if (t->right)
            {
                node *tmp = t->right;
                while (tmp->left)tmp = tmp->left;
                t->data = tmp->data;
                t->cnt = tmp->cnt;
                tmp->cnt = 1;
                del(t->right, tmp->data);
            }
            else if(t->left)
            {
                node *tmp = t->left;
                while (tmp->right) tmp = tmp->right;
                t->data = tmp->data;
                t->cnt = tmp->cnt;
                tmp->cnt = 1;
                del(t->left, tmp->data);
            }
            else t = NULL;
        }
    }

    int find_ith(node *t, int& i)
    {
        if (!t)return INF;
        int search1 = find_ith(t->left, i);
        if (search1 != INF) return search1;
        else
        {
            if (i <= t->cnt)return t->data;
            else
            {
                i -= t->cnt;
                return find_ith(t->right, i);
            }
        }
    }
public:
    binarySearchTree(node *p = NULL) :root(p) {}
    ~binarySearchTree() { makeEmpty(root); }
    void insert(int x) { insert(root, x); }
    void del(int x) { del(root, x); }
    void delBetween(int x,int y) { delBetween(root, x, y); }
    bool find(int x)
    {
        if (!root) return false;
        node *tmp = root;
        while (tmp)
        {
            if (tmp->data > x)tmp = tmp->left;
            else if (tmp->data < x)tmp = tmp->right;
            else return true;
        }
        return false;
    }
    int find_ith(int i)
    {
        return find_ith(root, i);
    }
};
int main()
{
    binarySearchTree tree;
    int num_of_instructions;
    char instruction[25];
    int ope1, ope2;
    cin>>num_of_instructions;
    for(int i = 0; i < num_of_instructions; ++i){
        cin>>instruction;
        if(strcmp(instruction, "insert") == 0){
            cin>>ope1;
            tree.insert(ope1);
        }
        else if(strcmp(instruction, "delete") == 0){
            cin>>ope1;
            tree.del(ope1);
        }
        else if(strcmp(instruction, "delete_less_than") == 0){
            cin>>ope1;
            tree.delBetween(INF,ope1);
        }
        else if(strcmp(instruction, "delete_greater_than") == 0){
            cin>>ope1;
            tree.delBetween(ope1, 0x7fffffff);
        }
        else if(strcmp(instruction, "delete_interval") == 0){
            cin>>ope1>>ope2;
            tree.delBetween(ope1, ope2);
        }
        else if(strcmp(instruction, "find") == 0){
            cin>>ope1;
            if(tree.find(ope1)) cout<<"Y\n";
            else cout<<"N\n";
        }
        else if(strcmp(instruction, "find_ith") == 0){
            cin>>ope1;
            int cmp = tree.find_ith(ope1);
            if(cmp == INF) cout<<"N\n";
            else cout<<cmp<<endl;
        }
    }
}
*/
