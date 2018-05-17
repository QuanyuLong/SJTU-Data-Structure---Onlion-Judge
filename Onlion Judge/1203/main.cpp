#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

template <class elemType>
class list{
private:

public:
    virtual int length() const = 0;
    virtual int search(const elemType &x)const = 0;
    virtual elemType visit(int i)const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse()const = 0;
    virtual ~list() {}
};
class outOfBound{};
class illigalSize{};

template <class elemType>
class seqList : public list<elemType>{
    friend seqList<elemType> operator+ (const seqList<elemType> & list1, const seqList<elemType> & list2)
    {
        seqList<elemType> result_list(list1.currentLength+list2.currentLength);
        result_list.currentLength = list1.currentLength+list2.currentLength;
        for(int i = 0; i<list1.currentLength;++i) result_list.data[i] = list1.data[i];
        for(int i = list1.currentLength;i<list1.currentLength+list2.currentLength;++i) result_list.data[i] = list2.data[i-list1.currentLength];
        return result_list;
    }
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
    seqList & operator=(const seqList & obj);
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

template <class elemType>
seqList<elemType> & seqList<elemType>::operator=(const seqList<elemType> & obj)
{
    if (this == & obj) return * this;
    delete [] data;
    maxSize = obj.maxSize;
    currentLength = obj.currentLength;
    data = new elemType [maxSize];
    for (int i = 0; i < currentLength; ++i) data[i] = obj.data[i];
    return * this;
}

int main()
{
    char type [10];
    int len1, len2;
    cin >> type >> len1 >> len2;
    if (strcmp(type,"int")==0)
    {
        seqList<int> list1(len1); seqList<int> list2(len2); int data;
        int i=0;
        while(i<len1){cin>>data; list1.insert(i,data);++i;}
        i = 0;
        while(i<len2) {cin>>data; list2.insert(i,data);++i;}
        seqList <int> list3(len1+len2);
        list3 = list1+list2;
        for (i = 0;i<list3.length();++i) cout<<list3.visit(i)<<' ';
    }
    if (strcmp(type,"char")==0)
    {
        seqList<char> list1(len1); seqList<char> list2(len2); char data;
        int i=0;
        while(i<len1){cin>>data; list1.insert(i,data);++i;}
        i = 0;
        while(i<len2) {cin>>data; list2.insert(i,data);++i;}
        seqList <char> list3(len1+len2);
        list3 = list1+list2;
        for (i = 0;i<list3.length();++i) cout<<list3.visit(i)<<' ';

    }
    if (strcmp(type,"double")==0)
    {
        seqList<double> list1(len1); seqList<double> list2(len2); double data;
        int i=0;
        while(i<len1){cin>>data; list1.insert(i,data);++i;}
        i = 0;
        while(i<len2) {cin>>data; list2.insert(i,data);++i;}
        seqList <double> list3(len1+len2);
        list3 = list1+list2;
        for (i = 0;i<list3.length();++i) cout<<list3.visit(i)<<' ';
    }
}
