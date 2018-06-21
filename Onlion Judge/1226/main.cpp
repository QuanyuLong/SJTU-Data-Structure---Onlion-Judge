#include <iostream>

using namespace std;

void Swap(int * arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int devide(int * arr, int low, int high)
{
    int mid = (low + high) / 2;
    if(arr[low] > arr[mid]) Swap(arr, low, mid);
    if(arr[mid] > arr[high]) Swap(arr, mid, high);
    if(arr[mid] > arr[low]) Swap(arr, mid, low);
    int pattern = arr[low];
    do{
        while(low < high && arr[high] >= pattern) --high;
        if(low < high) {arr[low] = arr[high]; ++low;}
        while(low < high && arr[low] <= pattern) ++low;
        if(low <  high) {arr[high] = arr[low]; --high;}
    }while(low != high);
    arr[low] = pattern;
    return low;
}

void quickSort(int * arr, int low, int high)
{
    if(low >= high) return;
    int mid = devide(arr, low, high);
    quickSort(arr, mid+1, high);
    quickSort(arr, low, mid-1);
}

int main()
{
    int N, * arr;
    cin >> N;
    arr = new int [N];
    for(int i = 0; i < N; ++i){
        cin>>arr[i];
    }
    quickSort(arr, 0, N-1);
    for(int i = 0; i < N; ++i) cout<<arr[i]<<' ';
}
