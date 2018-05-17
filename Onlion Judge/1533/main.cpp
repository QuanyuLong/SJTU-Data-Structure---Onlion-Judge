#include <iostream>

using namespace std;

int function(int n, int x, int y)
{
    int i = 1, j = 1, direction = 0, cnt = -1;
    bool flag = false;
    if (n == 1) return 0;
    for (int k = 0; k < 4*n-4; ++k)
    {
        ++cnt;
        if (i == x && j == y) { flag = true; break;}
        if(direction == 0){
            if(j == n) {++i; direction = 1;}
            else ++j;
            continue;
        }
        if(direction == 1){
            if(i == n) {--j; direction = 2;}
            else ++i;
            continue;
        }
        if(direction == 2){
            if(j == 1) {--i; direction = 3;}
            else --j;
            continue;
        }
        if(direction == 3){
            if (i == 2) break;
            else --i;
        }
    }
    if (flag) return cnt;
    else return cnt + 1 + function(n-2, x-1, y-1);
}


int main()
{
    int n, x, y;
    cin >> n >>x >>y;
    cout<<function(n, x, y);
}
