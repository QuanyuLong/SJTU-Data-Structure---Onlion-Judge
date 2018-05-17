#include <iostream>
#include "seqStack.h"
using namespace std;

int main()
{
    seqStack<int> stack1(10);
    for(int i = 0; i < 10; ++i) stack1.push(i);
    while(!stack1.isEmpty())cout<<stack1.pop();
}
