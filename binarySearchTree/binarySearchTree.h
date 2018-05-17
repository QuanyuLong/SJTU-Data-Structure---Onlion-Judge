#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <iostream>

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
    bool find(const elemType & x, node * root) const;
    void makeEmpty(node * & root);
public:
    binarySearchTree() {root = NULL;}
    ~binarySearchTree() {makeEmpty(root);}
    void insert(const elemType & x) {insert(x, root);}
    void remove(const elemType & x) {remove(x, root);}
    bool find(const elemType & x) const {return find(x, root);}

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
void binarySearchTree<elemType>::makeEmpty(node * & root)
{
    if(root->left) makeEmpty(root->left);
    if(root->right) makeEmpty(root->right);
    delete root;
}


#endif // BINARYSEARCHTREE_H_INCLUDED
