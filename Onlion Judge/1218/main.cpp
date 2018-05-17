#include <iostream>

using namespace std;

void quick_sort(int arr[], int left , int right)
{
    int pattern , _left = left, _right = right;
    if (left>right) return; else pattern = arr[left];
    while(left != right)
    {
        while (right > left && pattern <= arr[right]) --right;
        arr[left] = arr[right];
        while (right > left && pattern >= arr[left]) ++left;
        arr[right] = arr[left];
    }
    arr[left] = pattern;
    quick_sort(arr, _left, left-1);
    quick_sort(arr, right+1, _right);
}


class numSet{
private:
    struct node{
        int data;
        node * next;
        node(const int & x,node * p = NULL) :data(x), next(p) {}
        node(): next(NULL) {}
    };
    node * head;
    int length;
    void clear();
public:
    numSet();
    numSet(int arr[], int N);
    ~numSet();
    void print()const;
    void unionSet(int arr [], int N);
    void subtract(int arr[], int N);
    void intersection(int arr[], int N);
};

numSet::numSet()
{
    head = new node();
    length = 0;
}

numSet::numSet(int arr [], int N)
{
    quick_sort(arr, 0, N-1);
    head = new node();
    node * tmp, * p = head;
    for(int i = 0; i < N; ++i){
        tmp = new node(arr[i]);
        p->next = tmp;
        p = tmp;
    }
    length = N;
}

numSet::~numSet()
{
    clear();
}

void numSet::clear()
{
    node * p = head, * q;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
}

void numSet::print() const
{
    node * p = head->next;
    while(p){
        cout<<p->data<<' ';
        p = p->next;
    }
    cout<<'\n';
}

void numSet::unionSet(int arr [], int N)
{
    for(int i = 0; i < N; ++i){
        bool flag = true;
        node * p = head;
        while(p->next){
            if(p->next->data < arr[i] && p->next->next == NULL) {p = p->next; break;}
            else if(p->next->data == arr[i]) {flag = false; break;}
            else if(p->next->data > arr[i]) break;
            else if(p->next->data < arr[i] && p->next->data < arr[i]) {p = p->next; continue;}
            else if(p->next->data < arr[i] && p->next->data > arr[i]) {p = p->next;break;}
            else if(p->next->data < arr[i] && p->next->data == arr[i]) {flag = false; break;}
        }
        if(flag){
            node * tmp = p->next;
            p->next = new node(arr[i], tmp);
            ++length;
        }
    }
    print();
}

void numSet::subtract(int arr [], int N)
{
    for (int i = 0; i < N; ++i){
        node * p = head;
        bool flag = false;
        while(p->next){
            if(p->next->data == arr[i]){flag = true; break;}
            else if(p->next->data < arr[i]) p = p->next;
            else break;
        }
        if(flag){
            node * tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            --length;
        }
    }
    print();
}

void numSet::intersection(int arr[], int N)
{
    quick_sort(arr, 0, N-1);
    node * p, * tmp = new node (), * q = tmp;
    for(int i =0; i < N; ++i){
        //cout<<arr[i]<<endl;
        bool flag = false;
        p = head->next;
        while(p){
            if(p->data == arr[i]) {flag = true; break;}
            else if(p->data > arr[i]) break;
            else p = p->next;
        }
        if(flag){
            p = new node(arr[i], NULL);
            q->next = p;
            q = q->next;
        }
    }
    clear();
    head = tmp;
    print();
}


int main()
{

    int N, n, *arr;
    char ope;
    cin>>N;
    numSet s;
    for(int i = 0; i < N; ++i){
        cin>>ope>>n;
        if(i != 0) delete [] arr;
        arr = new int [n];
        for(int j = 0; j < n; ++j) cin>>arr[j];
        if(ope == '+') s.unionSet(arr, n);
        else if(ope == '-') s.subtract(arr, n);
        else if(ope == '*') s.intersection(arr, n);
    }

/*
    numSet s;
    int arr1[] = {1,2,3,4};
    int arr2[] = {1,4,5};
    s.intersection(arr1, 4);
    s.subtract(arr2, 3);
    s.unionSet(arr1, 4);
    s.intersection(arr2, 3);
    */
}
