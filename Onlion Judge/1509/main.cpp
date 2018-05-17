#include <iostream>
#include <cstdio>
using namespace std;

int s1[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int s2[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

bool runnian( int y)
{
  if(y%400 ==0 )
      return true;
  else if(y%4 == 0 && y%100 !=0)
      return true;
  else
      return false;
}
int huansuan(int y,int a,int b)
{
  int sum=0;
  for(int i=1850;i<y;i++)
  {
    if( runnian(i))
        sum += 366;
    else
        sum += 365;
  }

  if(runnian(y))
  {
    for(int i=1;i<a;i++)
    {
    sum += s2[i];
    }
  }
  else
  {
    for(int i=1;i<a;i++)
    {
    sum += s1[i];
    }
  }
  int result = ((sum+b-1)%7+2)%7;
  if (result==0) result = 7;
  return result;
  cout<<result<<endl;
}

int fun(int y,int a,int b,int c)
{
  int z = huansuan(y,a,1);
  //cout<<z<<endl;
  if(b==1 && c<z )
      return 0;
  else
  {
    int x= (7-z+1)+(b-2)*7+c;
    if (c < z) x += 7;
    if(runnian(y))
    {
      if( x>s2[a])
        return 0;
      else
        return x;
    }
    else
    {
      if( x>s1[a] )
        return 0;
      else
        return x;
    }
  }
}

int main()
{
  int a,b,c,y1,y2;
  cin >> a >> b >> c >> y1 >> y2;

  for(int i=y1;i<=y2;i++)
  {
    int j = fun(i,a,b,c);
    if(j !=0) {
        if(a>=10&&j>=10)  cout<<i<<"/"<<a<<"/"<<j<<endl;
        if(a<10&&j>=10)  cout<<i<<"/0"<<a<<"/"<<j<<endl;
        if(a>=10&&j<10)   cout<<i<<"/"<<a<<"/0"<<j<<endl;
        if(a<10&&j<10)  cout<<i<<"/0"<<a<<"/0"<<j<<endl;
    }
    else cout <<"none"<<endl;
  }
  return 0;
}
/*
#include <iostream>
using namespace std;

bool is_Special(int year){
    if(year%400==0||(year%4==0&&year%100!=0))
        return true;
    else return false;
}

int main(){
    int a,b,c,y1,y2;
    cin>>a>>b>>c>>y1>>y2;
    int month_day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=y1;i<=y2;i++){  //从y1年开始遍历，一直到y2年
        int first_day = 2;      //保存的是第i年第一天是星期几
        int base = 1850;   //基准是1850
        while(base!=i){
            if(is_Special(base))
                first_day = (first_day + 2)%7;
            else
                first_day = (first_day + 1)%7;
            if(first_day==0)
                first_day = 7;
            base++;
        }
        int month = 1;    //下面求第a个月第1天是星期几，用first_day表示
        while(month != a){
            if(is_Special(i))
                month_day[1] = 29;   //表示闰年2月份有29天
            first_day = (first_day + month_day[month-1]%7)%7;
            if(first_day == 0)
                first_day = 7;
            month++;
        }
        int day = 1;  //表示最终结果：第a月第day天
        day = day + 7*(b-2) + c + (7 - first_day);
        if((c - first_day) < 0)
            day = day + 7;
        if(day > month_day[a-1])
            cout<<"none"<<endl;  //表示day超过当前月最大天数
        else{
                if(a>=10&&day>=10)
                    cout<<i<<"/"<<a<<"/"<<day<<endl;
                if(a<10&&day>=10)
                    cout<<i<<"/0"<<a<<"/"<<day<<endl;
                if(a>=10&&day<10)
                    cout<<i<<"/"<<a<<"/0"<<day<<endl;
                if(a<10&&day<10)
                    cout<<i<<"/0"<<a<<"/0"<<day<<endl;
            }
        month_day[1] = 28;
    }
    return 0;
}
*/
