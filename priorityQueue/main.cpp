#include <iostream>
#include "priorityQueue.h"
using namespace std;

int main()
{
    int arr[11] = {40, 20, 60, 15, 30, 25, 10, 35, 45, 50, 55};
    priorityQueue<int> priQueue(arr, 11);
    priQueue.levelOrder();
    cout<<endl;
    priQueue.enQueue(1);
    priQueue.enQueue(9);
    cout<<priQueue.deQueue()<<endl;
    priQueue.levelOrder();
}
