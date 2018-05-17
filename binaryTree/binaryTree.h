#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <iostream>
#include "linkQueue.h"
#include "linkStack.h"

using namespace std;

template <class elemType>
class binaryTree{
private:
    struct node{
        elemType data;
        node * left,* right;
        node(const elemType & d, node * l = NULL, node * r = NULL):data(d),left(l),right(r) {}
        node():left(NULL),right(NULL) {}
        ~node() {}
    };
    node * root;
    void clear(node * t);
    int height(node * t) const;
    int size(node * t)const;
    void preOrder(node * t)const;
    void preOrder_nonrecursion_stack(node * t)const;
    void midOrder(node * t)const;
    void midOrder_nonrecursion_stack(node * t)const;
    void postOrder(node * t)const;
    void postOrder_nonrecursion_stack(node * t)const;
    void preOrder_Morris(node * t)const;
    void midOrder_Morris(node * t)const;
    void print_reverse(node * from, node * to) const;
    void postOrder_Morris(node * t)const;
    void levelOrder(node * t)const;

public:
    binaryTree() {root = NULL;}
    binaryTree(const elemType & x) {root = new node(x);}
    binaryTree(node * p):root(p) {}
    ~binaryTree() {clear();}
    void clear() {if(root!=NULL) {clear(root); root = NULL;}}
    int height()const {return height(root);}
    int size()const {return size(root);}
    void preOrder() const {preOrder(root);}
    void preOrder_nonrecursion_stack() const {preOrder_nonrecursion_stack(root);}
    void midOrder() const {midOrder(root);}
    void midOrder_nonrecursion_stack() const {midOrder_nonrecursion_stack(root);}
    void postOrder() const {postOrder(root);}
    void postOrder_nonrecursion_stack() const {postOrder_nonrecursion_stack(root);}
    void preOrder_Morris()const {preOrder_Morris(root);}
    void midOrder_Morris()const {midOrder_Morris(root);}
    void postOrder_Morris()const {postOrder_Morris(root);}
    void levelOrder() const {levelOrder(root);}
    void createTree(elemType flag);
    bool isEmpty() {return root==NULL;}
    elemType getRoot() {return root->data;}
    elemType getLeft() {return root->left->data;}
    elemType getRight() {return root->right->data;}
    void makeTree(const elemType & x, binaryTree & lt, binaryTree & rt);
    void delLeft();
    void delRight();
};

template <class elemType>
void binaryTree<elemType>::makeTree(const elemType & x, binaryTree & lt, binaryTree & rt)
{
    root = new node(x, lt.root, rt.root);
    lt.root = NULL;
    rt.root = NULL;
}

template <class elemType>
void binaryTree<elemType>::delLeft()
{
    binaryTree tmp = root->left;
    tmp.clear();
    root->left = NULL;
}

template <class elemType>
void binaryTree<elemType>::delRight()
{
    binaryTree tmp = root->right;
    tmp.clear();
    root->right = NULL;
}

template <class elemType>
int binaryTree<elemType>::size(node * t)const
{
    if (t==NULL) return 0;
    else return size(t->left)+size(t->right)+1;
}

template <class elemType>
int binaryTree<elemType>::height(node * t)const
{
    int lh, rh;
    if (t==NULL) return 0;
    else {lh = height(t->left); rh = height(t->right);}
    return 1 + ((lh>rh)?lh:rh);
}

template <class elemType>
void binaryTree<elemType>::preOrder(node * t)const
{
    cout<<t->data<<' ';
    if(t->left) preOrder(t->left);
    if(t->right) preOrder(t->right);
}

template <class elemType>
void binaryTree<elemType>::midOrder(node * t)const
{
    if(t->left) midOrder(t->left);
    cout<<t->data<<' ';
    if(t->right) midOrder(t->right);
}

template <class elemType>
void binaryTree<elemType>::postOrder(node * t)const
{
    if(t->left) postOrder(t->left);
    if(t->right) postOrder(t->right);
    cout<<t->data<<' ';
}

template <class elemType>
void binaryTree<elemType>::levelOrder(node * t)const
{
    linkQueue<node *> que;
    que.enQueue(t);
    node * tmp = que.deQueue();
    while(!que.isEmpty()){
        if(tmp){
            cout<<tmp->data<<' ';
            que.enQueue(tmp->left);
            que.enQueue(tmp->right);
        }
    }
}


template <class elemType>
void binaryTree<elemType>::clear(node * t)
{
    if(t->left) clear(t->left);
    if(t->right) clear(t->right);
    delete t;
}

template <class elemType>
void binaryTree<elemType>::createTree(elemType flag)
{
    linkQueue<node *> que;
    node *tmp;
    elemType x, ldata, rdata;
    //创建树，输入flag表示空
    cout << "\n输入根结点：";
    cin >> x;
    root = new node(x);
    que.enQueue(root);
    while (!que.isEmpty()) {
	    tmp = que.deQueue();
	    cout << "\n输入" << tmp->data<< "的两个儿子(" << flag << "表示空结点)：";
        cin >> ldata >> rdata;
	    if (ldata != flag)
            que.enQueue(tmp->left = new node(ldata));
	    if (rdata != flag)
            que.enQueue(tmp->right = new node(rdata));
	}
	cout << "create completed!\n";
}

template <class elemType>
void binaryTree<elemType>::preOrder_nonrecursion_stack(node * t)const
{
    linkStack<node *> sta;
    sta.push(t);
    while(!sta.isEmpty()){
        node * tmp = sta.pop();
        if(tmp) {
            cout<<tmp->data<<' ';
            if(tmp->right) sta.push(tmp->right);
            if(tmp->left) sta.push(tmp->left);
        }
    }
}

template <class elemType>
void binaryTree<elemType>::midOrder_nonrecursion_stack(node * t)const
{
    struct ctNode{
        node * no;
        int countTime;
        ctNode(node * n = NULL):no(n), countTime(0) {}
    };
    linkStack<ctNode> sta;
    ctNode current(t);
    if(t) {sta.push(current);}
    while(!sta.isEmpty()){
        current = sta.pop();
        if(++current.countTime == 2) {
            cout<<current.no->data<<' ';
            if(current.no->right) sta.push(ctNode(current.no->right));
        }
        else{
            sta.push(current);
            if(current.no->left) sta.push(ctNode(current.no->left));
        }
    }
}

template <class elemType>
void binaryTree<elemType>::postOrder_nonrecursion_stack(node * t)const
{
    struct ctNode{
        node * no;
        int countTime;
        ctNode(node * n = NULL):no(n), countTime(0) {}
    };
    linkStack<ctNode> sta;
    ctNode current(t);
    if(t) sta.push(current);
    while(!sta.isEmpty()){
        current = sta.pop();
        if(++current.countTime == 2) cout<<current.no->data<<' ';
        else{
            sta.push(current);
            if(current.no->right) sta.push(ctNode(current.no->right));
            if(current.no->left) sta.push(ctNode(current.no->left));
        }
    }
}

template <class elemType>
void binaryTree<elemType>::midOrder_Morris(node * t)const
{
    node * current_node = t, * prev_node = NULL;
    while(current_node){
        if(!current_node->left) {
            cout<<current_node->data<<' ';
            current_node = current_node->right;
        }
        else{
            prev_node = current_node->left;
            while(prev_node->right && prev_node->right != current_node) prev_node = prev_node->right;
            if (prev_node->right == NULL) {prev_node->right = current_node; current_node = current_node->left;}
            else {prev_node->right = NULL; cout<<current_node->data<<' '; current_node = current_node->right;}
        }
    }
}

template <class elemType>
void binaryTree<elemType>::preOrder_Morris(node * t)const
{
    node * current_node = t, * prev_node = NULL;
    while(current_node){
        if(!current_node->left) {cout<<current_node->data<<' ';current_node = current_node->right;}
        else{
            prev_node = current_node->left;
            while(prev_node->right && prev_node->right!=current_node) prev_node = prev_node->right;
            if(prev_node->right == NULL) {cout<<current_node->data<<' ';prev_node->right = current_node; current_node = current_node->left;}
            else {prev_node->right = NULL;  current_node = current_node->right;}
        }
    }
}

template <class elemType>
void binaryTree<elemType>::print_reverse(node * from, node * to)const
{
    linkStack<node *> sta;
    node * p = from;
    while(true){sta.push(p); if(p == to) break; p = p->right;}
    while(!sta.isEmpty()) cout<<sta.pop()->data<<' ';
}

template <class elemType>
void binaryTree<elemType>::postOrder_Morris(node * t)const
{
    node * tmp = new node(); tmp->left = t;
    node * current_node = tmp, * prev_node = NULL;
    while(current_node){
        if(!current_node->left) current_node = current_node->right;
        else{
            prev_node = current_node->left;
            while(prev_node->right && prev_node->right != current_node) prev_node = prev_node->right;
            if(prev_node->right == NULL) {prev_node->right = current_node; current_node = current_node->left;}
            else{
                prev_node->right = NULL;
                print_reverse(current_node->left, prev_node);
                current_node = current_node->right;
            }
        }
    }
}



#endif // BINARYTREE_H_INCLUDED
