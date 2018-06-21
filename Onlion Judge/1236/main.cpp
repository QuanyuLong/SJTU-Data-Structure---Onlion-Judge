#include <iostream>

using namespace std;

template <class elemType>
class Queue{
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType & x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~Queue(){}
};

template <class elemType>
class linkQueue : public Queue<elemType> {
private:
    struct node{
        node(const elemType & x, node * n = NULL):data(x) , next(n) {}
        node():next(NULL) {}
        elemType data;
        node * next;
        ~node(){}
    };
    node * front, * rear;
public:
    linkQueue():front(NULL), rear(NULL) {}
    ~linkQueue();
    bool isEmpty() const {return (front == NULL) && (rear == NULL);}
    void enQueue(const elemType & x);
    elemType deQueue();
    elemType getHead() const {return front->data;}
};

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType & x)
{
    if ((front == NULL) && (rear == NULL)) {front = rear = new node(x); return;}
    rear->next = new node(x);
    rear = rear->next;
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    elemType tmp = front->data;
    if ((front == rear)&&(front != NULL)) {delete front;front = rear = NULL; return tmp;}
    node * t = front;
    front = front->next; delete t; return tmp;
}

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node * tmp = front;
    while (front){
        front = front->next;
        delete tmp;
        tmp = front;
    }
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
    void negWeightedShortDistance(int start, int e, typeOfEdge noEdge)const;
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
void adjListGraph<typeOfEdge>::negWeightedShortDistance(int start, int e, typeOfEdge noEdge)const
{
    typeOfEdge * distance = new typeOfEdge [this->Vers];
    int * prev = new int [this->Vers];
    linkQueue<int> que;
    edgeNode * p;

    for(int i = 0; i < this->Vers; ++i) distance[i] = noEdge;
    distance[start] = 0;

    que.enQueue(start);
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
    cout<<distance[e]<<endl;
    //printPath(start, e, prev);

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
    graph.negWeightedShortDistance(start-1, end-1, noEdge);
}
