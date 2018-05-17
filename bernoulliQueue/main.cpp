#include <iostream>
#include "bernoulliQueue.h"

using namespace std;

int main()
{
    bernoulliQueue<int> priQueue(20);
    priQueue.enQueue(4);
    priQueue.enQueue(2);
    priQueue.enQueue(3);
    priQueue.enQueue(1);
    cout<<priQueue.dequeue();
    cout<<priQueue.dequeue();
}
