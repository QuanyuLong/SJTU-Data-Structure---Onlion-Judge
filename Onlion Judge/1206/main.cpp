#include <iostream>
#include <fstream>
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
/*
    fstream file("input.txt");
    linkStack<char> stack1;
    char tmp [1000], sentence[1000];
    sentence[0] = '\0';
    bool result = true;
    while(!file.eof())
    {
        file.getline(tmp,1000,'\n');
        for (int i = 0; tmp[i]!='\0'; ++i){
            if (tmp[i]=='i' && tmp[i+1]=='f') {strcat(sentence,"i");i+=1; continue;}
            if (tmp[i]=='t' && tmp[i+1]=='h' && tmp[i+2]=='e' && tmp[i+3]=='n') {strcat(sentence,"t");i+=3; continue;}
            if (tmp[i]=='e' && tmp[i+1]=='l' && tmp[i+2]=='s' && tmp[i+3]=='e') {strcat(sentence,"e");i+=3; continue;}
            if (tmp[i]=='b' && tmp[i+1]=='e' && tmp[i+2]=='g' && tmp[i+3]=='i' && tmp[i+4]=='n') {strcat(sentence,"b"); i+=4;continue;}
            if (tmp[i]=='e' && tmp[i+1]=='n' && tmp[i+2]=='d') {strcat(sentence,"d");i+=2;}
        }
    }
    //cout<<sentence<<endl;
*/
    linkStack<char> stack1;
    char str[1000];
    bool result = true;
    //cout<<sentence<<endl;
    while(cin>>str){
        if (strcmp(str, "begin") == 0 ||strcmp(str, "if") == 0){stack1.push(str[0]);continue;}
        if (strcmp(str, "then") == 0) {
            if(stack1.isEmpty() || stack1.pop()!= 'i') {result = false; break;}
            else {stack1.push('t'); continue;}
        }
        if (strcmp(str, "end") == 0){
            while(true){
                if(stack1.isEmpty()||stack1.top()=='i') {result = false; break;}
                if(stack1.pop()=='b') break;
            }
            if(!result) break;
            else continue;
        }
        if (strcmp(str, "else") == 0){
            if(stack1.isEmpty() || stack1.pop()!='t') {result = false; break;}
            else continue;
        }
    }
    while(!stack1.isEmpty()){
        if(stack1.pop()!='t') {result = false; break;}
    }
    if (result) cout<<"Match!"<<endl;
    else cout<<"Error!"<<endl;
}

/*
#include <iostream>
#include <cstring>
using namespace std;

class stack
{
private:
    char *data;
    int topP;
    int maxSize;

    void doubleSpace()
    {
        char *tmp = data;
        data = new char[maxSize * 2];
        for (int i = 0;i < maxSize;++i)data[i] = tmp[i];
        maxSize *= 2;
        delete[] tmp;
    }
public:
    stack() :topP(-1), maxSize(10) { data = new char[maxSize]; }
    bool empty()
    {
        return topP == -1;
    }
    void push(char c)
    {
        if (topP == maxSize - 1)doubleSpace();
        data[++topP] = c;
    }
    char pop()
    {
        if(!empty()) return data[topP--];
    }
    char top()
    {
        if(!empty()) return data[topP];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    stack v;
    char str[1000];
    bool isOk = true;
    while (cin >> str)
    {
        if (strcmp(str, "begin") == 0 || strcmp(str, "if") == 0)
            v.push(str[0]);
        else if (strcmp(str, "then") == 0)
        {
            if (v.empty() || v.pop()!='i') isOk = false;
            else v.push('t');
        }
        else if (strcmp(str, "end") == 0)
        {
            do
            {
                if (v.empty()||v.top()=='i')
                {
                    isOk = false;break;
                }
                if (v.pop() == 'b')break;
            } while (true);
            if (!isOk)break;
        }
        else if (strcmp(str, "else") == 0)
        {
            if (v.empty() || v.pop()!='t') isOk = false;
        }
        if (!isOk) break;
    }
    while (isOk&&!v.empty())
    {
        if (v.pop() != 't')isOk = false;
    }
    if (isOk)cout << "Match!" << '\n';
    else cout << "Error!" << '\n' ;
    cin.get();
    cin.get();
    return 0;
}
*/
