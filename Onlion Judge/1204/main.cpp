#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class list{
public:
    virtual int length() const = 0;
    virtual int search(const char &x)const = 0;
    virtual char visit(int i)const = 0;
    virtual void insert(int i, const char &x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse()const = 0;
    virtual ~list() {}
};
class outOfBound{};
class illigalSize{};

class seqList : public list{
private:
    int currentLength;
    int maxSize;
    char * data;
    void doubleSpace()
    {
        char * tmp = new char [maxSize * 2];
        if (!tmp) throw illigalSize();
        for (int i = 0; i<currentLength; ++i) tmp[i] = data[i];
        delete [] data;
        data = tmp;
        maxSize = maxSize * 2;
    }
public:
    seqList(int initSize);
    seqList(const char * s);
    seqList(const seqList & obj);
    int length() const;
    int search(const char & x)const;
    char visit(int i)const;
    void insert(int i, const char &x);
    void remove(int i);
    void clear()
    {
        currentLength = 0;
    }
    void traverse()const
    {
        for(int i=0; i< currentLength; ++i) cout<<data[i];
        cout<<endl;
    }
    ~seqList()
    {
        delete [] data;
    }
    seqList & operator=(const seqList & obj);
};

seqList::seqList(int initSize)
{
    data = new char [initSize];
    if (!data) throw illigalSize(); //容易忘记开辟空间失败的情况
    currentLength = 0;
    maxSize = initSize;
}

seqList::seqList(const char *s)
{
    maxSize = 2001;
    currentLength = strlen(s);
    data = new char [maxSize];
    for (int i = 0; i<currentLength;++i){
        data[i] = s[i];
    }
}

seqList::seqList(const seqList & obj)
{
    currentLength = obj.currentLength;
    maxSize = obj.maxSize;
    data = new char [maxSize];
    if (!data) throw illigalSize();
    for (int i = 0; i<currentLength; ++i) data[i] = obj.data[i];
}

int seqList::length() const
{
    return currentLength;
}

int seqList::search(const char & x)const
{
    int i;
    for (i = 0; i < currentLength; ++i) if (data[i]==x) break;
    if (i != currentLength) return i;
    return -1;
}

char seqList::visit(int i)const
{
    return data[i];
}

//i is not the index, count from 1, pay attention to can add a string at the end of list
void seqList::insert(int i,const char & x)
{
    if (currentLength == maxSize) doubleSpace();
    if (i == currentLength+1)
    {
        data[currentLength] = x;
        ++currentLength;
        return;
    }
    if (i < 1 || i > currentLength+1) {cout<<"Error!"<<endl; return;}
    for (int j = currentLength; j > i-1; --j) data[j] = data[j-1];
    data[i-1] = x;
    currentLength ++; //容易忘记
}

void seqList::remove(int i)
{
    if (i < 1 || i > currentLength) {cout<<"Error!"<<endl; return;}
    for (int j = i-1; j < currentLength; ++j) data[j] = data[j + 1];
    currentLength --;
}

seqList & seqList::operator=(const seqList & obj)
{
    if (this == & obj) return * this;
    delete [] data;
    maxSize = obj.maxSize;
    currentLength = obj.currentLength;
    data = new char [maxSize];
    for (int i = 0; i < currentLength; ++i) data[i] = obj.data[i];
    return * this;
}

void list(seqList * listlist [],int line_num,  int i, int j)
{
    if (i < 1 || j < 1 || i > line_num || j > line_num || i > j) {cout<<"Error!"<<endl; return;}
    for (int k = i-1; k < j;++k) listlist[k]->traverse();
}

void ins(seqList * listlist [],int line_num, int i, int j, char * s)
{
    if (i < 1 ||  i > line_num) {cout<<"Error!"<<endl; return;}
    int line_len = listlist[i-1]->length();
    if (j < 1 || j > line_len+1) {cout<<"Error!"<<endl; return;}
    for(unsigned int k = 0; k < strlen(s);++k) {
        listlist[i-1]->insert(j+k,s[k]);
    }
}

//pay attention to the range of i , j ,and num > length
void del(seqList * listlist [],int line_num, int i, int j, int num)
{
    if (i < 1 ||  i > line_num) {cout<<"Error!"<<endl; return;}
    int line_len = listlist[i-1]->length();
    if (j < 1 || j > line_len || num > line_len-j+1) {cout<<"Error!"<<endl; return;}
    for (int k = 0; k < num; ++k){
        listlist[i-1]->remove(j);
    }
}
int Pow(int i,int j)
{
    int result = 1;
    while(j) {result *= i; --j;}
    return result;
}
int str_to_int(char * s)
{
    int result = 0;
    //cout<<s<<strlen(s)<<endl;
    for(unsigned int i = 0; i < strlen(s);++i)
    {
        result += (s[i]-'0')*Pow(10,strlen(s)-i-1);
    }
    return result;
}
int main()
{
    ifstream infile("input.txt");
    char line[2001];
    seqList *listlist [100];
    infile.getline(line,2001,'\n');
    int line_num = 0;
    while(strcmp(line,"******")!=0){
        listlist[line_num] = new seqList(line);
        ++ line_num;
        infile.getline(line,2001,'\n');
    }
    //cout<<line_num<<endl;
    infile.getline(line,2001,'\n');
    //listlist[2]->insert(15,'X');
    while(strcmp(line,"quit")!=0){
        //cout<<line<<endl;
        //list
        if (line[0]=='l' && line[1]=='i'){
            int n1,n2,k,p;
            char N1 [2001],N2[2001];
            //n1 = 1, n2 = 1;
            int line_len = int(strlen(line));
            for (k = 5;line[k]!=' ';++k) N1[k-5] = line[k];
            N1[k-5] = '\0';
            n1 = str_to_int(N1);
            for (p = k+1;p<line_len;++p) N2[p-k-1] = line[p];
            N2[p-k-1] = '\0';
            n2 = str_to_int(N2);
            //cout<<n1<<' '<<n2<<endl;
            list(listlist,line_num,n1,n2);
        }
        //ins
        if (line[0]=='i' && line[1]=='n'){
            int i,j,k,p,q;
            char I [2001],J[2001],s[2001];
            //char s [] = "by yourself";
            //i = 3; j = 14;
            int line_len = int(strlen(line));
            for (k = 4;line[k]!=' ';++k) I[k-4] = line[k];
            I[k-4] = '\0';
            i = str_to_int(I);
            for (p = k+1;line[p]!=' ';++p) J[p-k-1] = line[p];
            J[p-k-1] = '\0';
            j = str_to_int(J);
            for (q = p +1;q<line_len;++q) s[q-p-1] = line[q];
            s[q-p-1] = '\0';
            //cout<<i<<' '<<j<<' '<<s<<endl;
            ins(listlist,line_num,i,j,s);
        }
        //del
        if (line[0]=='d'&&line[1]=='e'){
            int i,j,num,k,p,q;
            //i = 3; j = 14; num =3;
            char I [2001],J[2001],NUM[2001];
            int line_len = int(strlen(line));
            for (k = 4;line[k]!=' ';++k) I[k-4] = line[k];
            I[k-4] = '\0';
            i = str_to_int(I);
            for (p = k+1;line[p]!=' ';++p) J[p-k-1] = line[p];
            J[p-k-1] = '\0';
            j = str_to_int(J);
            for (q = p +1;q<line_len;++q) NUM[q-p-1] = line[q];
            NUM[q-p-1] = '\0';
            num = str_to_int(NUM);
            del(listlist,line_num,i,j,num);
        }
        infile.getline(line,2001,'\n');
    }
    if (strcmp(line,"quit")==0){
        for (int i = 0; i < line_num; ++i){listlist[i]->traverse();}
    }
}
