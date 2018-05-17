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
    if (!data) throw illigalSize(); //�������ǿ��ٿռ�ʧ�ܵ����
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
//�ڵ�i��Ԫ�ص�ǰ����룬i��0��ʼ���
void  seqList<elemType>::insert(int i, const elemType & x)
{
    if (currentLength == maxSize) doubleSpace();  //���������Ƿ��пռ�
    if (i < 0 || i > currentLength - 1) throw outOfBound(); //�ܼ�����Խ��
    for (int j = currentLength; j > i; --j) data[j] = data[j-1];
    data[i] = x;
    currentLength ++; //��������
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
