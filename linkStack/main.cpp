#include <iostream>
#include "linkStack.h"
using namespace std;

int main()
{
    linkStack<int> stack1;
    for(int i = 0; i< 10; ++i) stack1.push(i);
    cout<<stack1.top()<<endl;
    while(!stack1.isEmpty()) cout<<stack1.pop();
}
