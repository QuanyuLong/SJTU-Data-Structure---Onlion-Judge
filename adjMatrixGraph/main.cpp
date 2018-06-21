#include <iostream>
#include "adjMatrixGraph.h"
using namespace std;

int main()
{
    char v[4] = {'A','B','C','D'};
    int flag = -1;
    adjMatrixGraph<char, int> graph(4,v,flag);
    graph.insert(0,1,100);
    graph.insert(0,2,200);
    graph.insert(1,3,200);
    graph.insert(2,3,200);
    graph.insert(3,0,100);
    graph.insert(3,2,100);
    cout<<graph.numOfVers()<<' '<<graph.numOfEdges()<<endl;
    cout<<graph.exist(1,3)<<' '<<graph.exist(3,1)<<endl;
    graph.insert(3,1,1000);
    graph.remove(1,3);
    cout<<graph.exist(1,3)<<' '<<graph.exist(3,1)<<endl;
}
