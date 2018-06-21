#ifndef ADJLISTGRAPH_H_INCLUDED
#define ADJLISTGRAPH_H_INCLUDED

#include "graph.h"
#include "linkQueue.h"
#include <iostream>

using namespace std;

template<class typeOfVer, class typeOfEdge>
class adjListGraph : public graph<typeOfEdge>{
public:
    adjListGraph(int verSize, const typeOfVer v[]);
    ~adjListGraph();
    bool insert(int u, int v, typeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void dfs() const;
    void bfs() const;
    void unweightedShortDistance(typeOfVer start) const; //非加权的最短路径
    void dijkstra(typeOfVer start, typeOfEdge noEdge) const;
    void negWeightedShortDistance(typeOfVer start, typeOfEdge noEdge) const;
private:
    struct edgeNode{
        int end;
        typeOfEdge weight;
        edgeNode * next;
        edgeNode(int e, typeOfEdge w, edgeNode * n = NULL): end(e), weight(w), next(n) {}
    };
    struct verNode{
        typeOfVer verName;
        edgeNode * head;
        verNode(edgeNode * n = NULL): head(n){}
    };
    verNode * verList;
    void dfs(int v, bool * visited) const;
    void printPath(int s, int e, int * prev) const;
};

template <class typeOfVer, class typeOfEdge>
adjListGraph<typeOfVer, typeOfEdge>::adjListGraph(int verSize, const typeOfVer v [])
{
    this->Vers = verSize;
    this->Edges = 0;
    verList = new verNode [verSize];
    for(int i = 0; i < verSize; ++i) verList[i].verName = v[i];
}

template <class typeOfVer, class typeOfEdge>
adjListGraph<typeOfVer, typeOfEdge>::~adjListGraph()
{
    edgeNode * tmp;
    for(int i = 0; i < this->Vers; ++i)
        while((tmp = verList[i].head) != NULL){
            verList[i].head = tmp->next;
            delete tmp;
        }
    delete [] verList;
}

template <class typeOfVer, class typeOfEdge>
bool adjListGraph<typeOfVer, typeOfEdge>::insert(int u, int v, typeOfEdge w)
{
    if(u < 0 || u >= this->Vers || v < 0 || v >= this->Vers) return false;
    verList[u].head = new edgeNode (v, w, verList[u].head);
    ++this->Edges;
    return true;
}

template <class typeOfVer, class typeOfEdge>
bool adjListGraph<typeOfVer, typeOfEdge>::remove(int u, int v)
{
    if(u < 0 || u >= this->Vers || v < 0 || v >= this->Vers) return false;
    edgeNode * p = verList[u].head, * q;
    if(p == NULL) return false;
    if(p->end == v) {verList[u].head = p->next; delete p; --this->Edges; return true;}
    while(p->next && p->next->end != v) p = p->next;
    if(p->next){
        q = p; p = q->next;
        q->next = p->next; delete p; --this->Edges; return true;
    }
    return false;
}

template <class typeOfVer, class typeOfEdge>
bool adjListGraph<typeOfVer, typeOfEdge>::exist(int u, int v) const
{
    if(u < 0 || v >= this->Vers || v < 0 || v >= this->Vers) return false;
    edgeNode * tmp = verList[u].head;
    while(tmp && tmp->end != v) tmp = tmp->next;
    if(tmp) return true;
    else return false;
}

template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::dfs() const
{
    bool * visited = new bool [this->Vers + 1] {false};
    for(int i = 0; i < this->Vers; ++i){
        if(visited[i] == true) continue;
        dfs(i, visited);
        cout<<endl;
    }

}

template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::dfs(int v, bool * visited) const
{
    visited[v] = true;
    edgeNode * tmp = verList[v].head;
    cout<<verList[v].verName<<'\t';
    while(tmp){
        if(visited[tmp->end] == false) dfs(tmp->end, visited);
        else tmp = tmp->next;
    }
}
template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::bfs()const
{
    linkQueue<int> que;
    bool * visited = new bool [this->Vers] {false};
    for(int i = 0; i < this->Vers; ++i){
        if(visited[i] == true) continue;
        que.enQueue(i);
        while(!que.isEmpty()){
            int t = que.deQueue();
            if(visited[t] == true) continue;
            visited[t] = true;
            cout<<verList[t].verName<<'\t';
            edgeNode * tmp = verList[t].head;
            while(tmp){
                if(visited[tmp->end] == false) que.enQueue(tmp->end);
                tmp = tmp->next;
            }
        }
    cout<<endl;
    }
}

template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::printPath(int s, int e, int * prev)const
{
    if(s == e) {cout<<verList[s].verName; return;}
    printPath(s, prev[e], prev);
    cout<<"->"<<verList[e].verName;
}

template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::unweightedShortDistance(typeOfVer start) const
{
    linkQueue<int> que;
    int * distance = new int[this->Vers];
    int maxNum = 0x7fffffff;
    for(int i = 0; i < this->Vers; ++i) distance[i] = maxNum;
    int *prev = new int [this->Vers];
    int tmp, startNumber;

    for(startNumber = 0; startNumber < this->Vers; ++startNumber) if(verList[startNumber].verName == start) break;
    if(startNumber == this->Vers) {cout<<"Invalid start"<<endl; return;}
    distance[startNumber] = 0;

    edgeNode * p;
    que.enQueue(startNumber);
    while(!que.isEmpty()){
        tmp = que.deQueue();
        p = verList[tmp].head;
        while(p) {
            if(distance[p->end] == maxNum) {
                distance[p->end] = distance[tmp] + 1;
                prev[p->end] = tmp;
                que.enQueue(p->end);
            }
            p = p->next;
        }
    }

    for(int i = 0; i < this->Vers; ++i) {
        cout<<"from "<<start<<" to "<<verList[i].verName<<", the shortest path is: ";
        printPath(startNumber, i, prev);
        cout<<", the distance is: "<<distance[i]<<endl;
    }
}

template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::dijkstra(typeOfVer start, typeOfEdge noEdge) const
{
    typeOfEdge *distance = new typeOfEdge[this->Vers];
    int *prev = new int [this->Vers];
    bool *known = new bool[this->Vers] {false};
    int tmp, startNum;
    edgeNode *p;

    for(int i = 0; i < this->Vers; ++i) distance[i] = noEdge;
    for(startNum = 0; startNum < this->Vers; ++startNum) if(verList[startNum].verName == start) break;
    if(startNum == this->Vers) {cout<<"Invalid start!"<<endl; return;}
    distance[startNum] = 0;

    for(int i = 1; i < this->Vers; ++i){
        typeOfEdge minNum = noEdge;
        for(int j = 0; j < this->Vers; ++j){
            if(!known[j] && distance[j] < minNum) {minNum = distance[j]; tmp = j;}
        }
        known[tmp] = true;
        p = verList[tmp].head;
        while(p){
            if(!known[p->end] && distance[tmp] + p->weight < distance[p->end]){
                distance[p->end] = distance[tmp] + p->weight;
                prev[p->end] = tmp;
            }
            p = p->next;
        }
    }

    for(int i = 0; i < this->Vers; ++i){
        cout<<"from "<<start<<" to "<<verList[i].verName<<", the shortest path is: ";
        printPath(startNum, i, prev);
        cout<<", the distance is: "<<distance[i]<<endl;
    }
}


template <class typeOfVer, class typeOfEdge>
void adjListGraph<typeOfVer, typeOfEdge>::negWeightedShortDistance(typeOfVer start, typeOfEdge noEdge)const
{
    typeOfEdge * distance = new typeOfEdge [this->Vers];
    int * prev = new int [this->Vers];
    linkQueue<int> que;
    edgeNode * p;
    int startNum;

    for(int i = 0; i < this->Vers; ++i) distance[i] = noEdge;
    for(startNum = 0; startNum < this->Vers; ++startNum) if(verList[startNum].verName == start) break;
    if(startNum == this->Vers) {cout<<"Invalid start!"<<endl; return;}
    distance[startNum] = 0;

    que.enQueue(startNum);
    while(!que.isEmpty()){
        int tmp = que.deQueue();
        p = verList[tmp].head;
        while(p){
            if(distance[tmp] + p->weight < distance[p->end]){
                distance[p->end] = distance[tmp] + p->weight;
                prev[p->end] = tmp;
                que.enQueue(p->end);
            }
            p = p->next;
        }
    }

    for(int i = 0; i < this->Vers; ++i){
        cout<<"from "<<start<<" to "<<verList[i].verName<<", the shortest path is: ";
        printPath(startNum, i, prev);
        cout<<", the distance is: "<<distance[i]<<endl;
    }
}

#endif // ADJLISTGRAPH_H_INCLUDED
