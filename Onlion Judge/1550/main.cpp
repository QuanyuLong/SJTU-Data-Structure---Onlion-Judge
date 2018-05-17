#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int pow(int i)
{
    int result = 1;
    for(int j = 1; j <= i ;++j) result*=10;
    return result;
}

int str_to_int(char * str_num)
{
    int len = strlen(str_num);
    int result = 0;
    for(int i = 0; str_num[i]!='\0'; ++i){
        result += (str_num[i]-'0')*pow(len-i-1);
    }
    //cout<<result<<endl;
    return result;
}


int main()
{
    int num;
    cin>>num;
    int data[num], left_max[num], right_max[num], j = 0, k = 0, lm = 0, rm = 0, n;
    char* ch[num];
    char c;
    ch[0] = new char [10000];
    while(cin>>c){
        if(c>='0'&& c<= '9'){ch[j][k] = c;++k;}
        if(c==',' || c==']'){
            ch[j][k] = '\0';
            n = str_to_int(ch[j]);
            data[j] = n;
            if(j==0) {lm = n; left_max[0] = 0;}
            else {left_max[j] = lm;if(n>lm)lm = n;}
            ++j;
            ch[j] = new char [10000];
            k = 0;
        }
    }
    /*
    fstream file("input.txt");
    int num;
    file>>num;
    int data[num], left_max[num], right_max[num], j = 0, k = 0, lm = 0, rm = 0, n;
    char* ch[num];
    char c;
    ch[0] = new char [10000];
    while(file>>c){
        if(c>='0'&& c<= '9'){ch[j][k] = c;++k;}
        if(c==',' || c==']'){
            ch[j][k] = '\0';
            n = str_to_int(ch[j]);
            data[j] = n;
            if(j==0) {lm = n; left_max[0] = 0;}
            else {left_max[j] = lm;if(n>lm)lm = n;}
            ++j;
            ch[j] = new char [10000];
            k = 0;
        }
    }
    */
    //for(int i = 0; i < num; ++i) cout<<data[i]<<endl;
    //for(int i = 0; i < num; ++i) cout<<left_max[i]<<endl;
    for(int i = num - 1; i >= 0; --i){
        if(i ==0) {rm = data[i]; right_max[i] = 0;}
        else {right_max[i] = rm; if(data[i]>rm) rm = data[i];}
    }
    int result = 0;
    for(int i = 0; i<num; ++i){
        if(data[i]<left_max[i] && data[i]<right_max[i])result = result + min(left_max[i],right_max[i])-data[i];
    }
    cout<<result;
}
