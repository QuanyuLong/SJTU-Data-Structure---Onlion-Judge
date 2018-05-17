#include <iostream>
#include <cstring>
using namespace std;

template <class elemType>
class bernoulliQueue {
private:
    struct node{
        elemType data;
        node * son, * brother;
        node():son(NULL), brother(NULL){}
        node(const elemType & x,node * s = NULL,node * b = NULL):data(x), son(s), brother(b){}
    };
    node ** bernoulliForest;
    int maxSize;

    node * mergeTree(node * t1, node * t2)
    {
        if (t1->data > t2->data) return mergeTree(t2, t1);
        t2->brother = t1->son;
        t1->son = t2;
        return t1;
    }
    node ** mergeForest(node ** f1, node ** f2)
    {
        node ** resultForest = new node * [maxSize] {NULL};
        for (int i = 0; i < maxSize; ++i){
            if(f1[i] == NULL && f2[i] == NULL) continue;
            if(f1[i] == NULL && f2[i]){
                if(resultForest[i] == NULL) resultForest[i] = f2[i];
                else {resultForest[i+1] = mergeTree(resultForest[i] , f2[i]); resultForest[i] = NULL;}
            }
            if(f1[i] && f2[i] == NULL){
                if(resultForest[i] == NULL) resultForest[i] = f1[i];
                else {resultForest[i+1] = mergeTree(resultForest[i] , f1[i]); resultForest[i] = NULL;}
            }
            if(f1[i] && f2[i]) resultForest[i+1] = mergeTree(f1[i], f2[i]);
        }
        return resultForest;
    }
    node ** bernoulliTreeToForest(node * t, int level)
    {
        node ** resultForest = new node * [maxSize] {NULL};
        node * tmp = t->son;
        for (int i = level-1; i >= 0; --i){
            resultForest[i] = tmp;
            if(tmp->brother) tmp = tmp->brother;
        }
        for (int i = 0; i < level; ++i) resultForest[i]->brother = NULL;
        return resultForest;
    }
    void clearTree(node * p);


public:
    bernoulliQueue(int initialSize = 20){maxSize = initialSize; bernoulliForest = new node * [maxSize]{NULL};}
    ~bernoulliQueue();
    void enQueue(const elemType & x);
    elemType dequeue();
    void getmin() const;
};

template <class elemType>
void bernoulliQueue<elemType>::clearTree(node * p)
{
    if (p)
    {
        node *tmp = p->son;
        delete p;
        while (tmp)
        {
            p = tmp->brother;
            clearTree(tmp);
            tmp = p;
        }
    }
}

template <class elemType>
bernoulliQueue<elemType>::~bernoulliQueue()
{
    for(int i = 0; i < maxSize; ++i) if(bernoulliForest[i]) clearTree(bernoulliForest[i]);
    delete [] bernoulliForest;
}

template <class elemType>
void bernoulliQueue<elemType>::enQueue(const elemType & x)
{
    node * tmp = new node (x);
    int i = 0;
    for (i = 0; i < maxSize; ++i){
        if(bernoulliForest[i] == NULL) break;
        tmp = mergeTree(bernoulliForest[i], tmp);
        bernoulliForest[i] = NULL;
    }
    bernoulliForest[i] = tmp;
}

template <class elemType>
elemType bernoulliQueue<elemType>::dequeue()
{
    int minIndex;
    elemType minElem;
    bool flag = true;
    //find minimum tree-root int the bernoulli forest
    for (int i = 0; i < maxSize; ++i){
        if (bernoulliForest[i] != NULL && flag) {minElem = bernoulliForest[i]->data; flag = false; minIndex = i;continue;}
        if(!flag){
            if (bernoulliForest[i]!= NULL && bernoulliForest[i]->data < minElem) {minElem = bernoulliForest[i]->data; minIndex = i;}
        }
    }

    node ** tmp = bernoulliTreeToForest(bernoulliForest[minIndex], minIndex);
    bernoulliForest[minIndex] = NULL;
    bernoulliForest = mergeForest(bernoulliForest, tmp);
    return minElem;
}

template <class elemType>
void bernoulliQueue<elemType>::getmin()const
{
    elemType minElem;
    bool flag = true;
    //find minimum tree-root int the bernoulli forest
    for (int i = 0; i < maxSize; ++i){
        if (bernoulliForest[i] != NULL && flag) {minElem = bernoulliForest[i]->data; flag = false; continue;}
        if(!flag){
            if (bernoulliForest[i]!= NULL && bernoulliForest[i]->data < minElem) minElem = bernoulliForest[i]->data;
        }
    }
    cout<<minElem<<endl;
}

int main()
{
    int num_of_commands;
    cin >> num_of_commands;
    char command [10];
    int x;
    bernoulliQueue<int> priQueue;

    for (int i = 0; i < num_of_commands ; ++i){
        cin>>command;
        if(strcmp(command, "insert") == 0){
            cin >> x;
            priQueue.enQueue(x);
        }
        else if(strcmp(command, "delete") == 0){
            priQueue.dequeue();
        }
        else if(strcmp(command, "min") == 0){
            priQueue.getmin();
        }
    }
}
