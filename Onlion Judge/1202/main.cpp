#include <iostream>
#include <cstring>
using namespace std;
class outOfBound {};
class illigalSize {};

class list{
public:
    virtual int length() const = 0;
    virtual int search(const int &x)const = 0;
    virtual int visit(int i)const = 0;
    virtual void insert(int i, const int &x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse()const = 0;
    virtual ~list() {}
};

class linkList : public list{ //attention!!
    friend void adding(const linkList & obj1,const linkList & obj2)
    {
        int x = 0,tmp, data1,data2;
        node * p = obj1.head->next, * q = obj2.head->next;
        linkList result;
        while(p!=NULL || q!=NULL){
            if(!p) data1 = 0; else data1 = p->data;
            if(!q) data2 = 0; else data2 = q->data;
            tmp = data1 + data2 + x;
            x = tmp/10;
            tmp = tmp % 10;
            result.insert(0,tmp);
            if(p)p = p->next;
            if(q)q = q->next;
        }
        if (x>0) result.insert(0,1);
        result.traverse();
    }
private:
    struct node{
        int data;
        node * next;
        //attention! const and &
        node(const int &d, node * p = NULL){data = d; next = p;}
        node() {next = NULL;}
        //attention
        ~node(){}
    };
    node * head;
public:
    linkList(){head = new node();}
    int length() const;
    int search(const int & x)const;
    int visit(int i) const;
    void insert(int i, const int & x);
    void remove(int i);
    void clear();
    void traverse() const;
    ~linkList();
    void reverse();
};

int linkList::length() const
{
    node * p = head->next;
    int result = 0;
    while (p) {p = p->next; ++result;}
    return result;
}

int linkList::search(const int & x) const
{
    int i = 0;
    node * p = head->next;
    while (p) {
        if (p->data == x) break;
        ++i;
        p = p->next;
    }
    if (p) return i;
    return -1;
}

int linkList::visit(int i)const
{
    if (i < 0) throw outOfBound();
    node * p = head->next;
    while (p && i) {
        p = p->next;
        --i;
    }
    if (!p) throw outOfBound();
    return p->data;
}

void linkList::insert(int i, const int & x)
{
    if (i < 0) throw outOfBound();
    node * tmp = new node(x);
    node * p = head;
    while(p && i){
        p = p->next;
        --i;
    }
    if (!p) throw outOfBound();
    tmp->next = p->next; p->next = tmp;
}

void linkList::remove(int i)
{
    if (i < 0)throw outOfBound();
    node * p, *q;
    p = head; q = p->next;
    while (q && i){
        p = q; q = p->next; --i;
    }
    if (! q) throw outOfBound();
    p->next = q->next;
    delete q;
}

void linkList::clear()
{
    node * p, *q;
    p = head; q = p->next;
    while (q){
        p = q->next;
        delete q;
        q = p;
    }
}

void linkList::traverse()const
{
    node * p = head->next;
    while (p){
        cout<<p->data;
        p = p->next;
    }
}

linkList::~linkList()
{
    clear();
    delete head;
}

int main()
{
    char tmp = cin.get();
    linkList list1,list2;
    while(tmp != '\n'){
        list1.insert(0,tmp - '0');
        tmp = cin.get();
    }
    tmp = cin.get();
    while(tmp != '\n'){
        list2.insert(0,tmp - '0');
        tmp = cin.get();
    }
    adding(list1,list2);
}
