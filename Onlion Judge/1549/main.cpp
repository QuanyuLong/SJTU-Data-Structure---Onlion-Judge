#include <iostream>
#include <cstring>
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
    char str [101], result[101];
    linkStack<char> stack1;
    linkStack<int> stack2;
    while(cin.getline(str,101,'\n')){
        strcpy(result, str);
        for(int i = 0; str[i]!='\0'; ++i){
            if (str[i] == '(') {
                stack1.push('(');
                stack2.push(i);
                result[i] = ' ';
            }
            else{
                if (str[i] == ')') {
                    if(stack1.isEmpty()) result[i] = '?';
                    else {stack1.pop(); stack2.pop(); result[i] = ' ';}
                }
                else result[i] = ' ';
            }
        }
        while(!stack1.isEmpty()){
            stack1.pop();
            result[stack2.pop()] = '$';
        }
        cout<<str<<endl;
        cout<<result<<endl;
    }
}








