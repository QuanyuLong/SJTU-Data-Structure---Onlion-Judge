#include <iostream>
#include<fstream>
using namespace std;
template <class elemType>
class stack{
public:
    virtual elemType pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType & obj) = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};
template <class elemType>
class linkStack : public stack<elemType> {
private:
    struct node{
        elemType data;
        node * next;
        node() {next = NULL;}
        node(const elemType & obj, node * n = NULL) {data = obj; next = n;}
    };
    node * Top;
public:
    linkStack() {Top = NULL;}
    bool isEmpty() const;
    elemType pop();
    void push(const elemType & obj);
    elemType top() const;
    ~linkStack();
};

template <class elemType>
bool linkStack<elemType>::isEmpty()const
{
    return Top == NULL;
}

template <class elemType>
elemType linkStack<elemType>::top()const
{
    return Top->data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    node * tmp = Top;
    elemType x = Top->data;
    Top = Top->next;
    delete tmp;
    return x;
}

template <class elemType>
void linkStack<elemType>::push(const elemType & obj)
{
    node * tmp = new node(obj,Top);
    Top = tmp;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node * tmp = Top;
    while(tmp)
    {
        tmp = Top->next;
        delete Top;
        Top = tmp;
    }
}
int main()
{
    /*
    fstream file("input.txt");
    int num, po, sep, i = 0;
    file>>num;
    //cout<<num<<endl;
    int position[num], speed[num];
    while(file>>po>>sep && i < num){
        //cout<<po<<' '<< sep<<endl;
        position[i] = po;
        speed[i] = sep;
        i ++;
    }
    */

    int num, po, sep, i = 0;
    cin>>num;
    int position[num], speed[num];
    while(cin>>po>>sep && i < num){
        //cout<<po<<' '<< sep<<endl;
        position[i] = po;
        speed[i] = sep;
        i ++;
    }
/*
    bool flag;
    //for(int i = 0; i < num; ++i) cout<< position[i]<<' '<<speed[i]<<endl;
    for(int j = 1; j < num; ++j)
    {
        if(position[j]==position[j-1]) {if (speed[j] > speed[j-1]) speed[j] = speed[j-1];}
    }
    while(true){
        flag = true;
        position[num-1] += speed[num-1];
        for(int j = num-2; j >= 0; --j){
            position[j] += speed[j];
            if (position[j] >= position[j+1] && speed[j] != speed[j+1]){
                position[j] = position[j+1];
                speed[j] = speed[j+1];
                flag = false;
            }
            if (position[j] <= position[j+1] && speed[j] > speed[j+1]) flag = false;
        }
        if (flag) break;
        //for(int i = 0; i < num; ++i) cout<< position[i]<<' '<<speed[i]<<endl;
    }
    for(int i = 0; i < num; ++i) cout<< position[i]<<' '<<speed[i]<<endl;
    int result = 1, tmp = position[0];
    for(int j = 1; j < num; ++j){
        if (position[j] > tmp) {tmp = position[j]; ++result;}
    }
    cout<<result;
    */

    linkStack<int> stack1;
    for(int i = 0; i < num; ++i){
        if(stack1.isEmpty()) stack1.push(speed[i]);
        while(speed[i]<stack1.top() && !stack1.isEmpty()) stack1.pop()
    }
}
