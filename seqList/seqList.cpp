#include "seqList.h"
#include <iostream>
using namespace std;

template<class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType * tmp = new elemType [maxSize * 2];
    if (!tmp) throw illigalSize();
    for (int i = 0; i<currentLength; ++i) tmp[i] = data[i];
    delete [] data;
    data = tmp;
    maxSize = maxSize * 2;
}

template<class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType [initSize];
    if (!data) throw illigalSize(); //容易忘记开辟空间失败的情况
    currentLength = 0;
    maxSize = initSize;
}

template<class elemType>
seqList<elemType>::seqList(const seqList & obj)
{
    currentLength = obj.currentLength;
    maxSize = obj.maxSize;
    data = new elemType [maxSize];
    if (!data) throw illigalSize();
    for (int i = 0; i<currentLength; ++i) data[i] = obj.data[i];
}

template <class elemType>
int seqList<elemType>::length()const
{
    return currentLength;
}

template<class elemType>
int seqList<elemType>::search(const elemType & x)const
{
    int i;
    for (i = 0; i < currentLength; ++i) if (data[i]==x) break;
    if (i != currentLength) return i;
    return -1;
}

template<class elemType>
//在第i个元素的前面插入，i从0开始编号
void  seqList<elemType>::insert(int i, const elemType & x)
{
    if (currentLength == maxSize) doubleSpace();  //容易忘记是否还有空间
    if (i < 0 || i > currentLength - 1) throw outOfBound(); //溶剂忘记越界
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

template <class elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::traverse() const
{
    for(int i=0; i< currentLength; ++i) cout<<data[i]<<endl;
}
