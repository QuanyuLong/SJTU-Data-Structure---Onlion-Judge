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


struct node
{
    int lchild, brother, father,v;
    node() :lchild(0), brother(0), father(0),v(0) {}
};

class staticBTree
{
private:
    node *data;
    int size;
    int root;
public:
    staticBTree() :data(NULL), size(0),root(0) {}
    ~staticBTree()
    {
        if (data != NULL) delete[]data;
    }
    void getRoot()
    {
        int i = 1;
        while (data[i].father != 0)
            i = data[i].father;
        root = i;
    }
    void createTree(int N)
    {
        size = N;
        data = new node[N + 1];
        int p, q, v;
        for (int i = 1;i <= N;++i)
        {
            cin >> p >> q >> v;
            data[i].lchild = p;
            data[i].brother = q;
            data[i].v = v;
            data[p].father = data[q].father = i;
        }
        getRoot();
    }

    void levelOrder(int t)const
    {
        linkQueue<int> que;
        que.enQueue(t);
        while(!que.isEmpty()){
            int current = que.deQueue();
            cout<<data[current].v<<' ';
            if (data[current].lchild) {
                current = data[current].lchild;
                que.enQueue(current);
                while(data[current].brother) {que.enQueue(data[current].brother); current = data[current].brother;}
            }
        }
    }

    void levelOrder()const {levelOrder(root);}

    void preOrder(int t)const
    {
        if (t == 0) return;
        cout<<data[t].v<<' ';
        int n = data[t].lchild;
        while(n){
            preOrder(n);
            n = data[n].brother;
        }
    }

    void preOrder()const {preOrder(root);}

    void postOrder(int t)const
    {
        if (t == 0) return;
        int n = data[t].lchild;
        while(n) {
            postOrder(n);
            n = data[n].brother;
        }
        cout<<data[t].v<<' ';
    }

    void postOrder()const {postOrder(root);}
};

int main()
{
    int N;
    cin >> N;
    staticBTree bt;
    bt.createTree(N);
    bt.preOrder();
    cout<<endl;
    bt.postOrder();
    cout<<endl;
    bt.levelOrder();
    cin.get();
    cin.get();
    return 0;
}
