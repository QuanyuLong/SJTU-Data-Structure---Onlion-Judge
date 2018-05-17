#include <iostream>
#include "linkQueue.h"
using namespace std;

int main()
{
    linkQueue<int> queue1;
    queue1.enQueue(1);
    queue1.enQueue(2);
    queue1.enQueue(3);
    cout<<queue1.getHead()<<endl;
    queue1.deQueue();
    cout<<queue1.getHead()<<endl;
}
