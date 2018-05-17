#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <iostream>

using namespace std;

template <class elemType>
class AVLTree{
private:
    struct AVLNode{
        elemType data;
        AVLNode * left;
        AVLNode * right;
        int height;

        AVLNode(const elemType & x, AVLNode * l, AVLNode * r, int h = 0):data(x), left(l), right(r), height(h) {}
        AVLNode():left(NULL), right(NULL), height(0) {}
    };

    AVLNode * root;
    void insert(const elemmType & x, AVLNode * & t);
    void remove(const elemType & x, AVLNode * & t);
    void makeEmpty(AVLNode * & t);
    int height(AVLNode * t)const {return t == NULL ? -1 : t->height;}
    void LL(AVLNode * & t);
    void LR(AVLNode * & t);
    void RL(AVLNode * & t);
    void RR(AVLNode * & t);
    int max(int a, int b) {return (a>b) ? a:b ;}
public:
    AVLTree():root(NULL);
    ~AVLTree() {makeEmpty(root);}
    bool find(const elemType & x)const;
    void insert(const elemType & x) {insert(x, root);}
    void remove(const elemType & x) {remove(x, root);}
};

template <class elemType>
bool AVLTree<elemType>::find(const elemType & x)const
{
    AVLNode * t = root;
    bool result = false;
    while(t){
        if(t->data == x) {result = true; break}
        else if(t->data < x) t = t->right;
        else t = t->left;
    }
    return result;
}



#endif // AVLTREE_H_INCLUDED
