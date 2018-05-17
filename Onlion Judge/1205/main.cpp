#include <iostream>

using namespace std;
class stack{
public:
    virtual int pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual void push(const int & obj) = 0;
    virtual int top() const = 0;
    virtual ~stack() {}
};

class linkStack : public stack{
private:
    struct node{
        int data;
        node * next;
        node():next(NULL){}
        node(const int & obj, node * n = NULL):data(obj),next(n){}
        ~node(){}
    };
    node * Top;
public:
    linkStack() {Top = NULL;}
    bool isEmpty() const;
    int pop();
    void push(const int & obj);
    int top() const;
    ~linkStack();
};

bool linkStack::isEmpty()const
{
    return Top == NULL;
}

int linkStack::top()const
{
    return Top->data;
}

int linkStack::pop()
{
    node * tmp = Top;
    int x = Top->data;
    Top = Top->next;
    delete tmp;
    return x;
}

void linkStack::push(const int& obj)
{
    node * tmp = new node(obj,Top);
    Top = tmp;
}

linkStack::~linkStack()
{
    node * tmp = Top;
    while(tmp)
    {
        tmp = Top->next;
        delete Top;
        Top = tmp;
    }
}

long Akm(int m,int n)
{//Akerman函数的递归算法
    if(m==0)//条件m==0成立
        return n+1;
    else if(n==0)//条件m!=0且n==0成立
        return Akm(m-1,1);
    else//条件m!=0且n!=0成立
        return Akm(m-1,Akm(m,n-1));
}

int main()
{
    int m,n;
    linkStack stack1;
    cin>>m>>n;
    /*stack1.push(m);
    while(!stack1.isEmpty()){
        m = stack1.pop();
        if (m==0) n=n+1;
        else if (n==0) {stack1.push(m-1);n=1;}
        else {stack1.push(m-1);stack1.push(m);n=n-1;}
    }
    cout<<n;
    */
    cout<<Akm(m,n);
}
