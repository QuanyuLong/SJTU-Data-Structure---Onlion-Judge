#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

#include <iostream>
#include "Queue.h"

using namespace std;

template <class elemType>
class seqQueue : public Queue<elemType>{
private:
    elemType * elem;
    int front, rear, maxSize;
    void doubleSpace();
public:
    seqQueue(int initialSize = 10){
        elem = new elemType [initialSize];
        front = 0; rear = 0;
        maxSize = initialSize;
    }
    bool isEmpty() const;
    void enQueue(const elemType & x);
    elemType deQueue();
    elemType getHead() const;
    ~seqQueue();
};

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType & x)
{
    if ((rear+1)%maxSize == front) doubleSpace();
    rear = (rear+1)%maxSize;
    elem[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front+1)%maxSize;
    return elem[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front+1) % maxSize];
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return (front == rear);
}

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType * tmp = new elemType [maxSize*2];
    for (int i = 1; i < maxSize; ++i) tmp[i] = elem[(front+i)%maxSize]; //attention i counts from 1
    front = 0; rear = maxSize - 1;
    maxSize *= 2;
    delete [] elem;
    elem = tmp;
}

template <class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete [] elem;
}

#endif // SEQQUEUE_H_INCLUDED
