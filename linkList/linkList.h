#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
#include "list.h"
#include <iostream>
using namespace std;

class illigalSize{};
class outOfBound{};

//head -> a0 -> a1 -> a2 -> ... -> an -> NULL

template <class elemType>
class linkList : public list<elemType>{ //attention!!
private:
    struct node{
        elemType data;
        node * next;
        //attention! const and &
        node(const elemType &d, node * p = NULL){data = d; next = p;}
        node() {next = NULL;}
        //attention
        ~node(){}
    };
    node * head;
public:
    linkList(){head = new node();}
    int length() const;
    int search(const elemType & x)const;
    elemType visit(int i) const;
    void insert(int i, const elemType & x);
    void remove(int i);
    void clear();
    void traverse() const;
    ~linkList();
    void reverse();
};

template <class elemType>
int linkList<elemType>::length() const
{
    node * p = head->next;
    int result = 0;
    while (p) {p = p->next; ++result;}
    return result;
}

template <class elemType>
int linkList<elemType>::search(const elemType & x) const
{
    int i = 0;
    node * p = head->next;
    while (p) {
        if (p->data == x) break;
        ++i;
        p = p->next;
    }
    if (p) return i;
    return -1;
}

template <class elemType>
elemType linkList<elemType>::visit(int i)const
{
    if (i < 0) throw outOfBound();
    node * p = head->next;
    while (p && i) {
        p = p->next;
        --i;
    }
    if (!p) throw outOfBound();
    return p->data;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType & x)
{
    if (i < 0) throw outOfBound();
    node * tmp = new node(x);
    node * p = head;
    while(p && i){
        p = p->next;
        --i;
    }
    if (!p) throw outOfBound();
    tmp->next = p->next; p->next = tmp;
}

template <class elemType>
void linkList<elemType>::remove(int i)
{
    if (i < 0)throw outOfBound();
    node * p, *q;
    p = head; q = p->next;
    while (q && i){
        p = q; q = p->next; --i;
    }
    if (! q) throw outOfBound();
    p->next = q->next;
    delete q;
}

template <class elemType>
void linkList<elemType>::clear()
{
    node * p, *q;
    p = head; q = p->next;
    while (q){
        p = q->next;
        delete q;
        q = p;
    }
}

template <class elemType>
void linkList<elemType>::traverse()const
{
    node * p = head->next;
    while (p){
        cout<<p->data<<endl;
        p = p->next;
    }
}

template<class elemType>
linkList<elemType>::~linkList()
{
    clear();
    delete head;
}

template <class elemType>
void linkList<elemType>::reverse()
{
    node * tmp, * p, *q;
    tmp = new node();
    p = head; q = p->next;
    while(q){
        p = q->next;
        q->next = tmp->next;
        tmp->next = q;
        q = p;
    }
    delete head;
    head = tmp;
}

#endif // LINKLIST_H_INCLUDED
