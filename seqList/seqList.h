#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED
#include "list.h"
#include <iostream>
using namespace std;
class outOfBound{};
class illigalSize{};

template <class elemType>
class seqList : public list<elemType>{
private:
    int currentLength;
    int maxSize;
    elemType * data;
    void doubleSpace()
{
    elemType * tmp = new elemType [maxSize * 2];
    if (!tmp) throw illigalSize();
    for (int i = 0; i<currentLength; ++i) tmp[i] = data[i];
    delete [] data;
    data = tmp;
    maxSize = maxSize * 2;
}
public:
    seqList(int initSize);
    seqList(const seqList & obj);
    int length() const;
    int search(const elemType & x)const;
    elemType visit(int i)const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear()
    {
        currentLength = 0;
    }
    void traverse()const
    {
        for(int i=0; i< currentLength; ++i) cout<<data[i]<<endl;
    }
    ~seqList()
    {
        delete [] data;
    }
};

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType [initSize];
    if (!data) throw illigalSize(); //容易忘记开辟空间失败的情况
    currentLength = 0;
    maxSize = initSize;
}

template <class elemType>
seqList<elemType>::seqList(const seqList & obj)
{
    currentLength = obj.currentLength;
    maxSize = obj.maxSize;
    data = new elemType [maxSize];
    if (!data) throw illigalSize();
    for (int i = 0; i<currentLength; ++i) data[i] = obj.data[i];
}

template <class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

template <class elemType>
int seqList<elemType>::search(const elemType & x)const
{
    int i;
    for (i = 0; i < currentLength; ++i) if (data[i]==x) break;
    if (i != currentLength) return i;
    return -1;
}

template <class elemType>
elemType seqList<elemType>::visit(int i)const
{
    return data[i];
}

template <class elemType>
void seqList<elemType>::insert(int i,const elemType & x)
{
    if (currentLength == maxSize) doubleSpace();  //容易忘记是否还有空间
    if (i < 0 || i > currentLength) throw outOfBound(); //溶剂忘记越界
    for (int j = currentLength; j > i; --j) data[j] = data[j-1];
    data[i] = x;
    currentLength ++; //容易忘记
}

template <class elemType>
void seqList<elemType>::remove(int i)
{
    if (i < 0 || i > currentLength-1) throw outOfBound();
    for (int j = i; j < currentLength; ++j) data[j] = data[j + 1];
    currentLength --;
}

#endif // SEQLIST_H_INCLUDED
