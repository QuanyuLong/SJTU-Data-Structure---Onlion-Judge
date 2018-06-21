#ifndef ADJMATRIXGRAPH_H_INCLUDED
#define ADJMATRIXGRAPH_H_INCLUDED

#include "graph.h"
#include <iostream>

using namespace std;


template <class typeOfVer, class typeOfEdge>
class adjMatrixGraph : public graph<typeOfEdge>{
private:
    typeOfEdge ** edge;
    typeOfVer * ver;
    typeOfEdge noEdge;
public:
    adjMatrixGraph(int verSize, const typeOfVer v[], typeOfEdge noEdgeFlag);
    ~adjMatrixGraph();
    bool insert(int u, int v, typeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v)const;
};

template <class typeOfVer, class typeOfEdge>
adjMatrixGraph<typeOfVer, typeOfEdge>::adjMatrixGraph(int verSize, const typeOfVer v[], typeOfEdge noEdgeFlag)
{
    noEdge = noEdgeFlag;
    this->Vers = verSize;
    this->Edges = 0;
    ver = new typeOfVer [verSize];
    for(int i = 0; i < verSize; ++i) ver[i] = v[i];
    edge = new typeOfEdge* [verSize];
    for(int i = 0; i < verSize; ++i){
        edge[i] = new typeOfEdge [verSize];
        for(int j = 0; j < verSize; ++j) edge[i][j] = noEdge;
        //edge[i][i] = 0;
    }
}

template <class typeOfVer, class typeOfEdge>
adjMatrixGraph<typeOfVer, typeOfEdge>::~adjMatrixGraph()
{
    delete [] ver;
    for(int i = 0; i < this->Vers; ++i) delete [] edge[i];
    delete [] edge;
}

template <class typeOfVer, class typeOfEdge>
bool adjMatrixGraph<typeOfVer, typeOfEdge>::insert(int u, int v, typeOfEdge w)
{
    if(u < 0 || u >= this->Vers || v < 0|| v >= this->Vers) return false;
    if(edge[u][v] != noEdge) return false;
    edge[u][v] = w;
    ++this->Edges;
    return true;
}

template <class typeOfVer, class typeOfEdge>
bool adjMatrixGraph<typeOfVer, typeOfEdge>::remove(int u, int v)
{
    if(u < 0 || u >= this->Vers || v < 0 || v>= this->Vers) return false;
    if(edge[u][v] == noEdge) return false;
    edge[u][v] = noEdge;
    --this->Edges;
    return true;
}

template <class typeOfVer, class typeOfEdge>
bool adjMatrixGraph<typeOfVer, typeOfEdge>::exist(int u, int v)const
{
    if(u < 0 || u >= this->Vers || v < 0 || v >= this->Vers) return false;
    if(edge[u][v] != noEdge) return true;
    else return false;
}


#endif // ADJMATRIXGRAPH_H_INCLUDED
