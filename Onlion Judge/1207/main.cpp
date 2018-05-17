#include <iostream>
#include <fstream>
#include <iomanip>
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
    elemType getHead() const {
        if(isEmpty()) return -1;
        else  return front->data;
    }
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

int main()
{
    int num, car_type, arrive_T, count_Ke=0, count_Huo=0,count_ten = 0, count_four = 0, count_Chuan = 0;
    double wait_T_Ke = 0, wait_T_Huo = 0;
    bool flag1, flag2;
    linkQueue<double> queue_Ke, queue_Huo, queue_Chuan;
    cin>>num;

    while(cin>>car_type>>arrive_T){
        if (car_type == 0) {queue_Ke.enQueue(arrive_T);count_Ke++;}
        else {queue_Huo.enQueue(arrive_T);count_Huo++;}
    }

    //while(!queue_Huo.isEmpty()) cout<<queue_Huo.deQueue()<<endl;
    while(!queue_Ke.isEmpty() || !queue_Huo.isEmpty()){
        flag1 = queue_Ke.isEmpty() || queue_Ke.getHead()>count_Chuan*10;    //Ke is empty or next ship
        flag2 = queue_Huo.isEmpty() || queue_Huo.getHead()>count_Chuan*10;  //Huo is empty or next ship
        if (count_four < 4){
            if(flag1){
                if(!flag2) {
                    //cout<<"Huo de Que at 87."<<queue_Huo.getHead()<<' '<<wait_T_Huo<<endl;
                    wait_T_Huo=wait_T_Huo+count_Chuan*10-queue_Huo.deQueue();count_ten++;}//Huo de queue
            }
            else{wait_T_Ke=wait_T_Ke+count_Chuan*10-queue_Ke.deQueue();count_four++;count_ten++;}//Ke de queue
        }
        else{
            if(!flag2) {wait_T_Huo=wait_T_Huo+count_Chuan*10-queue_Huo.deQueue();count_ten++;count_four = 0;}//Huo de queue
            else {
                if(!flag1) {wait_T_Ke=wait_T_Ke+count_Chuan*10-queue_Ke.deQueue();count_ten++;count_four = 0;}//Ke de queue
            }
        }
        if(count_ten == 10 || (flag1 && flag2)){
            count_Chuan++;
            count_ten = 0;
            count_four = 0;
            //cout<<queue_Ke.getHead()<<' '<<queue_Huo.getHead()<<endl;
            //cout<<wait_T_Ke<<' '<<wait_T_Huo<<endl;
        }
    }
    //cout<<wait_T_Ke<<' '<<wait_T_Huo<<endl;
    cout<<fixed<<setprecision(3)<<wait_T_Ke*1.0/count_Ke;
    cout<<' ';
    cout<<fixed<<setprecision(3)<<wait_T_Huo*1.0/count_Huo;
}





