#include <iostream>
#include "linkList.h"
using namespace std;

int main()
{
    linkList<int> list1;
    for (int i = 0; i < 10; ++i) list1.insert(i , i);
    list1.remove(9);
    list1.insert(9,100);
    list1.reverse();
    list1.traverse();
}
