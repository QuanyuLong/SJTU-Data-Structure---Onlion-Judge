#include <iostream>
#include "seqQueue.h"
using namespace std;

int main()
{
    seqQueue<int> queue1(5);
    queue1.enQueue(1);
    queue1.enQueue(2);
    queue1.enQueue(3);
    queue1.enQueue(4);
    cout<<queue1.deQueue()<<endl;
    queue1.enQueue(5);
    queue1.enQueue(6);
    queue1.enQueue(7);
    queue1.enQueue(8);
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.deQueue()<<endl;
    cout<<queue1.isEmpty()<<endl;
}
