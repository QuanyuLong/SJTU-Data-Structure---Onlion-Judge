#ifndef DLINKLIST_H_INCLUDED
#define DLINKLIST_H_INCLUDED
#include <iostream>
#include "list.h"
using namespace std;

class outOfBound {};
class illigalSize {};

//head -> a0 -> a1 -> a2 -> ... -> an-1 -> tail

template <class elemType>
class DlinkList : public list<elemType>{
private:
    struct node{
        node(const elemType & x, node * p=NULL, node * n=NULL): data(x),prev(p),next(n) {}
        node(node * p = NULL, node * n = NULL):prev(p),next(n) {}
        ~node(){}
        elemType data;
        node * prev;
        node * next;
    };
    node * head;
    node * tail;
    int currentLength;

public:
    DlinkList();
    ~DlinkList() {clear();delete head; delete tail;}
    int length() const {return currentLength;}
    int search(const elemType & x) const;
    elemType visit(int i)const;
    void insert(int i, const elemType & x);
    void remove(int i);
    void clear();
    void traverse()const;
    void reverse();
};

template <class elemtype>
DlinkList<elemType>::DlinkList()
{
    head = new node();
    tail = new node();
    head->next = tail;
    tail->prev = head;
    currentLength = 0;
}

template <class elemType>
int DlinkList<elemType>::search(const elemType & x)const
{
/*
    int i = 0;
    node * p = head->next;
    while (p != tail){
        if (p->data == x) break;
        p = p->next; ++i;
    }
    if (p == tail) return -1;
    else return i;
*/
    int j;
    node * q = head->next;
    for (j=0; j<currentLength; ++j){
        if (q->data == x) break;
        q = q->next;
    }
    if (j == currentLength) return -1;
    else return j;
}

template <class elemType>
elemType DlinkList<elemType>::visit(int i)const
{
    if (i < 0 || i >= currentLength) throw outOfBound();
    node * p = head->next;
    for (int j = 0; j <= i; ++j)p = p->next;
    return p->data;
}

template <class elemType>
//because of the existence of the tail node, we can insert at index of n
void DlinkList<elemType>::insert(int i, const elemType & x)
{
    if ( i < 0 || i > currentLength) throw outOfBound();
    if (i == currentLength){
        node * tmp = new node(x,tail->prev,tail);
        tail->prev->next = tmp;
        tail->prev = tmp;
        return;
    }
    node * p = head;
    int j;
    for (j = 0;j < i;++j)p = p->next;
    node * tmp = new node(x, p, p->next);
    p->next->prev = tmp;
    p->next = tmp;
    currentLength ++;
}

template <class elemType>
void DlinkList<elemType>::remove(int i)
{
    if (i<0 || i>= currentLength) throw outOfBound();
    int j;
    node * p = head->next;
    for (j = 0;j < i; ++j) p = p->next;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    currentLength --;
}

template <class elemType>
coid DlinkList<elemType>::clear()
{
    node *
}


#endif // DLINKLIST_H_INCLUDED
