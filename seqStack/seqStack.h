#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED
#include <iostream>
#include"stack.h"

using namespace std;

template <class elemType>
class seqStack : public stack<elemType>{
private:
    int top_index;
    int maxSize;
    elemType * elem;
    void doubleSpace();
public:
    seqStack(int initialSize);
    bool isEmpty() const;
    elemType pop();
    void push(const elemType & obj);
    elemType top() const;
    ~seqStack() {delete [] elem;}
};

template <class elemType>
seqStack<elemType>::seqStack(int initialSize)
{
    elem = new elemType [initialSize];
    maxSize = initialSize;
    top_index = -1;
}

template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return top_index == -1;
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    return elem[top_index--];
}

template <class elemType>
void seqStack<elemType>::push(const elemType & obj)
{
    if (top_index == maxSize - 1) doubleSpace();
    elem[++top_index] = obj;
}

template <class elemType>
elemType seqStack<elemType>::top()const
{
    return elem[top_index];
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType * tmp = new elemType (maxSize*2);
    for (int i = 0; i<=top_index; ++i) tmp[i]=elem[i];
    maxSize *= 2;
    delete [] elem;
    elem = tmp;
}

#endif // SEQSTACK_H_INCLUDED
