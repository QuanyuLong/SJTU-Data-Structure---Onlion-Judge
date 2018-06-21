#include <iostream>
#include "adjListGraph.h"

using namespace std;

int main()
{
    char v[7] = {'0','1','2','3','4','5','6'};
    adjListGraph<char, int> graph(7, v);
    graph.insert(0,1,2);
    graph.insert(0,3,1);
    graph.insert(1,3,3);
    graph.insert(1,4,10);
    graph.insert(2,0,4);
    graph.insert(2,5,5);
    graph.insert(3,2,2);
    graph.insert(3,5,8);
    graph.insert(3,4,2);
    graph.insert(3,6,4);
    graph.insert(4,6,6);
    graph.insert(6,5,1);
    char start = '1';
    graph.dijkstra(start, 0x7fffffff);
}
