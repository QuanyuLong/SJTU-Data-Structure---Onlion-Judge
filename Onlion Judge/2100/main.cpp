#include <iostream>
using namespace std;


template <class elemType>
class priorityQueue{
private:
    int currentSize;
    elemType * array;
    int maxSize;

    void doubleSpace();
    void buildHelp();
    void buildHelpRecursion(int hole);
    void percolateDown(int hole);
    void percolateUp(int leaf);

public:
    priorityQueue( int capacity = 100 )
    {
        array = new elemType[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const elemType data[], int size );
	~priorityQueue() { delete [] array; }
    bool isEmpty( ) const { return currentSize == 0; }
    void enQueue( const elemType & x );
    elemType deQueue();
    elemType getHead() {return array[1]; }
    void levelOrder() const;
};

template <class elemType>
void priorityQueue<elemType>::doubleSpace()
{
    elemType * tmp = new elemType [2 * maxSize];
    for (int i = 1; i <= currentSize; ++i) tmp[i] = array[i];
    delete array;
    array = tmp;
    maxSize = maxSize * 2;
}

template <class elemType>
void priorityQueue<elemType>::buildHelp()
{
    for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}

template <class elemType>
void priorityQueue<elemType>::buildHelpRecursion(int hole)
{
    if(hole * 2 <= currentSize) buildHelpRecursion(hole * 2);
    else return;
    if(hole * 2 + 1 <= currentSize) buildHelpRecursion(hole * 2 + 1);
    percolateDown(hole);
}

template <class elemType>
void priorityQueue<elemType>::percolateDown(int hole)
{
    if (hole * 2 > currentSize) return;
    int child;
    elemType tmp = array [hole];
    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && array[child] > array [child + 1]) child ++;
        if (array[child] < tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template <class elemType>
void priorityQueue<elemType>::percolateUp(int leaf)
{
    if (leaf <= 1) return;
    int parent;
    elemType tmp = array[leaf];
    for (; leaf > 1; leaf = parent)
    {
        parent = leaf/2;
        if (array[parent] > tmp) array[leaf] = array[parent];
        else break;
    }
    array[leaf] = tmp;
}

template <class elemType>
priorityQueue<elemType>::priorityQueue(const elemType data [], int size)
{
    maxSize = 2 * size; currentSize = size;
    array = new elemType [maxSize];
    for (int i = 1; i <= currentSize; ++i) array[i] = data[i-1];
    buildHelp();
    //buildHelpRecursion(1);
}

template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType & x)
{
    if(currentSize == maxSize-1) doubleSpace();
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole/2] ; hole /= 2) array[hole] = array[hole/2];
    array[hole] = x;
}

template <class elemType>
elemType priorityQueue<elemType>::deQueue()
{
    elemType result = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return result;
}

template <class elemType>
void priorityQueue<elemType>::levelOrder()const
{
    for (int i = 0; i < currentSize; ++i) cout<<array[i+1]<<' ';
}

int main(){
    int N,data,min1, min2, result = 0;
    priorityQueue<int> que;
    cin>>N;
    for (int i = 0; i < N; ++i) {
        cin>>data;
        que.enQueue(data);
    }
    //que.levelOrder();
    while (!que.isEmpty()){
        min1 = que.deQueue();
        if (!que.isEmpty()) {
            min2 = que.deQueue();
            result += (min1 + min2);
            que.enQueue(min1 + min2);
        }
    }
    cout << result;

}
