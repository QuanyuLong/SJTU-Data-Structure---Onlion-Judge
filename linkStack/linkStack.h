#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED

#include "stack.h"
#include <iostream>

using namespace std;

template <class elemType>
class linkStack : public stack<elemType> {
private:
    struct node{
        elemType data;
        node * next;
        node() {next = NULL;}
        node(const elemType & obj, node * n = NULL) {data = obj; next = n;}
    };
    node * Top;
public:
    linkStack() {Top = NULL;}
    bool isEmpty() const;
    elemType pop();
    void push(const elemType & obj);
    elemType top() const;
    ~linkStack();
};

template <class elemType>
bool linkStack<elemType>::isEmpty()const
{
    return Top == NULL;
}

template <class elemType>
elemType linkStack<elemType>::top()const
{
    return Top->data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    node * tmp = Top;
    elemType x = Top->data;
    Top = Top->next;
    delete tmp;
    return x;
}

template <class elemType>
void linkStack<elemType>::push(const elemType & obj)
{
    node * tmp = new node(obj,Top);
    Top = tmp;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node * tmp = Top;
    while(tmp)
    {
        tmp = Top->next;
        delete Top;
        Top = tmp;
    }
}

#endif // LINKSTACK_H_INCLUDED
