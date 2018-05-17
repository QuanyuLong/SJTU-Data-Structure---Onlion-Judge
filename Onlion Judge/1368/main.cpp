#include <iostream>
#include <fstream>
using namespace std;

struct node{
    node(const int &d, node * n = NULL):data(d), next(n) {}
    node():next(NULL) {}
    int data;
    node * next;
    ~node(){}
};


int main()
{
    //fstream file("input.txt");
    int operation, result = 1; //n:number of monkey, m:number of operation
    long long int n,m,w,k,current_length;
    cin>>n>>m;
    current_length = n;
    //file>>n>>m;
    node * q, * p = new node (1),* head = p, *tmp;
    for(int i = 2; i <= n; ++i){
        q = new node(i);
        p->next = q;
        p = q;
        result += i;
    }
    p->next = head;p = head->next;
    //for(int i = 1; i<=n+1; ++i) {cout<<p->data<<endl;p = p->next;}
    //cout<<q->data<<' '<<head->data<<' '<<p->data<<endl;
    while(cin>>operation){
    //while(file>>operation){
        //if(operation == 0) file>>k;
        if(operation == 0) cin>>k;
        //else file>>k>>w;
        else cin>>k>>w;
        k = k % current_length;
        if(k == 0) k = current_length;
        while(k > 1){
            p = p->next; head=head->next; q = q->next;
            k--;
        }
        if(operation==0){
            result -= head->data;
            q->next = p;
            delete head;
            head = p;
            p=p->next;
            --current_length;
        }
        else{
            result += w;
            tmp = new node(w, p);
            head->next = tmp;
            q = head; head = tmp;
            ++current_length;
        }
        //cout<<head->data<<endl;
    }
    cout<<result;
}
