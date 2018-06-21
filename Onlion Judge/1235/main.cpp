#include <iostream>

using namespace std;

template <class elemType>
class priorityQueue{
private:
    int currentSize;
    elemType * array;
    int maxSize;

    void doubleSpace();
    void buildHelp();
    void buildHelpRecursion(int hole);
    void percolateDown(int hole);

public:
    priorityQueue( int capacity = 100 )
    {
        array = new elemType[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const elemType data[], int size );
	~priorityQueue() { delete [] array; }
    bool isEmpty( ) const { return currentSize == 0; }
    void enQueue( const elemType & x );
    elemType deQueue();
    elemType getHead() {return array[1]; }
    void levelOrder() const;
};

template <class elemType>
void priorityQueue<elemType>::doubleSpace()
{
    elemType * tmp = new elemType [2 * maxSize];
    for (int i = 1; i <= currentSize; ++i) tmp[i] = array[i];
    delete array;
    array = tmp;
    maxSize = maxSize * 2;
}

template <class elemType>
void priorityQueue<elemType>::buildHelp()
{
    for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}

template <class elemType>
void priorityQueue<elemType>::buildHelpRecursion(int hole)
{
    if(hole * 2 <= currentSize) buildHelpRecursion(hole * 2);
    else return;
    if(hole * 2 + 1 <= currentSize) buildHelpRecursion(hole * 2 + 1);
    percolateDown(hole);
}

template <class elemType>
void priorityQueue<elemType>::percolateDown(int hole)
{
    if (hole * 2 > currentSize) return;
    int child;
    elemType tmp = array [hole];
    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && array[child] > array [child + 1]) child ++;
        if (array[child] < tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template <class elemType>
priorityQueue<elemType>::priorityQueue(const elemType data [], int size)
{
    maxSize = 2 * size; currentSize = size;
    array = new elemType [maxSize];
    for (int i = 1; i <= currentSize; ++i) array[i] = data[i-1];
    buildHelp();
    //buildHelpRecursion(1);
}

template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType & x)
{
    if(currentSize == maxSize-1) doubleSpace();
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole/2] ; hole /= 2) array[hole] = array[hole/2];
    array[hole] = x;
}

template <class elemType>
elemType priorityQueue<elemType>::deQueue()
{
    elemType result = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return result;
}

template <class typeOfEdge>
class graph{
public:
    virtual bool insert(int u, int v, typeOfEdge w) = 0;
    virtual bool remove(int u, int v) = 0;
    virtual bool exist(int u, int v) const = 0;
    virtual int numOfVers() const {return Vers;}
    virtual int numOfEdges() const {return Edges;}

protected:
    int Vers, Edges;
};

template<class typeOfEdge>
class adjListGraph : public graph<typeOfEdge>{
public:
    adjListGraph(int verSize);
    ~adjListGraph();
    bool insert(int u, int v, typeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void dijkstra(int start, int e, typeOfEdge noEdge) const;
private:
    struct edgeNode{
        int end;
        typeOfEdge weight;
        edgeNode * next;
        edgeNode(int e, typeOfEdge w, edgeNode * n = NULL): end(e), weight(w), next(n) {}
    };
    struct verNode{
        edgeNode * head;
        verNode(edgeNode * n = NULL): head(n){}
    };
    struct queNode{
        int nodeNum;
        typeOfEdge dist;

        bool operator< (const queNode & rt)const {return dist < rt.dist;}
        bool operator> (const queNode & rt)const {return dist > rt.dist;}
    };
    verNode * verList;
    void printPath(int s, int e, int * prev) const;
};

template <class typeOfEdge>
adjListGraph<typeOfEdge>::adjListGraph(int verSize)
{
    this->Vers = verSize;
    this->Edges = 0;
    verList = new verNode [verSize];
}

template <class typeOfEdge>
adjListGraph<typeOfEdge>::~adjListGraph()
{
    edgeNode * tmp;
    for(int i = 0; i < this->Vers; ++i)
        while((tmp = verList[i].head) != NULL){
            verList[i].head = tmp->next;
            delete tmp;
        }
    delete [] verList;
}

template <class typeOfEdge>
bool adjListGraph<typeOfEdge>::insert(int u, int v, typeOfEdge w)
{
    if(u < 0 || u >= this->Vers || v < 0 || v >= this->Vers) return false;
    verList[u].head = new edgeNode (v, w, verList[u].head);
    ++this->Edges;
    return true;
}

template <class typeOfEdge>
bool adjListGraph<typeOfEdge>::remove(int u, int v)
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

template <class typeOfEdge>
bool adjListGraph<typeOfEdge>::exist(int u, int v) const
{
    if(u < 0 || v >= this->Vers || v < 0 || v >= this->Vers) return false;
    edgeNode * tmp = verList[u].head;
    while(tmp && tmp->end != v) tmp = tmp->next;
    if(tmp) return true;
    else return false;
}

template <class typeOfEdge>
void adjListGraph<typeOfEdge>::printPath(int s, int e, int * prev)const
{
    if(s == e) {cout<<s+1; return;}
    printPath(s, prev[e], prev);
    cout<<" "<<e+1;
}

template <class typeOfEdge>
void adjListGraph<typeOfEdge>::dijkstra(int start, int e, typeOfEdge noEdge) const
{
    typeOfEdge *distance = new typeOfEdge[this->Vers];
    int *prev = new int [this->Vers];
    int *pathNodeNum = new int [this->Vers] {0};
    bool *known = new bool[this->Vers];
    for(int i = 0; i < this->Vers; ++i) {distance[i] = noEdge; known[i] = false;}
    edgeNode *p;
    priorityQueue<queNode> priQue;
    distance[start] = 0;
    queNode minDistNode, tmp;
    minDistNode.dist = 0;
    minDistNode.nodeNum = start;
    priQue.enQueue(minDistNode);

    while(!priQue.isEmpty()){
        minDistNode = priQue.deQueue();
        //cout<<minDistNode.nodeNum<<endl;
        if(known[minDistNode.nodeNum]) continue;
        known[minDistNode.nodeNum] = true;
        p = verList[minDistNode.nodeNum].head;
        //cout<<p->end<<' '<<p->weight<<endl;
        //cout<<distance[minDistNode.nodeNum]<<' '<<distance[p->end]<<endl;
        while(p){
            if((!known[p->end] && distance[minDistNode.nodeNum] + p->weight < distance[p->end]) ||
               (distance[minDistNode.nodeNum] + p->weight == distance[p->end] && pathNodeNum[p->end] > pathNodeNum[minDistNode.nodeNum] + 1))
            {
                tmp.dist = distance[p->end] = distance[minDistNode.nodeNum] + p->weight;
                prev[p->end] = minDistNode.nodeNum;
                pathNodeNum[p->end] = pathNodeNum[minDistNode.nodeNum] + 1;
                tmp.nodeNum = p->end;
                priQue.enQueue(tmp);
            }
            p = p->next;
        }
    }

    cout<<distance[e]<<endl;
    printPath(start, e, prev);
}

int main()
{
    int n, m, start, end, u, v, weight;
    cin>>n>>m>>start>>end;
    adjListGraph<int> graph(n);
    for(int i = 0; i < m; ++i){
        cin>>u>>v>>weight;
        graph.insert(u-1, v-1, weight);
    }
    int noEdge = 0x7fffffff;
    graph.dijkstra(start-1, end-1, noEdge);
}
